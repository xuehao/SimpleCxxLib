cmake_minimum_required(VERSION 3.20)

find_package(Java COMPONENTS Development REQUIRED)
include(UseJava)

set(CMAKE_JAVA_COMPILE_FLAGS -Xlint:-serial)
set(JAVA_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/G3DRect.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GArc.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GCanvas.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GCompound.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GContainer.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GDimension.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GFillable.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GImage.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GImageTools.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GLabel.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GLine.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GMath.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GObject.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GOval.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GPoint.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GPolygon.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GRect.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GRectangle.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GResizable.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GRoundRect.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GScalable.java
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/GWindow.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GButton.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GCheckBox.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GChooser.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GInteractor.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GSlider.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/GTextField.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBECanvas.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBECommand.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBEConsole.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBEFileFilter.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBELabel.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBETopCompound.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JBEWindow.java
    ${CMAKE_CURRENT_SOURCE_DIR}/spl/JavaBackEnd.java
    ${CMAKE_CURRENT_SOURCE_DIR}/tokenscanner/TokenScanner.java)

add_jar(
  JavaBackEnd ${JAVA_SOURCE_FILES}
  ENTRY_POINT spl.JavaBackEnd
  OUTPUT_NAME spl)
