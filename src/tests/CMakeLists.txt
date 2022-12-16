cmake_minimum_required(VERSION 3.5)
project(PhotoLab_test VERSION 1.0 LANGUAGES CXX)

#=============================================================== Setup CMake
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS --coverage)
# set(CMAKE_EXE_LINKER_FLAGS --coverage)

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

add_executable(
  ${PROJECT_NAME}
  test.cc
  ../model/model.cc
  ../model/model.h
)

qt_add_resources(${PROJECT_NAME} "img"
    PREFIX "/"
    BASE "../../misc/images"
    FILES
    ../../misc/images/sample.png
    ../../misc/images/sample-bw-average.png
    ../../misc/images/sample-negative.png
    ../../misc/images/sample-ebmoss.png
    ../../misc/images/sample-sharpen.png
    ../../misc/images/sample-box-blur.png
    ../../misc/images/sample-gaussian-blur.png
    ../../misc/images/sample-outline.png
    ../../misc/images/sample-sobel-left.png
    ../../misc/images/sample-sobel-right.png
    ../../misc/images/sample-sobel-left-and-right.png
    ../../misc/images/sample-outline.png
)

target_link_libraries(${PROJECT_NAME}
  Qt6::Core
  Qt6::Widgets
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
