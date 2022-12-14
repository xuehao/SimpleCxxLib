cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  SimpleCxxLib
  VERSION 0.1
  DESCRIPTION "A Simple C++ Library for Introductory CS"
  LANGUAGES CXX)

# Add a library target
add_library(${PROJECT_NAME})

# Define Cxx standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Determines the thread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Add source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

# Add include directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/private)

# Build Java backend (depends on jdk8 and linux tools)
# add_dependencies(${PROJECT_NAME} JavaBackend)
# add_custom_target(
#   JavaBackend
#   COMMAND make
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/java)
