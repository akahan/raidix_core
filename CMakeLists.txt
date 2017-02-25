cmake_minimum_required(VERSION 3.2.0)

project(raidix_core)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-ferror-limit=100 -fspell-checking -Wunused-parameter -Wunreachable-code -Wall -std=c++11 -DBOOST_LOG_DYN_LINK")

set(BOOST_COMPONENTS system thread signals timer filesystem locale regex serialization log program_options)

set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_LIBS ON)

find_package (Threads)
find_package( Boost 1.60 REQUIRED COMPONENTS ${BOOST_COMPONENTS} )

add_subdirectory(src)
