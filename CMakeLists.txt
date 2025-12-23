cmake_minimum_required(VERSION 3.20)
project(PowermetricsTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ABSL_USE_GOOGLETEST OFF)
set(ABSL_ENABLE_INSTALL ON)
add_subdirectory(deps/abseil-cpp absl-build)

set(RE2_BUILD_TESTING OFF)
add_subdirectory(deps/re2 re2-build)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_executable(app ${SRCS} ${HEADERS})

target_include_directories(app PRIVATE
    include
    deps/abseil-cpp
    deps/re2
)

target_link_libraries(app PRIVATE re2)
