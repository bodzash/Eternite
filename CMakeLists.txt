# Set CMake standard
cmake_minimum_required(VERSION 3.26)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# State project
project(ApexGameEngine)

# Define sub-projects
add_subdirectory(Engine)
add_subdirectory(GameClient)
add_subdirectory(GameServer)