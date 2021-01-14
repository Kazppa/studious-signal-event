cmake_minimum_required(VERSION 3.17)
project(Event)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME} src/AbstractEvent.h src/Event.h src/Observer.h src/Observer.cpp src/main.cpp)