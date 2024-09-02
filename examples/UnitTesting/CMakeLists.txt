cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  UnitTesting
  VERSION 1.0
  DESCRIPTION "SimpleCxxLib Unit Testing"
  LANGUAGES CXX)

# Add an executable target
add_executable(${PROJECT_NAME})

# Define Cxx standard
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

# Add source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

# Add libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SimpleCxxLib)

# Copy dependency
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy ${SimpleCxxLib_BINARY_DIR}/java/spl.jar
          ${CMAKE_CURRENT_BINARY_DIR})

# Copy res files for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/TestTokenScannerClass.cpp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
