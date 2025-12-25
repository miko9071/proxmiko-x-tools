cmake_minimum_required(VERSION 3.16)
project(ScrollLedApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔥 ВАЖНО ДЛЯ Qt (moc / uic / rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(ScrollLedApp
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/switchwidget.cpp
    src/switchwidget.h
    assets/resources.qrc
)

target_link_libraries(ScrollLedApp
    Qt6::Widgets
)
