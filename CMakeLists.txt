cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  SimpleCxxLib
  VERSION 0.1
  DESCRIPTION "A Simple C++ Library for Introductory CS"
  LANGUAGES CXX)

# Add a library target
add_library(${PROJECT_NAME} STATIC)

# Define Cxx standard
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

# Determines the thread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Add source files
file(
  GLOB_RECURSE
  SOURCE_FILES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/collections/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/console/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/io/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/system/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/testing/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.cpp)
file(
  GLOB_RECURSE
  HEADER_FILES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/collections/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/console/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/io/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/system/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/testing/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/util/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/private/include/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

# Add include directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/collections/include
         ${CMAKE_CURRENT_SOURCE_DIR}/console/include
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include
         ${CMAKE_CURRENT_SOURCE_DIR}/io/include
         ${CMAKE_CURRENT_SOURCE_DIR}/system/include
         ${CMAKE_CURRENT_SOURCE_DIR}/testing/include
         ${CMAKE_CURRENT_SOURCE_DIR}/util/include
  PRIVITE
         ${CMAKE_CURRENT_SOURCE_DIR}/private/include)

# Configuration for testing
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(examples)
endif()

# Build Java backend
add_subdirectory(java)
add_dependencies(${PROJECT_NAME} JavaBackEnd)
