#include "App.hpp"


App::App(int window_width, int window_height, const FilePath& appPath) :
 _map(appPath.dirPath() + "/assets/maps/map6.pgm"),
 _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
 _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
 _appPath(appPath),
 _textures(),
 _models(),
 _width(window_width),
 _height(window_height),
 _camera(_width,_height,_player),
 _player(Cube(), _map.getSpawnPoint())
{
    size_callback(window_width, window_height);
}
void App::init(){
    // MESH DU CUBE ORIGINAL !!
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
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //TEST 2 CUBES
    /*model = glm::translate(model,glm::vec3(2,0,0));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[0].draw();
    model = glm::translate(model,glm::vec3(3,0,0));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    _models[1].draw();*/


    // Draw the map
    for(auto &cube:_map.getMap()){
        model = glm::mat4 (1.0f);
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
    //DELETING EVERYTHING
    //SHADERS
    _shaderProgram.deleteShader();
    _shaderProgram.~Shader();
    _skyboxShader.deleteShader();
    _skyboxShader.~Shader();
    //APP PATH
    _appPath.~FilePath();
    //TEXTURES
    for(auto &item : _textures){
        item.deleteTex();
    }
    _textures.erase(_textures.begin(), _textures.end());
    _textures.shrink_to_fit();
    //MODELS
    for(auto &item : _models){
        item.del();
    }
    _models.erase(_models.begin(), _models.end());
    _models.shrink_to_fit();
    //CAMERA
    _camera.~Camera();
    //SKYBOX
    _skybox.~Skybox();
    //PLAYER
    _player.~Player();
}

void App::key_callback(int key, /*int scancode,*/ int action/*, int mods*/)
{


    if(key == 65 && action == GLFW_PRESS){
        //TODO : we need to check if the player is able to move or if there is a collision
        _player.display();
        //TODO : we need to check if the player is turning while on intersection
        _player.moveLeft();
    }

    if(key == 68 && action == GLFW_PRESS){
        _player.moveRight();
        _player.display();
    }

    if(key == 32 && action == GLFW_PRESS){
        _player.startJump();
    }
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
    glfwSetCursorPos(window,(float)_width/2,(float)_height/2);
    float rotX = _camera._sensitivity * (float)(yPos - ((float)_height/2))/(float)_height;
    float rotY = _camera._sensitivity * (float)(xPos- ((float)_width/2))/(float)_width;

    _camera.rotateLeft(rotX);
    _camera.rotateUp(rotY);
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}