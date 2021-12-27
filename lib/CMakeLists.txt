cmake_minimum_required(VERSION 3.8)

project(lib)
add_library(${PROJECT_NAME} INTERFACE)

# ---Add GLFW---
add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} INTERFACE glfw)

# ---Add glad---
add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)
target_link_libraries(${PROJECT_NAME} INTERFACE glad)

# --- Add stb ---
add_library(stb stb/stb_image.cpp)
target_link_libraries(${PROJECT_NAME} INTERFACE stb)

# ---Add glm ---
add_subdirectory(glm)
target_link_libraries(${PROJECT_NAME} INTERFACE glm)

# --- Add Assimp ---
#add_library(assimp-5.0.1 assimp-5.0.1/include/assimp/config.h)
#target_include_directories(assimp-5.0.1 PUBLIC assimp-5.0.1/include)
#find_library(assimp assimp ${ASSIMP_DIRECTORY})
#target_link_libraries(${PROJECT_NAME} INTERFACE assimp)
#include_directories(assimp-5.0.1/include)
#set(BUILD_ASSIMP_TOOLS ON)
#set(ASSIMP_BUILD_STATIC_LIB ON)
#set(${PROJECT_SOURCE_DIR}/lib/assimp-5.0.1/build/code/libassimp.so)