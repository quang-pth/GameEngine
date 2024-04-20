project(VIEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} 
	PUBLIC
		ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0 
		_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING # TODO: Remove this macro when spdlog is update
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/VIEngine
	${CMAKE_SOURCE_DIR}/Vendors/include
	${CMAKE_SOURCE_DIR}/Vendors/glfw/include
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlogd glfw)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/pch.h ${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h)
