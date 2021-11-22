#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include "stb/stb_image.h"
#include "Cube.hpp"
#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "LibCraft/renderEngine/include/vbo.hpp"
#include "LibCraft/renderEngine/include/vao.hpp"
#include "LibCraft/renderEngine/include/ibo.hpp"
#include "LibCraft/renderEngine/include/Shader.hpp"
#include "LibCraft/tools/include/filePath.hpp"
#include "LibCraft/renderEngine/include/Texture.hpp"
#include "LibCraft/coreEngine/include/Map.hpp"

class App {
public:
    App(int window_width, int window_height, FilePath appPath);
    ~App();
    void render();
    void init();

    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    Map _map;
    vao _vao;
    vbo _vbo;
    ibo _ibo;
    Shader _shaderProgram;
    GLint _uniId, _tex0Id;
    FilePath _appPath;
    std::vector<Texture> _textures;
    float _rotation;
    double _prevTime;
    int _width{};
    int _height{};

};