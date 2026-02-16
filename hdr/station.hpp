#pragma once

#include "stats.hpp"

namespace Simulation {

// Forward declaration to min header includes.
class MiningTruck;

class UnloadStation {
public:
    UnloadStation(int id) 
        : id_(id), busy_(false), current_truck_(nullptr) {}
    
    int getId() const { return id_; }
    
    bool isBusy() const { return busy_; }
    void setBusy(bool busy) { busy_ = busy; }
    
    std::shared_ptr<MiningTruck> getCurrentTruck() const { return current_truck_; }
    void setCurrentTruck(std::shared_ptr<MiningTruck> truck) { 
        current_truck_ = truck; 
    }
    
    size_t getQueueLength() const { return queue_.size(); }
    
    void addToQueue(std::shared_ptr<MiningTruck> truck) {
        queue_.push(truck);
        stats_.max_queue_length = std::max(stats_.max_queue_length, 
                                           static_cast<int>(queue_.size()));
    }
    
    std::optional<std::shared_ptr<MiningTruck>> popFromQueue() {
        if (queue_.empty()) return std::nullopt;
        auto truck = queue_.front();
        queue_.pop();
        return truck;
    }
    
    StationStats& getStats() { return stats_; }
    const StationStats& getStats() const { return stats_; }
    
    SimTime getIdleStartTime() const { return idle_start_time_; }
    void setIdleStartTime(SimTime time) { idle_start_time_ = time; }
    
protected:
    int id_;
    bool busy_;
    std::shared_ptr<MiningTruck> current_truck_;
    std::queue<std::shared_ptr<MiningTruck>> queue_;
    StationStats stats_;
    SimTime idle_start_time_ = 0.0;
};
} //namespace
