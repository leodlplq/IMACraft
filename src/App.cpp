#include "App.hpp"

std::vector<Model> getAllModels(const FilePath& appPath){
    std::vector<Model> models;

    // MESH DU CUBE ORIGINAL !!
    Cube cube;

    //TEXTURE PATH FOR THE GROUND
    std::string filePathGrassSide = ((std::string)appPath.dirPath() + "/assets/textures/grass_cube/side.jpg");
    std::string filePathGrassTop = ((std::string)appPath.dirPath() + "/assets/textures/grass_cube/top.jpg");
    std::string filePathGrassBottom = ((std::string)appPath.dirPath() + "/assets/textures/grass_cube/bottom.jpg");

    // MODEL OF THE GROUND -- 0
    Model cube_model(cube,filePathGrassSide,filePathGrassSide,filePathGrassTop,filePathGrassBottom,filePathGrassSide,filePathGrassSide,GL_RGB);
    models.push_back(cube_model);

    // TEST: ANOTHER CUBE Text -- 1
    std::string filePathTest = ((std::string)appPath.dirPath() + "/assets/textures/player/side.png");
    Model cube_modeltest(cube,filePathTest,filePathTest,filePathTest,filePathTest,filePathTest,filePathTest,GL_RGBA);
    models.push_back(cube_modeltest);

    // GOLD TEXTURE MODEL -- 2
    std::string filePathGold = ((std::string)appPath.dirPath() + "/assets/textures/gold/side.jpeg");
    Model gold_cube(cube,filePathGold,filePathGold,filePathGold,filePathGold,filePathGold,filePathGold,GL_RGB);
    models.push_back(gold_cube);

    // REDSTONE TEXTURE MODEL -- 3
    std::string filePathRedstone = ((std::string)appPath.dirPath() + "/assets/textures/redstone/side.jpg");
    Model redstone_cube(cube,filePathRedstone,filePathRedstone,filePathRedstone,filePathRedstone,filePathRedstone, filePathRedstone,GL_RGB);
    models.push_back(redstone_cube);

    //

    return models;
}

App::App(int window_width, int window_height, const FilePath& appPath) :
     _models(getAllModels(appPath)),
     _map(appPath.dirPath() + "/assets/maps/map7.pgm", _models),
     _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
     _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
     _appPath(appPath),
     _textures(),
     _width(window_width),
     _height(window_height),
     _camera(_width,_height,_player, _map),
     _player(Cube(), _map.getSpawnPoint(), _map)
{
    size_callback(window_width, window_height);
}
void App::init(){
    //PLAYER
    std::string filePathWood = ((std::string)_appPath.dirPath() + "/assets/textures/cobblestone/side.png");
    TextureCube player(&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0], GL_RGBA);
    player.texUnit(_shaderProgram,"tex0",0);
    _textures.push_back(player);

    // CAMERA
    glEnable(GL_DEPTH_TEST);
    std::cout << _width << _height << std::endl;

    std::cout << _map.getSecondFloor().size() << " =? " << 128*128 << std::endl;


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


    // Draw the map
    //FLOOR PART
    for(auto &me:_map.getFloor()){
        if(me.getModel() != -1){
            model = me.getObjectMatrix();
            glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
            _models[static_cast<unsigned long>(me.getModel())].draw();
        }
    }

    //SECOND FLOOR PART (WALL / JUMP OBSTACLE...)
    for(auto &me:_map.getSecondFloor()){
        if(me.getModel() != -1){
            model = me.getObjectMatrix();
            glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
            _models[static_cast<unsigned long>(me.getModel())].draw();
        }
    }

    /* VERIF SI ON EST EN TRAIN DE TOURNER
     *
     * SI OUI -- ON AUGMENTE X PAR X JUSQU'A MAX 90
     * SI NON -- ON FAIT RIEN.
     *
     * */
    float valueToRotatePerFrame = 5.f;
    if(_camera.isTurningLeft() && _camera.getCurrentAngleX() < 90){
        _camera.rotateLeft(-valueToRotatePerFrame);
        _camera.setCurrentAngleX(_camera.getCurrentAngleX() + valueToRotatePerFrame);
    } else if(_camera.isTurningRight() && _camera.getCurrentAngleX() < 90) {
        _camera.rotateLeft(valueToRotatePerFrame);
        _camera.setCurrentAngleX(_camera.getCurrentAngleX() + valueToRotatePerFrame);
    } else {
        _camera.setCurrentAngleX(0.f);
        _camera.setTurningLeft(false);
        _camera.setTurningRight(false);
    }

    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader,_camera,_width,_height);
}



void App::key_callback(int key, /*int scancode,*/ int action/*, int mods*/)
{

    if(key == 65 && action == GLFW_PRESS){
        _player.turnLeft();
        _camera.turnLeft();
    }

    if(key == 68 && action == GLFW_PRESS){
        _player.turnRight();
        _camera.turnRight();
    }


    if(key == 32 && (action == GLFW_PRESS)){
        _player.startJump();
    }

    //L == LOCKING THE CAMERA
    if(key == 76 && (action == GLFW_PRESS)){
        _camera.invertCamLock();
    }

    //M == LOCKING THE CAMERA
    if(key == 77 && (action == GLFW_PRESS)){

        _camera.invertCamMode();
        _camera.resetAngle();
    }

    //std::cout << "key : " << key << std::endl;
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double xOffset, double yOffset)
{
    if(!_camera.isCamLocked()) {
        _camera.scrollCallback(xOffset, -yOffset);
    }
}

void App::cursor_position_callback(double xPos, double yPos, GLFWwindow* window)
{

    glfwSetCursorPos(window,(float)_width/2,(float)_height/2);
    //IT CAN ONLY ROTATE WHEN THE USER WANT
    if(!_camera.isCamLocked()){
        float rotX = _camera.getSensitivity() * (float)(yPos - ((float)_height/2))/(float)_height;
        float rotY = _camera.getSensitivity() * (float)(xPos- ((float)_width/2))/(float)_width;

        _camera.rotateLeft(rotY);
        _camera.rotateUp(rotX);
    }

}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
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

// -------------------------------------------------------- PRESSE PAPIER ---------------------------------------------------------------

/*std::cout << "------------ PLAYER -------------" << std::endl;
        _player.getHitbox().display();
        std::cout << "------------ BLOCK -------------" << std::endl;
        blockHitbox.display();
        std::cout << (_player.getHitbox().intersect(blockHitbox) ? "collision" : "no collision")<< std::endl;
        std::cout << "------------ OTHER BLOCK -------------" << std::endl;
        neiBlockHitbox.display();
        std::cout << (_player.getHitbox().intersect(neiBlockHitbox) ? "collision" : "no collision")<< std::endl;*/