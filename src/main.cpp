#include <iostream>
#include "truck_simulation.hpp"

/**
 * @brief print out the usage for the simulator
 *
 * @param program_name - argv[0] from main
 */
void printUsage(const char* program_name) {
    std::cout << "Usage: " << program_name << " <num_trucks> <num_stations> [seed]\n";
    std::cout << "  num_trucks  : Number of mining trucks (positive integer)\n";
    std::cout << "  num_stations: Number of unload stations (positive integer)\n";
    std::cout << "  seed        : Random seed (optional, default: 42)\n";
    std::cout << "\nExample: " << program_name << " 10 3\n";
    std::cout << "         " << program_name << " 20 5 12345\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc < 3 || argc > 4) {
            printUsage(argv[0]);
            return 1;
        }

        int num_trucks = std::stoi(argv[1]);
        int num_stations = std::stoi(argv[2]);
        unsigned int seed = 42;

        if (argc == 4) {
            seed = static_cast<unsigned int>(std::stoi(argv[3]));
        }

        if (num_trucks <= 0) {
            std::cerr << "Error: Number of trucks must be positive\n";
            return 1;
        }

        if (num_stations <= 0) {
            std::cerr << "Error: Number of stations must be positive\n";
            return 1;
        }
        Simulation::Truck_simulation sim(num_trucks, num_stations, seed);
        sim.run();
        sim.printStatistics();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid argument - " << e.what() << "\n";
        printUsage(argv[0]);
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Number out of range - " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
