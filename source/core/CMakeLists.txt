add_library(core STATIC
			engine.cpp
			loader.cpp
			)

target_link_libraries(core ${ASSIMP_LIBRARIES})