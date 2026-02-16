#include "truck_simulation.hpp"
#include <gtest/gtest.h>

class EventTest : public ::testing::Test {
  protected:
    void SetUp() override {}
};

TEST(EventTest, Constructor) {
    auto truck = std::make_shared<Simulation::MiningTruck>(1);
    auto station = std::make_shared<Simulation::UnloadStation>(1);

    Simulation::Event event;
    event.time = 100.0;
    event.type = Simulation::EventType::MINING_COMPLETE;
    event.truck = truck;
    event.station = station;

    EXPECT_EQ(event.time, 100.0);
    EXPECT_EQ(event.type, Simulation::EventType::MINING_COMPLETE);
    EXPECT_EQ(event.truck, truck);
    EXPECT_EQ(event.station, station);
}

TEST(EventTest, EventTypes) {
    auto truck = std::make_shared<Simulation::MiningTruck>(1);
    auto station = std::make_shared<Simulation::UnloadStation>(1);

    Simulation::Event miningEvent;
    miningEvent.time = 100.0;
    miningEvent.type = Simulation::EventType::MINING_COMPLETE;
    miningEvent.truck = truck;

    Simulation::Event arriveEvent;
    arriveEvent.time = 200.0;
    arriveEvent.type = Simulation::EventType::ARRIVE_AT_STATION;
    arriveEvent.truck = truck;
    arriveEvent.station = station;

    Simulation::Event unloadEvent;
    unloadEvent.time = 300.0;
    unloadEvent.type = Simulation::EventType::UNLOAD_COMPLETE;
    unloadEvent.truck = truck;
    unloadEvent.station = station;

    EXPECT_EQ(miningEvent.type, Simulation::EventType::MINING_COMPLETE);
    EXPECT_EQ(arriveEvent.type, Simulation::EventType::ARRIVE_AT_STATION);
    EXPECT_EQ(unloadEvent.type, Simulation::EventType::UNLOAD_COMPLETE);
}

TEST(EventTest, OperatorGreater) {
    auto truck = std::make_shared<Simulation::MiningTruck>(1);

    Simulation::Event event1;
    event1.time = 100.0;
    event1.type = Simulation::EventType::MINING_COMPLETE;
    event1.truck = truck;

    Simulation::Event event2;
    event2.time = 200.0;
    event2.type = Simulation::EventType::ARRIVE_AT_STATION;
    event2.truck = truck;

    EXPECT_FALSE(event1 > event2);
    EXPECT_TRUE(event2 > event1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
