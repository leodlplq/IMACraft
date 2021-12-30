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
#include "LibCraft/tools/include/deleteElementsFromVector.hpp"
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

#include "LibCraft/renderEngine/include/Text.hpp"
//CORE ENGINE
#include "LibCraft/coreEngine/include/Map.hpp"
#include "LibCraft/coreEngine/include/Player.hpp"
#include "LibCraft/coreEngine/include/Collectible.hpp"
#include "LibCraft/coreEngine/include/Enemy.hpp"
#include "LibCraft/coreEngine/include/HUD.hpp"

class App {
public:
    //CONSTRUCTORS & DESTRUCTORS
    App(int window_width, int window_height, const FilePath& appPath);
    ~App();

    //USEFUL
    void init();
    void render(GLFWwindow* window, double FPS);

    //ALL THE SCENE*
    void renderMainMenu(GLFWwindow* window, double FPS);
    void renderGame(GLFWwindow* window, double FPS);
    void renderPauseMenu(GLFWwindow* window);
    void renderLooseScreen(GLFWwindow* window);
    void renderWinScreen(GLFWwindow* window);


    inline bool isGameRunning() const { return _running; }
    inline void closeGame(){ _running = false; }

    //EVENT
    void key_callback(int key, /*int scancode,*/ int action/*, int mods*/);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xOffset, double yOffset);
    void cursor_position_callback(double xPos, double yPos, GLFWwindow* window);
    void size_callback(int width, int height);


    //SCENE SELECTION
    inline unsigned int getScene() const { return _selectedScene; }
    inline void setScene(unsigned int value) { _selectedScene = value; }

    //FPS
    inline void invertFPSShow() { _showingFPS = !_showingFPS; }




private:
    bool _running = true;

    std::vector<Model> _models;
    std::vector<Model> _modelsMap;

    Map _map;
    Shader _lightShader;
    Shader _skyboxShader;
    Shader _shaderProgram;
    Shader _steveShader;
    Shader _textShader;
    FilePath _appPath;
    std::vector<TextureCube> _textures;
    int _width;
    int _height;
    Player _player;
    Camera _camera;
    Skybox _skybox;
    float _angle =0;
    std::vector<Collectible> _collectibles;
    std::vector<Enemy> _enemies;
    HUD _hud;
    Cube _sun;

    //void Continue(GLFWwindow *window);

    unsigned int _selectedScene = 1;

    //FPS
    bool _showingFPS = false;
    //FREETYPE
    Text _textArial;
    Text _textMinecraft;
};

std::vector<Model> getAllModels(const FilePath &appPath);