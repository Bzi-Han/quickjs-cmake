cmake_minimum_required(VERSION 3.12.0)

project(libquickjs)

cmake_policy(SET CMP0077 NEW)

option(QUICKJS_BUILD_TEST "Build test program." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} /MT /GR- /utf-8")
add_definitions(-DUNICODE -D_UNICODE -D_UCRT_NOISY_NAN)

include_directories(quickjs)

set(SOURCES
	quickjs/quickjs.h
	quickjs/quickjs-libc.h
	quickjs/quickjs.c
	quickjs/libregexp.c
	quickjs/libunicode.c
	quickjs/cutils.c
	quickjs/quickjs-libc.c)

# Build quickjs static library
add_library(quickjs STATIC ${SOURCES})

# Build test program
if(QUICKJS_BUILD_TEST)
	add_executable(quickjs-test test/main.cc)
	target_link_libraries(quickjs-test quickjs)
endif()