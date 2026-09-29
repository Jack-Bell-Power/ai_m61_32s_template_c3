cmake_minimum_required(VERSION 3.15)

find_package(bouffalo_sdk REQUIRED HINTS $ENV{BL_SDK_BASE})

sdk_set_main_file(src/main.c)

sdk_add_static_library(${CMAKE_CURRENT_SOURCE_DIR}/c3_out/librun.a)

project(ai_m61_32s_template)
