#pragma once
// Time representation in minutes for the simulation
using SimTime = double;
using Clock = std::chrono::steady_clock;

// Constants
constexpr SimTime MINING_TIME_MIN = 60.0;      // 1 hour in minutes
constexpr SimTime MINING_TIME_MAX = 300.0;     // 5 hours in minutes
constexpr SimTime TRAVEL_TIME = 30.0;          // 30 minutes
constexpr SimTime UNLOAD_TIME = 5.0;           // 5 minutes
constexpr SimTime SIMULATION_DURATION = 4320.0; // 72 hours in minutes
