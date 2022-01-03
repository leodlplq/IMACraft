#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>


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
#include "LibCraft/renderEngine/include/Light.hpp"
#include "LibCraft/renderEngine/include/Text.hpp"
#include "LibCraft/renderEngine/include/Button.hpp"
//CORE ENGINE
#include "LibCraft/coreEngine/include/Map.hpp"
#include "LibCraft/coreEngine/include/Player.hpp"
#include "LibCraft/coreEngine/include/Collectible.hpp"
#include "LibCraft/coreEngine/include/Enemy.hpp"
#include "LibCraft/renderEngine/include/HUD.hpp"
#include "LibCraft/renderEngine/include/Sauvegarde.hpp"

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
    void renderPauseMenu(GLFWwindow* window, double FPS);
    void renderLooseScreen(GLFWwindow* window, double FPS);
    void renderWinScreen(GLFWwindow* window, double FPS);

    inline bool isGameRunning() const { return _running; }
    inline void closeGame(){ _running = false; }

    //EVENT
    void key_callback(int key, /*int scancode,*/ int action/*, int mods*/);
    void mouse_button_callback(int button, int action, int mods, GLFWwindow* window);
    void scroll_callback(double xOffset, double yOffset);
    void cursor_position_callback(double xPos, double yPos, GLFWwindow* window);
    void size_callback(int width, int height);

    //SCENE SELECTION
    inline unsigned int getScene() const { return _selectedScene; }
    inline void setScene(unsigned int value) { _selectedScene = value; }

    //FPS
    inline void invertFPSShow() { _showingFPS = !_showingFPS; }

    void KeyBoardListener(GLFWwindow *window);

    //BUTTONS
    void initButtons();
    void handleClickEvent(GLFWwindow* window);
    void handleHoverEvent(double xPos, double yPos);

    void restart(){
        _restart = !_restart;
        _camera.restart();
        _player.restart();
        for(auto & _collectible : _collectibles){
            _collectible.reset();
        }
    }



private:
    bool _running = true;

    std::vector<Model> _models;
    std::vector<Model> _modelsMap;

    Map _map;
    Shader _skyboxShader;
    Shader _shaderProgram;
    Shader _steveShader;
    Shader _textShader;
    Shader _buttonShader;
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
    bool _scoreRegister = false;
    bool _restart = false;

    unsigned int _selectedScene = 0;
    Sauvegarde _sauv;
    std::string _pseudo;
    int _keypressed;

    //FPS
    bool _showingFPS = false;
    //FREETYPE
    Text _textArial;
    Text _textMinecraft;

    Light _light;


    void displayGame(double FPS);

    unsigned int _i = 0;
    int _key = _keypressed;

    //BUTTONS
    std::vector<Button> _buttons;

};

std::vector<Model> getAllModels(const FilePath &appPath);
std::vector<glm::vec3> getAllLitght(Map &map);