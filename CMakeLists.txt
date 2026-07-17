cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(Swingers
    VERSION 0.1.0)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(PLATFORM Web CACHE INTERNAL "")
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/nonk123/raylib.git
    GIT_TAG 041148384a1ace990a7c890cc9e0ff608744e502
    EXCLUDE_FROM_ALL)

FetchContent_Declare(S_fixed
    GIT_REPOSITORY https://github.com/Schwungus/S_fixed.git
    GIT_TAG 74bd2c38527fbbecd46bff9c0b9efb2c186d59ef
    EXCLUDE_FROM_ALL)

FetchContent_Declare(NutBlast
    GIT_REPOSITORY https://github.com/Schwungus/NutBlast.git
    GIT_TAG 8a7a2ab2edc6e4779a2b0b344c7129aa07e47625
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
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11 cxx_std_23)

if(EMSCRIPTEN)
    target_link_options(${PROJECT_NAME}
        PRIVATE
            -sEXPORTED_RUNTIME_METHODS=HEAPF32,HEAPU32,HEAPU8,ccall
            --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@assets)
endif()
