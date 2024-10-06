cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


project(CLocksCompiler)



set(SRC ${PROJECT_SOURCE_DIR}/src)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES 

)

# if ("${SOURCES}" NOT EQUAL "")
#     add_library("${PROJECT_NAME}_SRC" SOURCES)
# endif("${SOURCES}" NOT EQUAL "")

add_executable(${PROJECT_NAME} ${SRC}/main.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})