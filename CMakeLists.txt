cmake_minimum_required(VERSION 3.31)

project(PO6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++23 -Wall -Wextra -O3 ")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
FILE(GLOB SRC src/*.cpp)
set(SOURCES ${SRC})

add_executable(po6 ${SOURCES})

find_package(SDL2)

if(SDL2_FOUND)
	message("SDL2 Found")
	include_directories(${SDL2_INCLUDE_DIRS})
	target_link_libraries(po6 ${SDL2_LIBRARIES})
elseif(NOT Boost_FOUND)
	error("SDL2 Not Found")
endif()
