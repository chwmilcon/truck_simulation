#pragma once

#include "sim_time.hpp"
#include "truck.hpp"
#include "station.hpp"

namespace Simulation {
// Event types for discrete event simulation
enum class EventType {
    MINING_COMPLETE,
    ARRIVE_AT_STATION,
    UNLOAD_COMPLETE
};

// Event structure for priority queue
struct Event {
    SimTime time;
    EventType type;
    std::shared_ptr<MiningTruck> truck;
    std::shared_ptr<UnloadStation> station;
    
    // Priority queue orders by time (earliest first)
    bool operator>(const Event& other) const {
        return time > other.time;
    }
};

}// namespace
