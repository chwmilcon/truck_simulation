#pragma once

namespace Simulation {
// Statistics tracking for unload stations
struct StationStats {
    int station_id;
    int trucks_serviced = 0;
    SimTime total_busy_time = 0.0;
    SimTime total_idle_time = 0.0;
    int max_queue_length = 0;
    SimTime total_queue_wait_time = 0.0; // Sum of all waiting times
    
    double utilization() const {
        SimTime total_time = total_busy_time + total_idle_time;
        return total_time > 0 ? (total_busy_time / total_time) * 100.0 : 0.0;
    }
    
    double avg_queue_wait() const {
        return trucks_serviced > 0 ? total_queue_wait_time / trucks_serviced : 0.0;
    }
};

// Statistics tracking for trucks
struct TruckStats {
    int truck_id;
    int trips_completed = 0;
    SimTime total_mining_time = 0.0;
    SimTime total_travel_time = 0.0;
    SimTime total_unload_time = 0.0;
    SimTime total_queue_wait_time = 0.0;
    SimTime total_idle_time = 0.0;
    
    double utilization() const {
        SimTime active_time = total_mining_time + total_travel_time + total_unload_time;
        SimTime total_time = active_time + total_queue_wait_time + total_idle_time;
        return total_time > 0 ? (active_time / total_time) * 100.0 : 0.0;
    }
};

} //namespace
