cmake_minimum_required(VERSION 2.8)
project(yggdrasil)

set(WINDOWS_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

# SDL
if(MSVC)
	set(SDL_2_INCLUDE_DIRS ${WINDOWS_LIB_DIR}/sdl/include)
	set(SDL_LIBRARY_DIRS ${WINDOWS_LIB_DIR}/sdl/lib)
	set(SDL2_LIBRARIES SDL2.lib SDL2main.lib SDL2test.lib)
else()
	include(FindPkgConfig)
	pkg_search_module(SDL2 REQUIRED sdl2)
endif()
include_directories(${SDL_2_INCLUDE_DIRS})
link_directories(${SDL_LIBRARY_DIRS})

# Assimp
if(MSVC)
	set(ASSIMP_INCLUDE_DIRS ${WINDOWS_LIB_DIR}/assimp/include)
	set(ASSIMP_LIBRARY_DIRS ${WINDOWS_LIB_DIR}/assimp/lib)
	set(ASSIMP_LIBRARIES assimp.lib)
else()
	find_package(ASSIMP REQUIRED)
endif()
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})

add_subdirectory(source)
