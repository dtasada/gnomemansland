cmake_minimum_required(VERSION 3.31)

project(po6)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

file(GLOB CLIENT_FILES client/src/*.cpp)
file(GLOB SERVER_FILES server/src/*.cpp)

# Define source files for each target
set(CLIENT_SRC ${CLIENT_FILES})
set(SERVER_SRC ${SERVER_FILES})

# Add executables
add_executable(client ${CLIENT_SRC})
add_executable(server ${SERVER_SRC})

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_NET REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SQLITE3_INCLUDE_DIRS})

if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()

include(FetchContent)
FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG master
)

FetchContent_MakeAvailable(sqlite_orm)
target_include_directories(server PRIVATE ${sqlite_orm_SOURCE_DIR}/include)

target_link_libraries(client
	SDL2::SDL2
	SDL2::SDL2main
	SDL2_image::SDL2_image
	SDL2_net::SDL2_net
	SQLite::SQLite3
)
target_link_libraries(server
	SDL2::SDL2
	SDL2::SDL2main
	SDL2_image::SDL2_image
	SDL2_net::SDL2_net
	SQLite::SQLite3
)

add_custom_target(build-client
    DEPENDS client
	WORKING_DIRECTORY $CWD
    COMMENT "Running the client executables"
)

add_custom_target(build-server
    DEPENDS server
	WORKING_DIRECTORY $CWD
    COMMENT "Running the server executables"
)
