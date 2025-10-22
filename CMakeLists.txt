cmake_minimum_required(VERSION 3.30)

project(ckanji)
find_package(Curses REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(inc)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} 
                src/main.cpp
                src/menu_state.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})