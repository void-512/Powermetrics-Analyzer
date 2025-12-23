cmake_minimum_required(VERSION 3.20)
project(powermetricsTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ABSL_USE_GOOGLETEST OFF CACHE BOOL "" FORCE)
set(ABSL_ENABLE_INSTALL ON CACHE BOOL "" FORCE)
add_subdirectory(deps-src/abseil-cpp absl-build)

set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(deps-src/re2 re2-build)

file(GLOB SRCS CONFIGURE_DEPENDS *.cpp *.hpp)

add_executable(app ${SRCS})

target_include_directories(app PRIVATE
    ${PROJECT_SOURCE_DIR}
    deps-src/abseil-cpp
    deps-src/re2
)

target_link_libraries(app PRIVATE re2)
