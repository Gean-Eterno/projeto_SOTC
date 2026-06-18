cmake_minimum_required(VERSION 3.20)
project(TrabalhoFinal)

set(CMAKE_CXX_STANDARD 14)

# Procura o OpenCV instalado no sistema
find_package(OpenCV REQUIRED)

# Define o executável com os arquivos fonte
add_executable(TrabalhoFinal main.cpp Filtros.cpp)

# Linka as bibliotecas do OpenCV no executável
target_link_libraries(TrabalhoFinal ${OpenCV_LIBS})