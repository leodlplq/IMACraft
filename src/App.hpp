#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include "stb/stb.h"
#include "Triangle.h"

#include "LibCraft/renderEngine/vbo.hpp"
#include "LibCraft/renderEngine/vao.hpp"
#include "LibCraft/renderEngine/ibo.hpp"
#include "LibCraft/renderEngine/Shader.hpp"

class App {
public:
    App(int window_width, int window_height);
    ~App();
    void render();
    void init();

    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:

    vao _vao;
    vbo _vbo;
    ibo _ibo;
    Shader _shaderProgram;
    GLint _uniId;
    int _width{};
    int _height{};

};