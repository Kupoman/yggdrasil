include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_library(module_assimploader STATIC
			assimploader.h

			assimploader.cpp
			)

