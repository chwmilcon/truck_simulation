
all:	cmake
	@echo "All done"

cmake:	build
	cmake --build build

build:
	rm -rf build/
	cmake -S . -B build -G "Unix Makefiles"

clean:
	rm -rf build/
