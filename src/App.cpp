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
     _camera(_width,_height,_player),
     _player(Cube(), _map.getSpawnPoint())
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
    inputs(window);
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


    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader,_camera,_width,_height);
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

    //L == LOCKING THE CAMERA
    if(key == 76 && (action == GLFW_PRESS)){
        _camera.invertCamLock();
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