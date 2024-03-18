project(VIMemory VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_MEMORY DYNAMIC_BUILD)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlogd)
target_include_directories(${PROJECT_NAME} 
	PRIVATE ${CMAKE_SOURCE_DIR}/Vendors/include/spdlog
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
