#include "truck_simulation.hpp"
#include <gtest/gtest.h>

class UnloadStationTest : public ::testing::Test {
  protected:
    void SetUp() override {}
};

TEST(UnloadStationTest, Constructor) {
    Simulation::UnloadStation station(1);
    EXPECT_EQ(station.getId(), 1);
    EXPECT_FALSE(station.isBusy());
    EXPECT_EQ(station.getCurrentTruck(), nullptr);
    EXPECT_EQ(station.getQueueLength(), 0);
}

TEST(UnloadStationTest, SetBusy) {
    Simulation::UnloadStation station(1);
    station.setBusy(true);
    EXPECT_TRUE(station.isBusy());
    station.setBusy(false);
    EXPECT_FALSE(station.isBusy());
}

TEST(UnloadStationTest, SetCurrentTruck) {
    Simulation::UnloadStation station(1);
    auto truck = std::make_shared<Simulation::MiningTruck>(1);
    station.setCurrentTruck(truck);
    EXPECT_EQ(station.getCurrentTruck(), truck);
}

TEST(UnloadStationTest, AddToQueue) {
    Simulation::UnloadStation station(1);
    auto truck1 = std::make_shared<Simulation::MiningTruck>(1);
    auto truck2 = std::make_shared<Simulation::MiningTruck>(2);

    station.addToQueue(truck1);
    EXPECT_EQ(station.getQueueLength(), 1);

    station.addToQueue(truck2);
    EXPECT_EQ(station.getQueueLength(), 2);

    EXPECT_EQ(station.getStats().max_queue_length, 2);
}

TEST(UnloadStationTest, PopFromQueue) {
    Simulation::UnloadStation station(1);
    auto truck1 = std::make_shared<Simulation::MiningTruck>(1);
    auto truck2 = std::make_shared<Simulation::MiningTruck>(2);

    station.addToQueue(truck1);
    station.addToQueue(truck2);

    auto popped = station.popFromQueue();
    EXPECT_TRUE(popped.has_value());
    EXPECT_EQ(popped.value(), truck1);
    EXPECT_EQ(station.getQueueLength(), 1);
}

TEST(UnloadStationTest, PopFromEmptyQueue) {
    Simulation::UnloadStation station(1);
    auto popped = station.popFromQueue();
    EXPECT_FALSE(popped.has_value());
}

TEST(UnloadStationTest, IdleStartTime) {
    Simulation::UnloadStation station(1);
    station.setIdleStartTime(100.0);
    EXPECT_EQ(station.getIdleStartTime(), 100.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
