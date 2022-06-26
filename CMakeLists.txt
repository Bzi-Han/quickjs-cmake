cmake_minimum_required(VERSION 3.0)

project(libquickjs)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} /MT /GR- /utf-8")
add_definitions(-DUNICODE -D_UNICODE)

include_directories(quickjs)

set(SOURCES
	quickjs/quickjs.h
	quickjs/quickjs-libc.h
	quickjs/quickjs.c
	quickjs/libregexp.c
	quickjs/libunicode.c
	quickjs/cutils.c
	quickjs/quickjs-libc.c)

# build quickjs static library
add_library(quickjs STATIC ${SOURCES})

# build test program
add_executable(test test/main.cc)
target_link_libraries(test quickjs)