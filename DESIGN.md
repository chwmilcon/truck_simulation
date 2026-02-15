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

### 2.2. Truck state machine
* State: Mining
    * Event: Travel -> Traveling to Station
    * Event: Complete -> Traveling to Mine
* State: Traveling to station
    * Event: Travel 30 min -> Arrive at station
* State: Arrive at station
    * Event: Station Busy -> Queue
    * Event: Station not busy -> Unload
* State: Queue
    * Event: Station not busy -> Unload
* State: Unload
    * Event: Unload -> Travel to mine
*State: Travel to mine
    * Event: Travel -> Minining

**Statistics**
* Trips completed
* Time in each state
* Utilization

### 2.3 Unload Station Model
**Queue Management:**

* FIFO queue
* Trucks commit to selected queue

**States:**

* **Idle**
* **Busy**

**Statistics**

* Trucks serviced
* Busy vs idle time
* Maximum queue length observed
* Average queue wait time
* Utilization

### 2.4 Station Selection Algorithm

The strategy selects an unload station using a two-tier prioritization system:
* **First priority:** It always prefers idle stations over busy
  ones. If any station is currently idle (not processing a truck), it
  will be chosen over all busy stations. 
* **Second priority:** When comparing stations of the same status
  (both idle or both busy), it selects the one with the shortest
  queue—meaning the fewest trucks waiting in line. 
