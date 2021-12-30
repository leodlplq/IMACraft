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

# ---Add assimp ---
add_subdirectory(assimp) # trouve assimp au chemin spécifié, ici lib/assimp par exemple ; et comme leur CMakeLists.txt est dans un dossier code on met le chemin vers ce dossier
target_link_libraries(${PROJECT_NAME} INTERFACE assimp::assimp) # Déclare que notre projet utilise assimp ; ça va faire les bons include directories etc, nous on a rien de plus à faire que cette ligne là

# ---Add freetype ---
add_subdirectory(freetype)
target_link_libraries(${PROJECT_NAME} INTERFACE freetype::freetype)