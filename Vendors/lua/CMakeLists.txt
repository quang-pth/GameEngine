project(lua)

### lua
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_USE_WINDOWS)
endif()

if (UNIX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_USE_LINUX)
  target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()
