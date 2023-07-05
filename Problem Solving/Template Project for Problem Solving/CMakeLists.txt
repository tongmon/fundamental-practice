cmake_minimum_required(VERSION 3.23)

project(ProblemSolving VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ./*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})