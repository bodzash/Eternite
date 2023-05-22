cmake_minimum_required(VERSION 3.26)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ApexGameEngine)

# Common output for exe and dll files NOTE: temporary
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

# Define sub-projects
add_subdirectory(Engine)
add_subdirectory(Runtime)
#add_subdirectory(Editor)