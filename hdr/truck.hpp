#pragma once

#include "stats.hpp"

namespace Simulation {

// Forward declare
class UnloadStation;

// Truck states
enum class TruckState {
    MINING,
    TRAVELING_TO_STATION,
    QUEUED_AT_STATION,
    UNLOADING,
    TRAVELING_TO_MINE
};

// Mining Truck class
class MiningTruck {
public:
    MiningTruck(int id) 
        : id_(id), state_(TruckState::MINING), current_station_(nullptr) {}
    
    int getId() const { return id_; }
    TruckState getState() const { return state_; }
    void setState(TruckState state) { state_ = state; }
    
    std::shared_ptr<UnloadStation> getCurrentStation() const { return current_station_; }
    void setCurrentStation(std::shared_ptr<UnloadStation> station) { 
        current_station_ = station; 
    }
    
    TruckStats& getStats() { return stats_; }
    const TruckStats& getStats() const { return stats_; }
    
    SimTime getQueueEntryTime() const { return queue_entry_time_; }
    void setQueueEntryTime(SimTime time) { queue_entry_time_ = time; }
    
private:
    int id_;
    TruckState state_;
    std::shared_ptr<UnloadStation> current_station_;
    TruckStats stats_;
    SimTime queue_entry_time_ = 0.0;
};

} // namespace
