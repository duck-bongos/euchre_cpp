cmake_minimum_required(VERSION 3.6)
project(Euchre)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "-fpermissive -std=c++17")
    set(CMAKE_BUILD_TYPE DEBUG)
endif(NOT MSVC)

if(APPLE)
  add_definitions(-DMAC_OS)
endif(APPLE)

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Include the 'include' of the project itself
include_directories(
  "${CMAKE_SOURCE_DIR}/include"
)

include_directories(
  "${CMAKE_SOURCE_DIR}/include/core" 
  "${CMAKE_SOURCE_DIR}/include/3rdParty/mongocxx/"
)

# Also, the file(GLOB...) allows for wildcard additions
file(GLOB SRCS
    "include/*.h"
    "src/*.cpp"
    "src/*.cc")

# Add an executablee target called euchre
add_executable(euchre src/main.cc)

# Install the executeable program in the bin folder of the
# current project directory.
add_custom_command(
    TARGET euchre
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E 
    copy $<TARGET_FILE:euchre> ${CMAKE_SOURCE_DIR}/bin
  )