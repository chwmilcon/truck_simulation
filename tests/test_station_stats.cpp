#include "truck_simulation.hpp"
#include <gtest/gtest.h>

class StationStatsTest : public ::testing::Test {
  protected:
    void SetUp() override {}
};

TEST(StationStatsTest, Constructor) {
    Simulation::StationStats stats;
    stats.station_id = 1;
    EXPECT_EQ(stats.station_id, 1);
    EXPECT_EQ(stats.trucks_serviced, 0);
    EXPECT_EQ(stats.total_busy_time, 0.0);
    EXPECT_EQ(stats.total_idle_time, 0.0);
    EXPECT_EQ(stats.max_queue_length, 0);
    EXPECT_EQ(stats.total_queue_wait_time, 0.0);
}

TEST(StationStatsTest, Utilization) {
    Simulation::StationStats stats;
    stats.station_id = 1;
    stats.total_busy_time = 50.0;
    stats.total_idle_time = 50.0;
    EXPECT_DOUBLE_EQ(stats.utilization(), 50.0);
}

TEST(StationStatsTest, UtilizationWithZeroTime) {
    Simulation::StationStats stats;
    stats.station_id = 1;
    EXPECT_DOUBLE_EQ(stats.utilization(), 0.0);
}

TEST(StationStatsTest, AvgQueueWait) {
    Simulation::StationStats stats;
    stats.station_id = 1;
    stats.trucks_serviced = 4;
    stats.total_queue_wait_time = 200.0;
    EXPECT_DOUBLE_EQ(stats.avg_queue_wait(), 50.0);
}

TEST(StationStatsTest, AvgQueueWaitWithZeroServiced) {
    Simulation::StationStats stats;
    stats.station_id = 1;
    EXPECT_DOUBLE_EQ(stats.avg_queue_wait(), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
