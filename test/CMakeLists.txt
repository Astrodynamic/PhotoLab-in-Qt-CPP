cmake_minimum_required(VERSION 3.15)
project(TEST VERSION 1.0 LANGUAGES CXX)

# =============================================================== Setup CMake
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Qt6 REQUIRED COMPONENTS
  Core
  Widgets
)

include_directories(
  ${PROJECT_SOURCE_DIR}/../model
)

enable_testing()

set(HEADERS
  ${PROJECT_SOURCE_DIR}/../model/model.h
)

set(SOURSES
  ${PROJECT_SOURCE_DIR}/../model/model.cc
)

add_executable(
  ${PROJECT_NAME}
  ${HEADERS}
  ${SOURSES}
  ${PROJECT_SOURCE_DIR}/tests.cc
)

qt_add_resources(${PROJECT_NAME} "img"
  PREFIX "/"
  BASE "../data/img"
  FILES
  ../data/img/sample.png
  ../data/img/sample-bw-average.png
  ../data/img/sample-negative.png
  ../data/img/sample-ebmoss.png
  ../data/img/sample-sharpen.png
  ../data/img/sample-box-blur.png
  ../data/img/sample-gaussian-blur.png
  ../data/img/sample-outline.png
  ../data/img/sample-sobel-left.png
  ../data/img/sample-sobel-right.png
  ../data/img/sample-sobel-left-and-right.png
  ../data/img/sample-outline.png
)

target_link_libraries(${PROJECT_NAME}
  Qt6::Core
  Qt6::Widgets
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
