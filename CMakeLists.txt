cmake_minimum_required(VERSION 3.20)
project(TrabalhoFinal)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(TrabalhoFinal main.cpp Filtros.cpp)

target_link_libraries(TrabalhoFinal ${OpenCV_LIBS})