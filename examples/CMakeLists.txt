cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  Examples
  VERSION 1.0
  DESCRIPTION "Examples using SimpleCxxLib"
  LANGUAGES CXX)

# Add subdirectory
add_subdirectory(UnitTesting)
add_subdirectory(GraphicExample)
add_subdirectory(GHelloWorld)
add_subdirectory(DrawDiagonals)
add_subdirectory(DrawLines)
add_subdirectory(DrawRectangles)
add_subdirectory(Flower)
add_subdirectory(PacMan)
add_subdirectory(Snowflake)
add_subdirectory(Stoplight)
add_subdirectory(USFlag)
