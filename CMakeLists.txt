cmake_minimum_required(VERSION 3.14)

project(HomeWOrk38_1_QT)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Core Widgets WebEngineWidgets Multimedia MultimediaWidgets REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::WebEngineCore Qt5::WebEngineWidgets Qt5::Multimedia Qt5::MultimediaWidgets)
