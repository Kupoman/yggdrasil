include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(yggdrasil main.cpp)
target_link_libraries(yggdrasil core nameexample ${SDL2_LIBRARIES})

# Copy DLLS
if(MSVC)
	add_custom_command(TARGET yggdrasil POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${SDL_LIBRARY_DIRS}/SDL2.dll"
		$<TARGET_FILE_DIR:yggdrasil>)
		
	add_custom_command(TARGET yggdrasil POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${ASSIMP_LIBRARY_DIRS}/Assimp64.dll"
		$<TARGET_FILE_DIR:yggdrasil>)
endif()
