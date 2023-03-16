cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  TestingForSimpleCxxLib
  VERSION 1.0
  DESCRIPTION "Program to test SimpleCxxLib"
  LANGUAGES CXX)

# Add an executable target
add_executable(${PROJECT_NAME}
    TestVectorClass.cpp
    TestSetClass.cpp)

# Define Cxx standard
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://gitee.com/tjopenlab/Catch2.git
  GIT_TAG v3.3.2)
FetchContent_MakeAvailable(Catch2)

# Add libraries
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE Catch2::Catch2WithMain # Add Catch2
          SimpleCxxLib # Add SimpleCxxLib
)

add_test(NAME TestingForSimpleCxxLib COMMAND ${PROJECT_NAME})
