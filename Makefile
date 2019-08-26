help:
	@echo "Usage:"
	@echo "	make help"
	@echo "	make tests"
	@echo "	make doc"
	@echo "	make debug"
	@echo "	make paranoid"
	@echo "	make coverage"
	@echo "	make clean"
doc:
	rm -rf docs
	if hash doxygen 2>/dev/null; then doxygen; fi
external:
	git submodule update --init
build:
	mkdir -p build
tests: 	external build
	cd build && cmake .. -DBUILD_TESTING=ON
	cmake --build ./build -- -j4
	cd build && ctest
paranoid: external build
	cd build && cmake .. -DBUILD_TESTING=ON -DPARANOID_WARNINGS=ON
	cmake --build ./build -- -j4
debug: external build
	cd build && cmake .. -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE="Debug"
	cmake --build ./build -- -j4
coverage:	external build doc
	cd build && cmake .. -DCODE_COVERAGE=ON -DBUILD_TESTING=ON
	cmake --build ./build -- -j4
	cd build && ctest
	if [ -f "./.ci/coverage-report.sh" ]; then ./.ci/coverage-report.sh docs/html/cov-report ; fi
clean:
	rm -rf docs
	cd build && make clean
