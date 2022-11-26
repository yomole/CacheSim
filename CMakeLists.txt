cmake_minimum_required(VERSION 3.15)
project(CacheSim)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/cachetypes)
include_directories(src/test)

set(MAIN src/main.cpp)
set(CACHEFILES
        src/cachetypes/parent/Cache.cpp
        src/cachetypes/parent/Cache.h
        src/cachetypes/FullyAssociative.h
        src/cachetypes/FullyAssociative.cpp
        src/tracehandler/Tracehandler.cpp
        src/tracehandler/Tracehandler.h
        src/cachePrint/cachePrint.h
        src/cachePrint/cachePrint.cpp src/cachetypes/SetAssociative.cpp src/cachetypes/SetAssociative.h src/help/help.h src/help/help.cpp)

set(TEST src/test/test.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(CacheSim ${CACHEFILES} ${MAIN})
target_link_options(CacheSim PRIVATE -static)