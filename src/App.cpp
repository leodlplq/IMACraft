#include "App.hpp"

std::vector<Model> getAllModels(const FilePath& appPath){
    std::vector<Model> models;

    // MODEL OF THE GROUND -- 0
    Model grass(((std::string)appPath.dirPath() + "/assets/obj/grass/scene.gltf").c_str());
    models.push_back(grass);

    // COBBLE TEXTURE MODEL -- 1
    Model cobblestone(((std::string)appPath.dirPath() + "/assets/obj/cobblestone/scene.gltf").c_str());
    models.push_back(cobblestone);

    // GOLD TEXTURE MODEL -- 2
    Model gold(((std::string)appPath.dirPath() + "/assets/obj/gold/scene.gltf").c_str());
    models.push_back(gold);

    // REDSTONE TEXTURE MODEL -- 3
    Model redstone(((std::string)appPath.dirPath() + "/assets/obj/redstone/scene.gltf").c_str());
    models.push_back(redstone);

    //

    return models;
}

App::App(int window_width, int window_height, const FilePath& appPath) :
     _models(),
     _modelsMap(getAllModels(appPath)),
     _map(appPath.dirPath() + "/assets/maps/map7.pgm", _modelsMap, 0.5),
     _lightShader("assets/shaders/lightShader.vs.glsl","assets/shaders/lightShader.fs.glsl" , appPath),
     _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
     _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
     _steveShader("assets/shaders/shaderSteve.vs.glsl","assets/shaders/shaderSteve.fs.glsl",appPath),
     _appPath(appPath),
     _textures(),
     _width(window_width),
     _height(window_height),
     _player(Model(((std::string)appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str()), _map.getSpawnPoint(),0.026f),
     _camera(_width,_height,_player),
     _collectibles(),
     _enemies(),
     _sun()
{
    size_callback(window_width, window_height);
}
void App::init(){

    // CAMERA
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // load models
    // -----------
    Model steve(((std::string)_appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str());
    _models.push_back(steve);
    std::cout << "Taille de Steve: " << steve.getHeight() << std::endl;
    Model terrain(((std::string)_appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str());
    _models.push_back(terrain);
    Model hud(((std::string)_appPath.dirPath() + "/assets/obj/hud/scene.gltf").c_str());
    _models.push_back(hud);
    Model pickaxe(((std::string)_appPath.dirPath() + "/assets/obj/pickaxe/scene.gltf").c_str());
    _models.push_back(pickaxe);
    Model sun(((std::string)_appPath.dirPath() + "/assets/obj/cube/cube.obj").c_str());
    _models.push_back(sun);

    Enemy zombie(((std::string)_appPath.dirPath() + "/assets/obj/zombie/scene.gltf").c_str(),glm::vec3(1.3,0.1,-1),glm::vec3(0.06f, 0.06f, 0.06f));
    _enemies.push_back(zombie);
    Enemy creeper(((std::string)_appPath.dirPath() + "/assets/obj/creeper/scene.gltf").c_str(),glm::vec3(1,0.5,0),glm::vec3(0.06f, 0.06f, 0.06f));
    _enemies.push_back(creeper);
    Enemy enderMan(((std::string)_appPath.dirPath() + "/assets/obj/enderman/scene.gltf").c_str(),glm::vec3(1.8,-0.5,1),glm::vec3(0.05f, 0.05f, 0.05f));
    _enemies.push_back(enderMan);
    std::cout << _map.getSecondFloor().size() << " =? " << 128*128 << std::endl;

    Collectible diamond(((std::string)_appPath.dirPath() + "/assets/obj/diamond/scene.gltf").c_str(), glm::vec3(0.0f, 0.6f, 10.0f));
    _collectibles.push_back(diamond);

    // SKYBOX SHADER BINDING
    _skyboxShader.activate();
    glUniform1i(glGetUniformLocation(_skyboxShader._id,"skybox"),0);


}

void App::render(GLFWwindow* window) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader, _camera, _width, _height);

    _steveShader.activate();
    _camera.Matrix(45.0f, 0.1f, 100.0f);
    inputs(window);
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.f, 2.f, 7.f);
    //Light
    _lightShader.activate();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));    // it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(_lightShader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(_camera.getProjMatrix() * _camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(_lightShader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    _models[4].Draw(_lightShader);


    // Tell OpenGL which Shader Program we want to use
    _steveShader.activate();
    glUniform4f(glGetUniformLocation(_steveShader._id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(_steveShader._id, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(_steveShader._id, "camPos"), _camera._position.x, _camera._position.y,_camera._position.z);

    //HUD
    if (_player.getDistanceToPlayer() != 0) {
        //INPUTS
        inputs(window);
        _player.render();
        _hud.DrawHUD(_steveShader, _models[2]);
    } else { //Game Over
        _hud.DrawGameOver(_steveShader, _models[3]);
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            _player.setDistanceToPlayer(1.f);
            std::cout << "Restart" << std::endl;
        }
    }

    //Player Part
    _steveShader.activate();
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(_camera.getProjMatrix() * _camera.getViewMatrix()));
    //_player.Draw(_steveShader);

    //
    _shaderProgram.activate();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.f));
    model = glm::scale(model, glm::vec3(100000));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(_camera.getProjMatrix() * _camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    _player.getHitbox().Draw();

// Collectibles
    for (unsigned int i = 0; i < _collectibles.size(); i++) {
        _collectibles[i].Update(_player);
        _collectibles[i].Draw(_steveShader, _camera);
    }
//
//    //Enemies
//    for (unsigned int i = 0; i < _enemies.size(); i++) {
//        _enemies[i].DrawEnemy(_player, _camera, _steveShader);
//    }


    // Draw the map
    //FLOOR PART
    for (auto &me: _map.getFloor()) {
        if (me.getModel() != -1) {
            model = me.getObjectMatrix();
            model = glm::scale(model,glm::vec3(0.5f, 0.5f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
            _modelsMap[static_cast<unsigned long>(me.getModel())].Draw(_steveShader);
        }
    }
//    SECOND FLOOR PART (WALL / JUMP OBSTACLE...)
    for (auto &me: _map.getSecondFloor()) {
        if (me.getModel() != -1) {
            model = me.getObjectMatrix();
            model = glm::scale(model,glm::vec3(0.5f, 0.5f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
            _modelsMap[static_cast<unsigned long>(me.getModel())].Draw(_steveShader);
        }

    }

}

void App::key_callback(int key, /*int scancode,*/ int action/*, int mods*/)
{

    double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));
    if(key == 65 && action == GLFW_PRESS){
        int xPlayer = static_cast<int>(round(_player.getPosition().x));
        int yPlayer = static_cast<int>(round(_player.getPosition().z));


        int coord = static_cast<int>((xPlayer * sizeMap) + yPlayer);

        if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
            _player.setOrientationRotation(90.f);
            switch (_player.getFacingDirection()) {
                case 'N':
                    _player.setFacingOrientation('W');
                    break;
                case 'W':
                    _player.setFacingOrientation('S');
                    break;
                case 'S':
                    _player.setFacingOrientation('E');
                    break;
                case 'E':
                    _player.setFacingOrientation('N');
                    break;
            }
            _camera.rotateLeft(-90.f);
        }

    }

    if(key == 68 && action == GLFW_PRESS){
        int xPlayer = static_cast<int>(round(_player.getPosition().x));
        int yPlayer = static_cast<int>(round(_player.getPosition().z));

        int coord = static_cast<int>((xPlayer * sizeMap) + yPlayer);

        if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
            _player.setOrientationRotation(-90.f);
            switch (_player.getFacingDirection()) {
                case 'N':
                    _player.setFacingOrientation('E');
                    break;
                case 'W':
                    _player.setFacingOrientation('N');
                    break;
                case 'S':
                    _player.setFacingOrientation('W');
                    break;
                case 'E':
                    _player.setFacingOrientation('S');
                    break;
            }

            _camera.rotateLeft(90.f);
        }

    }

    if(key == 32 && (action == GLFW_PRESS)){
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

    _camera.rotateLeft(rotY);
    _camera.rotateUp(rotX);
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}

void App::inputs(GLFWwindow* window) {
//(x * 128)+y TO GET 2D VECTOR WITH JUST 1D VECTOR.
    //GOING FORWARD
    if(glfwGetKey(window,87) == GLFW_PRESS){ //GOING FORWARD
        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourRX;
        int nextBlockNeighbourRY;
        int nextBlockNeighbourLX;
        int nextBlockNeighbourLY;

        switch (_player.getFacingDirection()) {
            case 'N':
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                //RIGHT
                nextBlockNeighbourRX = -1;
                nextBlockNeighbourRY = -1;
                //LEFT
                nextBlockNeighbourLX = -1;
                nextBlockNeighbourLY = 1;
                break;
            case 'S':
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                //RIGHT
                nextBlockNeighbourRX = 1;
                nextBlockNeighbourRY = 1;
                //LEFT
                nextBlockNeighbourLX = 1;
                nextBlockNeighbourLY = -1;
                break;
            case 'W':
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                //RIGHT
                nextBlockNeighbourRX = -1;
                nextBlockNeighbourRY = 1;
                //LEFT
                nextBlockNeighbourLX = 1;
                nextBlockNeighbourLY = 1;
                break;

            case 'E':
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                //RIGHT
                nextBlockNeighbourRX = 1;
                nextBlockNeighbourRY = -1;
                //LEFT
                nextBlockNeighbourLX = -1;
                nextBlockNeighbourLY = -1;
                break;
            default:
                assert("y'a autres choses frro");

                break;
        } // WHICH DIRECTION IT GOES

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(_player.getPosition().x));
        int yPlayer = static_cast<int>(round(_player.getPosition().z));
        int x =  xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;

        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();

        //RIGHT NEIGHBOUR
        int neiX = xPlayer + nextBlockNeighbourRX;
        int neiY = yPlayer + nextBlockNeighbourRY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();

        //LEFT NEIGHBOUR
        int neiX2 = xPlayer + nextBlockNeighbourLX;
        int neiY2 = yPlayer + nextBlockNeighbourLY;
        int neiCoord2 = static_cast<int>((neiX2 * sizeMap) + neiY2);
        Hitbox neiBlockHitbox2 = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord2)].getHitbox();

        _player.display();
        std::cout << "-------------DIRECTION : " << _player.getFacingDirection() << " -------------"<< std::endl;

        bool playerBlock = !_player.getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !_player.getHitbox().intersect(neiBlockHitbox);
        bool playerBlockNei2 = !_player.getHitbox().intersect(neiBlockHitbox2);

        if(
                (playerBlock && playerBlockNei  && playerBlockNei2) ||
                (playerBlock && playerBlockNei  && !playerBlockNei2 && blockHitbox.getCorner1().x == 10000.5) ||
                (playerBlock && !playerBlockNei  && playerBlockNei2 && blockHitbox.getCorner1().x == 10000.5)

                ){
            _player.moveForward();
        } else {
            //closeGame(); COMMENTED WHILE WORKING ON THE GAME.
        }


    }

    //GOING LEFT
    if(glfwGetKey(window, 65) == GLFW_PRESS){ // MOVEMENT TO THE LEFT
        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourX;
        int nextBlockNeighbourY;
        switch (_player.getFacingDirection()) {
            case 'N':
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'S':
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'W':
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'E':
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            default:
                assert("y'a pas a etre ici ????!");
                break;
        }

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(_player.getPosition().x));
        int yPlayer = static_cast<int>(round(_player.getPosition().z));

        int x = xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;
        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();
        std::cout << "-------------DIRECTION : " << _player.getFacingDirection() << " -------------"<< std::endl;
        int neiX = xPlayer + nextBlockNeighbourX;
        int neiY = yPlayer + nextBlockNeighbourY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();

        std::cout << "------------ PLAYER -------------" << std::endl;
        _player.getHitbox().display();
        std::cout << "------------ BLOCK -------------" << std::endl;
        blockHitbox.display();
        std::cout << (_player.getHitbox().intersect(blockHitbox) ? "collision" : "no collision")<< std::endl;
        std::cout << "------------ OTHER BLOCK -------------" << std::endl;
        neiBlockHitbox.display();
        std::cout << (_player.getHitbox().intersect(neiBlockHitbox) ? "collision" : "no collision")<< std::endl;


        bool playerBlock = !_player.getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !_player.getHitbox().intersect(neiBlockHitbox);

        /*if(playerBlock &&  playerBlockNei){
            _player.moveLeft();
        }*/
        if(
                (playerBlock &&  playerBlockNei) ||
                (playerBlock &&  !playerBlockNei && blockHitbox.getCorner1().x == 10000.5)
                ){
            if(!_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
                _player.moveLeft();
            }

        }



    }
    if(glfwGetKey(window, 68) == GLFW_PRESS){ //GOING RIGHT

        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourX;
        int nextBlockNeighbourY;
        switch (_player.getFacingDirection()) {
            case 'N': //WHEN GOING LEFT Z INCREASE
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'S': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'W': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'E': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            default: // if it is not N or S then it's W or E and it's a 0;
                assert("y'a pas a etre ici ????!");
                break;
        }

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(_player.getPosition().x));
        int yPlayer = static_cast<int>(round(_player.getPosition().z));
        std::cout << "-------------DIRECTION : " << _player.getFacingDirection() << " -------------"<< std::endl;
        int x = xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;
        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();

        int neiX = xPlayer + nextBlockNeighbourX;
        int neiY = yPlayer + nextBlockNeighbourY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();

        bool playerBlock = !_player.getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !_player.getHitbox().intersect(neiBlockHitbox);

        if(
                (playerBlock &&  playerBlockNei) ||
                (playerBlock &&  !playerBlockNei && blockHitbox.getCorner1().x == 10000.5)
        ){
            if(!_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
                _player.moveRight();
            }
        }



    }

    if(glfwGetKey(window,83) == GLFW_PRESS){ //GOING BACKWARD
        _player.moveBackward();
    }
}

App::~App(){
    //DELETING EVERYTHING
    //SHADERS
//    _shaderProgram.deleteShader();
//    _shaderProgram.~Shader();
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
//    for(auto &item : _modelsCube){
//        item.del();
//    }
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