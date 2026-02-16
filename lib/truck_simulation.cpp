#include <iostream>
#include "truck_simulation.hpp"

//
// helper
//
void not_implemented() {
    throw std::runtime_error("Function not yet implemented");
}

//
// Simulation 
//
namespace Simulation {
Truck_simulation::Truck_simulation(int num_trucks, int num_stations, unsigned int seed)
    : current_time_(0.0),
      num_trucks_(num_trucks),
      num_stations_(num_stations),
      rng_(seed),
      mining_dist_(MINING_TIME_MIN, MINING_TIME_MAX) {
    
    // Create trucks
    trucks_.reserve(num_trucks);
    for (int i = 0; i < num_trucks; ++i) {
        auto truck = std::make_shared<MiningTruck>(i);
        truck->getStats().truck_id = i;
        trucks_.push_back(truck);
    }
    
    // Create unload stations
    stations_.reserve(num_stations);
    for (int i = 0; i < num_stations; ++i) {
        auto station = std::make_shared<UnloadStation>(i);
        station->getStats().station_id = i;
        station->setIdleStartTime(0.0);
        stations_.push_back(station);
    }
    
    // Schedule initial mining completion events for all trucks
    for (auto& truck : trucks_) {
        SimTime mining_time = generateMiningTime();
        truck->getStats().total_mining_time += mining_time;
        scheduleEvent(mining_time, EventType::MINING_COMPLETE, truck);
    }
}

void Truck_simulation::run() {
    std::cout << "Starting simulation with " << num_trucks_ << " trucks and " 
              << num_stations_ << " stations...\n";
    std::cout << "Simulation duration: 72 hours (" << SIMULATION_DURATION << " minutes)\n\n";
    
    auto start = Clock::now();
    
    // Main event loop
    while (!event_queue_.empty() && current_time_ < SIMULATION_DURATION) {
        Event event = event_queue_.top();
        event_queue_.pop();
        
        // Advance simulation time
        current_time_ = event.time;
        
        // Process event based on type
        switch (event.type) {
            case EventType::MINING_COMPLETE:
                handleMiningComplete(event);
                break;
            case EventType::ARRIVE_AT_STATION:
                handleArriveAtStation(event);
                break;
            case EventType::UNLOAD_COMPLETE:
                handleUnloadComplete(event);
                break;
        }
    }
    
    // Update final statistics for idle stations
    for (auto& station : stations_) {
        if (!station->isBusy()) {
            station->getStats().total_idle_time += 
                current_time_ - station->getIdleStartTime();
        }
    }
    
    auto end = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Simulation completed in " << duration.count() << " ms\n";
    std::cout << "Simulated time: " << current_time_ / 60.0 << " hours\n\n";
}

void Truck_simulation::handleMiningComplete(const Event& event) {
    auto truck = event.truck;
    
    // Truck finished mining, now travels to unload station
    truck->setState(TruckState::TRAVELING_TO_STATION);
    truck->getStats().total_travel_time += TRAVEL_TIME;
    
    // Schedule arrival at station
    scheduleEvent(current_time_ + TRAVEL_TIME, 
                 EventType::ARRIVE_AT_STATION, truck);
}

void Truck_simulation::handleArriveAtStation(const Event& event) {
    auto truck = event.truck;
    
    // Select the station with shortest queue
    auto station = selectStation();
    truck->setCurrentStation(station);
    
    if (!station->isBusy()) {
        // Station is available, start unloading immediately
        station->setBusy(true);
        station->setCurrentTruck(truck);
        truck->setState(TruckState::UNLOADING);
        
        // Update station idle time
        station->getStats().total_idle_time += 
            current_time_ - station->getIdleStartTime();
        
        // Schedule unload completion
        scheduleEvent(current_time_ + UNLOAD_TIME, 
                     EventType::UNLOAD_COMPLETE, truck, station);
        
    } else {
        // Station is busy, join the queue
        truck->setState(TruckState::QUEUED_AT_STATION);
        truck->setQueueEntryTime(current_time_);
        station->addToQueue(truck);
    }
}

void Truck_simulation::handleUnloadComplete(const Event& event) {
    auto truck = event.truck;
    auto station = event.station;
    
    // Update statistics
    truck->getStats().trips_completed++;
    truck->getStats().total_unload_time += UNLOAD_TIME;
    station->getStats().trucks_serviced++;
    station->getStats().total_busy_time += UNLOAD_TIME;
    
    // Check if there are trucks waiting in queue
    auto next_truck_opt = station->popFromQueue();
    
    if (next_truck_opt.has_value()) {
        auto next_truck = next_truck_opt.value();
        
        // Calculate queue wait time for the next truck
        SimTime wait_time = current_time_ - next_truck->getQueueEntryTime();
        next_truck->getStats().total_queue_wait_time += wait_time;
        station->getStats().total_queue_wait_time += wait_time;
        
        // Start unloading the next truck immediately
        station->setCurrentTruck(next_truck);
        next_truck->setState(TruckState::UNLOADING);
        
        // Schedule unload completion for next truck
        scheduleEvent(current_time_ + UNLOAD_TIME, 
                     EventType::UNLOAD_COMPLETE, next_truck, station);
        
    } else {
        // No trucks waiting, station becomes idle
        station->setBusy(false);
        station->setCurrentTruck(nullptr);
        station->setIdleStartTime(current_time_);
    }
    
    // Current truck travels back to mine
    truck->setState(TruckState::TRAVELING_TO_MINE);
    truck->getStats().total_travel_time += TRAVEL_TIME;
    truck->setCurrentStation(nullptr);
    
    // After travel time, truck starts mining again (if within simulation time)
    SimTime arrival_at_mine = current_time_ + TRAVEL_TIME;
    if (arrival_at_mine < SIMULATION_DURATION) {
        SimTime mining_time = generateMiningTime();
        
        // Check if mining will complete within simulation time
        if (arrival_at_mine + mining_time <= SIMULATION_DURATION) {
            truck->getStats().total_mining_time += mining_time;
            scheduleEvent(arrival_at_mine + mining_time, 
                         EventType::MINING_COMPLETE, truck);
        } else {
            // Partial mining time until end of simulation
            SimTime partial_mining = SIMULATION_DURATION - arrival_at_mine;
            if (partial_mining > 0) {
                truck->getStats().total_mining_time += partial_mining;
            }
        }
    }
}

SimTime Truck_simulation::generateMiningTime() {
    return mining_dist_(rng_);
}

std::shared_ptr<UnloadStation> Truck_simulation::selectStation() {
    // Select station with shortest queue (greedy approach)
    return *std::min_element(stations_.begin(), stations_.end(),
        [](const auto& a, const auto& b) {
            // If one is free and other is busy, prefer the free one
            if (!a->isBusy() && b->isBusy()) return true;
            if (a->isBusy() && !b->isBusy()) return false;
            // Otherwise compare queue lengths
            return a->getQueueLength() < b->getQueueLength();
        });
}

void Truck_simulation::scheduleEvent(SimTime time, EventType type,
                                    std::shared_ptr<MiningTruck> truck,
                                    std::shared_ptr<UnloadStation> station) {
    Event event{time, type, truck, station};
    event_queue_.push(event);
}


}// namespace
