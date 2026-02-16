
all:	cmake
	@echo "All done"

cmake:	build
	cmake --build build

build:
	rm -rf build/
	cmake -S . -B build -G "Unix Makefiles"

test:	cmake
	build/simulation_test
	build/test_event
	build/test_mining_truck
	build/test_station_stats
	build/test_truck_stats
	build/test_unload_station

clean:
	rm -rf build/
