cmake_minimum_required(VERSION 3.20)

project(LuaTest)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#the interpreter
set(INTERPRETER interpreter CACHE INTERNAL "The name of the cmake target")
add_executable(${INTERPRETER})
target_include_directories(${INTERPRETER} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Lua REQUIRED)
if(LUA_FOUND)
	target_link_libraries(${INTERPRETER} PRIVATE ${LUA_LIBRARIES})
	target_include_directories(${INTERPRETER} PRIVATE ${LUA_INCLUDE_DIR})
endif()

add_subdirectory(src)
