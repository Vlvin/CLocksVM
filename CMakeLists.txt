cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


project(CLocksCompiler)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(DEBUG_TRACE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES 
    ${SRC}/loxChunk.c
    ${SRC}/loxMemory.c
    ${SRC}/loxVM.c
    ${SRC}/bitsTricks.c
    ${SRC}/loxStack.c
    ${SRC}/lineTracker.c
    ${SRC}/loxValue.c
    ${SRC}/debug.c
)

add_library("${PROJECT_NAME}_SRC" ${SOURCES})
target_include_directories("${PROJECT_NAME}_SRC" PUBLIC ${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC}/main.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_SRC")