cmake_minimum_required(VERSION 3.5)
project (HashTable VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Test target ===

# Add test files.
file(GLOB SOURCES_TEST "test/*.cpp")
#add_executable(hash ${SOURCES_TEST})
add_executable(hash "test/main.cpp" )

# Link with the google test libraries.
target_link_libraries(hash PRIVATE ${GTEST_LIBRARIES} PRIVATE pthread )