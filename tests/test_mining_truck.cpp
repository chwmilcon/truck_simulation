#include "truck_simulation.hpp"
#include <gtest/gtest.h>

class MiningTruckTest : public ::testing::Test {
  protected:
    void SetUp() override {}
};

TEST(MiningTruckTest, Constructor) {
    Simulation::MiningTruck truck(1);
    EXPECT_EQ(truck.getId(), 1);
    EXPECT_EQ(truck.getState(), Simulation::TruckState::MINING);
    EXPECT_EQ(truck.getCurrentStation(), nullptr);
}

TEST(MiningTruckTest, SetState) {
    Simulation::MiningTruck truck(1);
    truck.setState(Simulation::TruckState::TRAVELING_TO_STATION);
    EXPECT_EQ(truck.getState(), Simulation::TruckState::TRAVELING_TO_STATION);
}

TEST(MiningTruckTest, SetCurrentStation) {
    Simulation::MiningTruck truck(1);
    auto station = std::make_shared<Simulation::UnloadStation>(1);
    truck.setCurrentStation(station);
    EXPECT_EQ(truck.getCurrentStation(), station);
}

TEST(MiningTruckTest, GetStats) {
    Simulation::MiningTruck truck(1);
    auto &stats = truck.getStats();
    EXPECT_EQ(stats.trips_completed, 0);
}

TEST(MiningTruckTest, QueueEntryTime) {
    Simulation::MiningTruck truck(1);
    truck.setQueueEntryTime(100.0);
    EXPECT_EQ(truck.getQueueEntryTime(), 100.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
