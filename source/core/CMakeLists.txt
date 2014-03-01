add_library(core STATIC
			engine.h
			entity.h
			loader.h
			system.h

			engine.cpp
			entity.cpp
			loader.cpp
			)

target_link_libraries(core ${ASSIMP_LIBRARIES})
