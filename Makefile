SHELL := /bin/bash

all:
	cmake -S. -Bbuild
	cmake --build build

run-test:
	cd build && ctest && cd ..

clean:
	rm -rf build