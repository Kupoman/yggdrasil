# SDL
if(MSVC)
	set(SDL_INCLUDE_DIRS ${WINDOWS_LIB_DIR}/sdl/include)
	set(SDL_LIBRARY_DIRS ${WINDOWS_LIB_DIR}/sdl/lib)
	set(SDL_LIBRARIES SDL2.lib SDL2main.lib SDL2test.lib)
else()
	find_package(SDL2 REQUIRED)
endif()
include_directories(${SDL_INCLUDE_DIRS})
link_directories(${SDL_LIBRARY_DIRS})

add_executable(yggdrasil main.cpp)
target_link_libraries(yggdrasil ${SDL_LIBRARIES})


# Copy DLLS
if(MSVC)
	add_custom_command(TARGET yggdrasil POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${WINDOWS_LIB_DIR}/sdl/lib/SDL2.dll"
		$<TARGET_FILE_DIR:yggdrasil>)
		
	add_custom_command(TARGET yggdrasil POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${WINDOWS_LIB_DIR}/assimp/lib/Assimp64.dll"
		$<TARGET_FILE_DIR:yggdrasil>)
endif()