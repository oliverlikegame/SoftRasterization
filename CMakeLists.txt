cmake_minimum_required(VERSION 3.10)

set( PROJECT_NAME SoftRasterization )

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} common.hpp Geometry.hpp Geometry.cpp mathutil.hpp mathutil.cpp 
Rasterizer.hpp Rasterizer.cpp  Scene.hpp Scene.cpp Loader.hpp Mesh.hpp Texture.hpp Texture.cpp 
FragmentShader.hpp FragmentShader.cpp VertexShader.hpp Global.hpp Global.cpp Ray.hpp main.cpp )

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()