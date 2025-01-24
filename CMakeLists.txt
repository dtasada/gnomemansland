cmake_minimum_required(VERSION 3.31)

project(po6)
set(CMAKE_CXX_STANDARD 23)
if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "GNU CXX detected, adding compile flags")
	add_compile_options(-Wall -Wextra -O3)
endif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE CLIENT_FILES client/src/*.cpp)
file(GLOB_RECURSE SERVER_FILES server/src/*.cpp)

# Define source files for each target
set(CLIENT_SRC ${CLIENT_FILES})
set(SERVER_SRC ${SERVER_FILES})

# Add executables
add_executable(client ${CLIENT_SRC})
add_executable(server ${SERVER_SRC})

if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()

include(FetchContent)

FetchContent_Declare(SDL2		GIT_REPOSITORY https://github.com/libsdl-org/SDL		GIT_TAG release-2.30.11)
FetchContent_Declare(SDL2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image	GIT_TAG release-2.8.4)
FetchContent_Declare(SDL2_net	GIT_REPOSITORY https://github.com/libsdl-org/SDL_net	GIT_TAG release-2.2.0)
FetchContent_Declare(json		GIT_REPOSITORY https://github.com/nlohmann/json			GIT_TAG v3.11.3)
FetchContent_Declare(toml		GIT_REPOSITORY https://github.com/marzer/tomlplusplus	GIT_TAG v3.4.0)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_net json toml)

foreach(TARGET client server)
	target_include_directories(${TARGET} PRIVATE
		${SDL2_INCLUDE_DIR}
		${SDL2_image_INCLUDE_DIR}
		${SDL2_net_INCLUDE_DIR}
		${json_SOURCE_DIR}/include
		${toml_SOURCE_DIR}/include
	)

	target_link_libraries(${TARGET}
		SDL2::SDL2
		SDL2::SDL2main
		SDL2_image::SDL2_image
		SDL2_net::SDL2_net
		${json_LIBRARIES}
	)
endforeach()
