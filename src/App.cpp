#include "App.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include <valarray>


App::App(int window_width, int window_height, FilePath appPath) :
 _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
 _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
 _uniId(0),
 _appPath(appPath),
 _textures(),
 _models(),
 _rotation(0.0f),
 _prevTime(0.0f),
 _width(window_width),
 _height(window_height),
 _player(Cube(), glm::vec3(0.f, 1.0f, 0.f)),
 _camera(_width,_height,_player)


{
    size_callback(window_width, window_height);
}
void App::init(){

    // MAP
    _map = Map(_appPath.dirPath() + "/assets/maps/map3.pgm");

    // MESH DU CUBE ORIGINEL !!
    Cube cube;

    //TEXTURE PATH FOR THE GROUND
    std::string filePathGrassSide = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/side.jpg");
    std::string filePathGrassTop = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/top.jpg");
    std::string filePathGrassBottom = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/bottom.jpg");

    // MODEL OF THE GROUND
    Model cube_model(cube,filePathGrassSide,filePathGrassSide,filePathGrassTop,filePathGrassBottom,filePathGrassSide,filePathGrassSide,GL_RGB);
    _models.push_back(cube_model);

    // TEST: ANOTHER CUBE Text
    std::string filePathTest = ((std::string)_appPath.dirPath() + "/assets/textures/player/side.png");
    Model cube_modeltest(cube,filePathTest,filePathTest,filePathTest,filePathTest,filePathTest,filePathTest,GL_RGBA);
    _models.push_back(cube_modeltest);

    //PLAYER
    _player = Player(cube, glm::vec3(0.f, 1.0f, 0.f));
    std::string filePathWood = ((std::string)_appPath.dirPath() + "/assets/textures/cobblestone/side.png");
    TextureCube player(&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0], GL_RGBA);
    player.texUnit(_shaderProgram,"tex0",0);
    _textures.push_back(player);

    // CAMERA
    glEnable(GL_DEPTH_TEST);
    std::cout << _width << _height << std::endl;


    // SKYBOX SHADER BINDING
    _skyboxShader.activate();
    glUniform1i(glGetUniformLocation(_skyboxShader._id,"skybox"),0);
}

void App::render(GLFWwindow* window)
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //INPUTS
    _player.Inputs(window);
    _player.render();

    // Tell OpenGL which Shader Program we want to use
    _shaderProgram.activate();
    _camera.Matrix(45.0f,0.1f,100.0f);

    int matrixID = glGetUniformLocation(_shaderProgram._id,"camMatrix");
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(_camera.getModelMatrix()));
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));

    // DRAW OUR PLAYER FOR TESTING
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,_player.getPosition());
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[0]._vao.bind();
    _textures[0].bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //TEST 2 CUBES
    model = glm::translate(model,glm::vec3(2,0,0));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[0].draw();
    model = glm::translate(model,glm::vec3(3,0,0));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[1].draw();


    // Draw the map
    for(auto &cube:_map.getMap()){
        glm::mat4 model = glm::mat4 (1.0f);
        model = cube.getObjectMatrix();
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
        if(int(model[3][2]) % 2 == 0){
            _models[0].draw();
        }
        else {
            _models[1].draw();
        }
    }
    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader,_camera,_width,_height);
}

App::~App(){
    _skybox._vao.deleteVao();
    _skybox._vbo.deleteVbo();
    _skybox._ibo.deleteIbo();
    for(unsigned int i=0;i<_models.size();i++){
        _models[0].del();
    }
    for(auto &item : _textures){
        item.deleteTex();
    }
    _shaderProgram.deleteShader();
    _skyboxShader.deleteShader();

}

void App::key_callback(int key, int scancode, int action, int mods)
{
    std::cout << key << std::endl;
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double xoffset, double yoffset)
{
    _camera.scrollCallback(xoffset, -yoffset);
}

void App::cursor_position_callback(double xpos, double ypos, GLFWwindow* window)
{
    glfwSetCursorPos(window,(_width/2),(_height/2));
    float rotx = _camera._sensitivity * (float)(ypos - ((float)_height/2))/(float)_height;
    float roty = _camera._sensitivity * (float)(xpos- ((float)_width/2))/(float)_width;

    _camera.rotateLeft(rotx);
    _camera.rotateUp(roty);
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}