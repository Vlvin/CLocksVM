cmake_minimum_required(VERSION 3.11 FATAL_ERROR)


project(CLocksCompiler)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(DEBUG_PRINT_CODE)
    add_compile_definitions(DEBUG_TRACE)
    # add_compile_definitions(NDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -01")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -03")
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES 
    ${SRC}/bitsTricks.c
    ${SRC}/debug.c
    ${SRC}/loxChunk.c
    ${SRC}/loxObject.c
    ${SRC}/loxCLI.c
    ${SRC}/loxCompiler.c
    ${SRC}/loxErrors.c
    ${SRC}/loxLineTracker.c
    ${SRC}/loxHashMap.c
    ${SRC}/loxMemory.c
    ${SRC}/loxParser.c
    ${SRC}/loxScanner.c
    ${SRC}/loxStack.c
    ${SRC}/loxToken.c
    ${SRC}/loxValue.c
    ${SRC}/loxValueArray.c
    ${SRC}/loxVM.c
)

add_library("${PROJECT_NAME}_SRC" ${SOURCES})
target_include_directories("${PROJECT_NAME}_SRC" PUBLIC ${INCLUDE_DIRS})


add_executable(hash-bench test/hash_map_bench.c)
target_include_directories(hash-bench PRIVATE ${INCLUDE_DIRS})
target_link_libraries(hash-bench "${PROJECT_NAME}_SRC")
add_test(NAME hash-bench COMMAND hash-bench)

# Enable testing
enable_testing()

add_executable(${PROJECT_NAME} ${SRC}/main.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_SRC")
