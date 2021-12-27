cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0112 NEW) # Required by copy_folder_to_output()

project(IMACraft)
add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Enable many good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Set the folder where the executable is created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Add all the files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)


# --- Include libs

add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PUBLIC lib)

set(ASSIMP_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp)
find_library(assimp assimp ${ASSIMP_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)


# Copy the assets to the output folder (where the executable is created)
function(copy_folder_to_output DIR)
    string(SHA1 TARGET_HASH ${DIR})              # Create a unique name for our custom target. We can't use ${DIR} directly because it could contain invalid characters like spaces
    set(TARGET_NAME CopyToOutput_${TARGET_HASH}) #
    add_custom_target(${TARGET_NAME}
        COMMENT "Copying \"${DIR}\""
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DIR}
    )
    add_dependencies(${PROJECT_NAME} ${TARGET_NAME}) # Mark our custom target as a dependency of the main project, so that whenever the main project is launched our custom target is triggered and files are copied
endfunction()
copy_folder_to_output("assets")