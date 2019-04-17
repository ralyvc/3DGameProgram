include(CMakeToolsHelpers OPTIONAL)

cmake_minimum_required(VERSION 2.8)

#添加opencv头文件的搜索路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Third/include/SDL2)

# 查找路径下的所有源文件
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(RenderEngine ${DIR_LIB_SRCS})



# 添加链接库  
#TARGET_LINK_LIBRARIES(RenderEngine ${PROJECT_SOURCE_DIR}/Third/libs/libSDL2.a)  
#TARGET_LINK_LIBRARIES(RenderEngine ${PROJECT_SOURCE_DIR}/Third/libs/libSDL2main.a)  
TARGET_LINK_LIBRARIES(RenderEngine ${PROJECT_SOURCE_DIR}/Third/libs/libSDL2.dll.a)  
 



