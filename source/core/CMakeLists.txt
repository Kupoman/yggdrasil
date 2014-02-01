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

add_library(core STATIC
			engine.cpp
			loader.cpp
			)

target_link_libraries(core ${ASSIMP_LIBRARIES})