# 使用CMake Tools插件（可选，如果这个项目去到一个没有这个插件的机器也同样可以生成项目）
include(CMakeToolsHelpers OPTIONAL)

# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目名称
project(3DSoftRender)

include_directories(./  ./SoftRender)#添加多目录的路径

add_subdirectory(SoftRender)

# 指定生成目标
add_executable(3DSoftRender main.cpp )
# 添加链接库  
#TARGET_LINK_LIBRARIES(3DSoftRender Math )
TARGET_LINK_LIBRARIES(3DSoftRender RenderEngine )  
 