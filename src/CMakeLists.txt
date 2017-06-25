cmake_minimum_required(VERSION 2.8)

project(cie_plot_launcher)

#set(LAUNCHER ${PROJECT_NAME} )

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DLIB_COMPILE)

include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/utils/googletest/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/src_avis_plot)

set(SOURCE 
	main.cpp
)

add_executable( ${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} avis_plot)

set_target_properties( ${PROJECT_NAME} PROPERTIES
					RUNTIME_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_DEBUG ${G_BIN_DIR}
					RUNTIME_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					LIBRARY_OUTPUT_DIRECTORY_RELEASE ${G_BIN_DIR}
					)
					

#endif( ${ENABLE_TESTING} )					