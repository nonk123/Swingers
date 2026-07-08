cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(Swingers
    VERSION 0.1.0)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(PLATFORM Web CACHE INTERNAL "")
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    EXCLUDE_FROM_ALL)

FetchContent_Declare(S_fixed
    GIT_REPOSITORY https://github.com/Schwungus/S_fixed.git
    GIT_TAG 70b3044b3d758108828e2054683c21faf744b3de
    EXCLUDE_FROM_ALL)

FetchContent_Declare(NutBlast
    GIT_REPOSITORY https://github.com/Schwungus/NutBlast.git
    GIT_TAG 19633b12f4a66a11ef5578a1a225025e286c4045
    EXCLUDE_FROM_ALL)

FetchContent_MakeAvailable(raylib S_fixed NutBlast)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/cmake.hpp.in ${CMAKE_BINARY_DIR}/gen/cmake.hpp @ONLY)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_BINARY_DIR}/gen)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib S_fixed NutBlast)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    target_link_options(${PROJECT_NAME} PRIVATE -sASYNCIFY -sEXPORTED_RUNTIME_METHODS=HEAPF32,HEAPU32,HEAPU8)
endif()
