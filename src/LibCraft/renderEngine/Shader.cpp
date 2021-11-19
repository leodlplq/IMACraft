//
// Created by leodlplq on 18/11/2021.
//

#include "Shader.hpp"

std::string get_file_contents(const char* filepath){
    std::string content;
    std::string currPath = std::filesystem::current_path();
    std::ifstream  fileStream(currPath + filepath, std::ios::in);

    if(!fileStream.is_open()){
        std::cerr << "not load" << std::endl;
        return "";
    }

    std::string line = "";

    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    _id = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(_id);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate() {
    glUseProgram(_id);
}

void Shader::deleteShader() {
    glDeleteProgram(_id);
}