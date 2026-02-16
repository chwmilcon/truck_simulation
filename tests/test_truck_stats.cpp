#include "truck_simulation.hpp"
#include <gtest/gtest.h>

class TruckStatsTest : public ::testing::Test {
  protected:
    void SetUp() override {}
};

TEST(TruckStatsTest, Constructor) {
    Simulation::TruckStats stats;
    stats.truck_id = 1;
    EXPECT_EQ(stats.truck_id, 1);
    EXPECT_EQ(stats.trips_completed, 0);
    EXPECT_EQ(stats.total_mining_time, 0.0);
    EXPECT_EQ(stats.total_travel_time, 0.0);
    EXPECT_EQ(stats.total_unload_time, 0.0);
    EXPECT_EQ(stats.total_queue_wait_time, 0.0);
    EXPECT_EQ(stats.total_idle_time, 0.0);
}

TEST(TruckStatsTest, Utilization) {
    Simulation::TruckStats stats;
    stats.truck_id = 1;
    stats.total_mining_time = 100.0;
    stats.total_travel_time = 50.0;
    stats.total_unload_time = 25.0;
    stats.total_queue_wait_time = 10.0;
    stats.total_idle_time = 15.0;
    double expected = (175.0 / 200.0) * 100.0;
    EXPECT_DOUBLE_EQ(stats.utilization(), expected);
}

TEST(TruckStatsTest, UtilizationWithZeroTotalTime) {
    Simulation::TruckStats stats;
    stats.truck_id = 1;
    EXPECT_DOUBLE_EQ(stats.utilization(), 0.0);
}

TEST(TruckStatsTest, UtilizationWithOnlyActiveTime) {
    Simulation::TruckStats stats;
    stats.truck_id = 1;
    stats.total_mining_time = 100.0;
    stats.total_travel_time = 50.0;
    stats.total_unload_time = 25.0;
    double expected = (175.0 / 175.0) * 100.0;
    EXPECT_DOUBLE_EQ(stats.utilization(), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
