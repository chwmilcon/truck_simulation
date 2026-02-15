#include <gtest/gtest.h>
#include "truck_simulation.hpp"

class SimulationTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST(SimulationTest, Balanced) {
    Truck_simulation sim(10, 5, 42);
    sim.run();
}

TEST(SimulationTest, Bottleneck) {
    Truck_simulation sim(20, 2, 42);
    sim.run();
}

TEST(SimulationTest, Excess) {
    Truck_simulation sim(5, 10, 42);
    sim.run();
}

TEST(SimulationTest, Large) {
    Truck_simulation sim(100, 20, 42);
    sim.run();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
