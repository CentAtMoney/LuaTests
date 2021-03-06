cmake_minimum_required(VERSION 3.22)

project(LuaTest)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# use a variable for the target name
set(INTERPRETER interpreter CACHE INTERNAL "The name of the cmake target")

set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(${INTERPRETER})
target_include_directories(${INTERPRETER} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${INTERPRETER} PRIVATE ${CMAKE_DL_LIBS})
#target_precompile_headers(${INTERPRETER} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/common.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${INTERPRETER} PRIVATE Threads::Threads)

find_package(Lua REQUIRED)
target_include_directories(${INTERPRETER} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${INTERPRETER} PRIVATE ${LUA_LIBRARIES})

find_package(GLFW3 REQUIRED)
target_include_directories(${INTERPRETER} PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(${INTERPRETER} PRIVATE ${GLFW3_LIBRARY})
target_compile_definitions(${INTERPRETER} PRIVATE GLFW_INCLUDE_NONE)

find_package(OpenGL REQUIRED)
target_link_libraries(${INTERPRETER} PRIVATE OpenGL::GL)

find_package(GLM REQUIRED)
target_link_libraries(${INTERPRETER} PRIVATE GLM::GLM)

add_subdirectory(src)
