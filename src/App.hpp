#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//TOOLS
#include "LibCraft/tools/include/filePath.hpp"
//RENDER ENGINE
#include "LibCraft/renderEngine/include/vbo.hpp"
#include "LibCraft/renderEngine/include/vao.hpp"
#include "LibCraft/renderEngine/include/ibo.hpp"
#include "LibCraft/renderEngine/include/Shader.hpp"
#include "LibCraft/renderEngine/include/Texture.hpp"
#include "LibCraft/renderEngine/include/Camera.hpp"
#include "LibCraft/renderEngine/include/Skybox.hpp"
#include "LibCraft/renderEngine/include/TextureCube.hpp"
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/renderEngine/include/Mesh.hpp"
#include "LibCraft/renderEngine/include/Model.hpp"
//CORE ENGINE
#include "LibCraft/coreEngine/include/Map.hpp"
#include "LibCraft/coreEngine/include/Player.hpp"
#include "LibCraft/coreEngine/include/Collectible.hpp"
#include "LibCraft/coreEngine/include/Enemy.hpp"
#include "LibCraft/coreEngine/include/HUD.hpp"

class App {
public:
    App(int window_width, int window_height, const FilePath& appPath);
    ~App();
    void render(GLFWwindow* window);
    void init();

    static void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xOffset, double yOffset);
    void cursor_position_callback(double xPos, double yPos, GLFWwindow* window);
    void size_callback(int width, int height);

private:
    Map _map;
    Shader _lightShader;
    Shader _skyboxShader;
    Shader _steveShader;
    GLint _uniId, _tex0Id{};
    FilePath _appPath;
    std::vector<TextureCube> _textures;
    std::vector<Model> _models;
    float _rotation;
    double _prevTime;
    int _width;
    int _height;
    Camera _camera;
    Skybox _skybox;

    Player _player;
    Model* _steve;
    float _angle =0;
    std::vector<Collectible> _collectibles;
    std::vector<Enemy> _enemies;
    HUD _hud;
    Cube _sun;

    void Continue(GLFWwindow *window);
};