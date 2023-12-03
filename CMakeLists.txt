cmake_minimum_required(VERSION 3.12)

project(mundoVirtual)

# Adiciona o execut�vel do projeto
add_executable(mundoVirtual "main.cpp" "Error.h" "Error.cpp" "Camera.h" "Camera.cpp" "Cube.cpp" "Shader.h" "Shader.cpp" "Primitives.h" "Primitives.cpp" "Pyramid.cpp" "Terrain.cpp" "Rectangle.cpp" "Diamond.cpp" "glad.c")

target_link_libraries(${PROJECT_NAME}  GL dl glfw)