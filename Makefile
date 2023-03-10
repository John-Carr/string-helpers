SHELL := /bin/bash

all:
	cmake -S. -Bbuild
	cmake --build build

run-test:
	cd build && ctest && cd ..

gen-cov:
	cd build && lcov -c --directory . --output-file main_coverage.info && genhtml main_coverage.info --output-directory code-cov && cd ..

clean:
	rm -rf build
