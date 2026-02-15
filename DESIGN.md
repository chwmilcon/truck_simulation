## Executive Summary

The project requires a simulation in C++23 that models Helium-3 mining on the
moon. It needs to run through 72 hours of mining operations fast and keep track
of how well the mining trucks and unload stations are performing.

## 1. Architecture Overview

### 1.1 Core Design Pattern

The core design uses a Discrete Event Simulation (DES) pattern, which was chosen
for several key reasons. DES is time-efficient because it only uses CPU
cycles when something actually happens, rather than constantly checking
everything. It's also really accurate since it handles event timing precisely
without running into floating-point drift issues. The pattern scales well,
it can handle thousands of entities without much overhead.

### 1.2 System Components
* Priority Queue: Events ordered by time
* Trucks (n)
* Stations (m)
* Event handler
* Stats collectors
  * Utilization
  * Queue times
  * Through put

## 2. Detailed design
### 2.1 Event system
* Events
  * complete
  * arrive
  * unloaded
* Event
  * time
  * event type
  * truck
  * station
* Queue
  * Use a `std::priority_queue`
  * Ordered by event time (earliest first)
  * Ensure deterministic event processing ordering
