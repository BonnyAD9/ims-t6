BUILD_TYPE=Debug
PARALEL=-j $(shell nproc)
IMS_T6=src/*.cpp # src/*.hpp src/**/*.cpp src/**/*.hpp
ALL=$(IMS_T6)

.PHONY: all
all: build doc

.PHONY: build
build:
	if [ ! -f build/Makefile ]; then \
		mkdir build; \
		cd build \
			&& cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE); \
	fi
	cd build && $(MAKE) $(PARALEL)

.PHONY: run
run: build
	build/ims-t6

.PHONY: fmt
fmt:
	clang-format -i $(ALL)

.PHONY: cppcheck
cppcheck:
	cppcheck --check-level=exhaustive $(ALL)

.PHONY: tidy
tidy: build
	run-clang-tidy $(PARALEL) -use-color -quiet -p build \
		-header-filter=src/ 'src/.*\.cpp' 'src/.*\.hpp'

.PHONY: check
check: fmt cppcheck tidy

.PHONY: clean
clean:
	-cd build && $(MAKE) clean
	cd doc && $(MAKE) clean
