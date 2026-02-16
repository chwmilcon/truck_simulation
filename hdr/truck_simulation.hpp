#pragma once

// CHW: initial bunch of headers, check for unneeded.
#include <chrono>
#include <queue>
#include <vector>
#include <memory>
#include <random>
#include <mutex>
#include <atomic>
#include <optional>

#include "helper.hpp"
#include "sim_time.hpp"
#include "event.hpp"
#include "station.hpp"
#include "truck.hpp"

namespace Simulation {

//
// Trucking simulation main class
//
class Truck_simulation 
{
public:
    // TODO: complete, just to get tests compiling.
    Truck_simulation(int num_trucks, int num_stations, unsigned int seed = 42);
    virtual ~Truck_simulation() = default;
    Truck_simulation(const Truck_simulation &obj) = delete;
    Truck_simulation& operator=(const Truck_simulation&) = delete;
    Truck_simulation& operator=(Truck_simulation&&) = delete;
    friend std::ostream& operator<<(std::ostream& ostr, const Truck_simulation& obj) {
        return obj.output(ostr);
    }
    void run();
    void printStatistics() const;

// NOTE: reviewer, our team prefers protected over private, this isn't
// the case for all teams.
protected:
    // Event handlers
    void handleMiningComplete(const Event& event);
    void handleArriveAtStation(const Event& event);
    void handleUnloadComplete(const Event& event);

    // Helper methods
    SimTime generateMiningTime();
    std::shared_ptr<UnloadStation> selectStation();
    void scheduleEvent(SimTime time, EventType type, 
                      std::shared_ptr<MiningTruck> truck,
                      std::shared_ptr<UnloadStation> station = nullptr);


    virtual std::ostream& output(std::ostream& ostr) const {
        ostr << "Truck_simulation:";
        return ostr;
    }

// NOTE: Our team makes a separate protected section for member data
// for internal tooling.
protected:    
    // Simulation state
    SimTime current_time_;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> event_queue_;
    
    // Configuration
    int num_trucks_;
    int num_stations_;
    
    // Entities
    std::vector<std::shared_ptr<MiningTruck>> trucks_;
    std::vector<std::shared_ptr<UnloadStation>> stations_;
    
    // Random number generation
    std::mt19937 rng_;
    std::uniform_real_distribution<SimTime> mining_dist_;            
};
} // namespace
