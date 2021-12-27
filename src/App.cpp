#include "App.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include <valarray>


App::App(int window_width, int window_height, const FilePath& appPath) :
 _lightShader("assets/shaders/lightShader.vs.glsl","assets/shaders/lightShader.fs.glsl" , appPath),
 _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
 _steveShader("assets/shaders/shaderSteve.vs.glsl","assets/shaders/shaderSteve.fs.glsl",appPath),
 _uniId(0),
 _appPath(appPath),
 _textures(),
 _models(),
 _rotation(0.0f),
 _prevTime(0.0f),
 _width(window_width),
 _height(window_height),
 _camera(_width,_height,_player),
 _player(Cube(), glm::vec3(0.f, 1.0f, 0.f)),
 _steve(),
 _collectibles(),
 _enemies(),
 _sun()
{
    size_callback(window_width, window_height);
}
void App::init(){

//    // MAP
//    _map = Map(_appPath.dirPath() + "/assets/maps/map3.pgm");
//
//    // MESH DU CUBE ORIGINAL !!
//    Cube cube;
//
//    //TEXTURE PATH FOR THE GROUND
//    std::string filePathGrassSide = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/side.jpg");
//    std::string filePathGrassTop = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/top.jpg");
//    std::string filePathGrassBottom = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/bottom.jpg");

    // CAMERA
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // load models
    // -----------
    Model steve(((std::string)_appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str());
    _models.push_back(steve);
    std::cout << "Taille de Steve: " << steve.getHeight() << std::endl;
    Model terrain(((std::string)_appPath.dirPath() + "/assets/obj/a_minecraft_village/scene.gltf").c_str());
    _models.push_back(terrain);
    Model hud(((std::string)_appPath.dirPath() + "/assets/obj/hud/scene.gltf").c_str());
    _models.push_back(hud);
    Model pickaxe(((std::string)_appPath.dirPath() + "/assets/obj/pickaxe/scene.gltf").c_str());
    _models.push_back(pickaxe);
    Model sun(((std::string)_appPath.dirPath() + "/assets/obj/cube/cube.obj").c_str());
    _models.push_back(sun);

    Enemy zombie(((std::string)_appPath.dirPath() + "/assets/obj/zombie/scene.gltf").c_str(),glm::vec3(-0.3,0.1,1),glm::vec3(0.027f, 0.027f, 0.027f));
    _enemies.push_back(zombie);
    Enemy creeper(((std::string)_appPath.dirPath() + "/assets/obj/creeper/scene.gltf").c_str(),glm::vec3(0,0.3,0),glm::vec3(0.03f, 0.03f, 0.03f));
    _enemies.push_back(creeper);
    Enemy enderMan(((std::string)_appPath.dirPath() + "/assets/obj/enderman/scene.gltf").c_str(),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.025f, 0.025f, 0.025f));
    _enemies.push_back(enderMan);

    Collectible diamond(((std::string)_appPath.dirPath() + "/assets/obj/diamond/scene.gltf").c_str(), glm::vec3(0.0f, 0.6f, 10.0f));
    _collectibles.push_back(diamond);

    // SKYBOX SHADER BINDING
    _skyboxShader.activate();
    glUniform1i(glGetUniformLocation(_skyboxShader._id,"skybox"),0);


}

void App::render(GLFWwindow* window)
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::vec4 lightColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    glm::vec3 lightPos = glm::vec3(0.f,2.f,7.f);
    //Light
    _lightShader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,lightPos);
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(_lightShader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(_lightShader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[4].Draw(_lightShader);
    // Tell OpenGL which Shader Program we want to use
    _steveShader.activate();
    glUniform4f(glGetUniformLocation(_steveShader._id,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(_steveShader._id,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
    _camera.Matrix(45.0f,0.1f,100.0f);
    glUniform3f(glGetUniformLocation(_steveShader._id,"camPos"),_camera._position.x,_camera._position.y,_camera._position.z);
    //HUD
    if(_player.getDistanceToPlayer() != 0) {
        //INPUTS
        _player.Inputs(window);
        _player.render();
        _hud.DrawHUD(_steveShader,_models[2]);
    }
    else{ //Game Over
        _hud.DrawGameOver(_steveShader,_models[3]);
        if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS){
            _player.setDistanceToPlayer(1.f);
            std::cout << "Restart" << std::endl;
        }
    }

    //Player Part
    _steveShader.activate();
    model = glm::mat4(1.0f);
    model = glm::translate(model,_player.getPosition());
    model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1,0,0));
    model = glm::scale(model, glm::vec3(0.013f, 0.013f, 0.013f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[0].Draw(_steveShader);
    //Terrain
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1,0,0));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[1].Draw(_steveShader);

// Collectibles
    for(unsigned int i = 0; i< _collectibles.size();i++){
        _collectibles[i].Update(_player);
        _collectibles[i].Draw(_steveShader, _camera);
    }

    //Enemies
    for(unsigned int i = 0; i< _enemies.size();i++) {
        _enemies[i].DrawEnemy(_player,_camera,_steveShader);
    }
    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader,_camera,_width,_height);


    //    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));

//      glm::mat4 model = glm::mat4(1.0f);
//    // Draw the map
//    for(auto &cube:_map.getMap()){
//        model = glm::mat4 (1.0f);
//        model = cube.getObjectMatrix();
//        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
//        if(int(model[3][2]) % 2 == 0){
//            _models[0].draw();
//        }
//        else {
//            _models[1].draw();
//        }
//    }
}

App::~App(){
    _skybox._vao.deleteVao();
    _skybox._vbo.deleteVbo();
    _skybox._ibo.deleteIbo();
//    for(unsigned int i=0;i<_models.size();i++){
//        _models[0].del();
//    }
    for(auto &item : _textures){
        item.deleteTex();
    }
    //_shaderProgram.deleteShader();
    _skyboxShader.deleteShader();

}

void App::key_callback(int key, int scancode, int action, int mods)
{
    std::cout << key << std::endl;
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double xOffset, double yOffset)
{
    _camera.scrollCallback(xOffset, -yOffset);
}

void App::cursor_position_callback(double xPos, double yPos, GLFWwindow* window)
{
    glfwSetCursorPos(window,(float(_width)/2.f),(float(_height)/2.f));
    float rotX = _camera._sensitivity * (float)(yPos - ((float)_height / 2)) / (float)_height;
    float rotY = _camera._sensitivity * (float)(xPos - ((float)_width / 2)) / (float)_width;

    _camera.rotateLeft(rotX);
    _camera.rotateUp(rotY);
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}