SDK_DEMO_PATH ?= $(abspath .)
BL_SDK_BASE ?= $(abspath  ./../..)

export BL_SDK_BASE

CHIP ?= bl616
BOARD ?= bl616dk

include $(BL_SDK_BASE)/project.build

.PHONY: run_c3c_build

run_c3c_build:
	c3c build

build: run_c3c_build

clean_all:
	$(MAKE) clean
	$(BL_SDK_BASE)/tools/cmake/bin/cmake.exe -E remove_directory "c3_out"
