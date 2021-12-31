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
     _textShader("assets/shaders/textShader.vs.glsl", "assets/shaders/textShader.fs.glsl", appPath),
     _buttonShader("assets/shaders/buttonShader.vs.glsl", "assets/shaders/buttonShader.fs.glsl", appPath),
     _appPath(appPath),
     _textures(),
     _width(window_width),
     _height(window_height),
     _player(Model(((std::string)appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str()), _map.getSpawnPoint(),0.026f, _map),
     _camera(_width,_height,_player, _map),
     _hud(_width,_height),
     _textArial(appPath, _width, _height, "arial"),
     _textMinecraft(appPath, _width, _height, "Minecraft"),
     _sauv(((std::string)appPath.dirPath() + "/assets/sauvegarde_score.txt").c_str(),((std::string)appPath.dirPath() + "/assets/sauvegarde_pseudo.txt").c_str(),(std::string)appPath.dirPath() + "/assets/sauvegarde.txt"),
     _buttons()
{
    size_callback(window_width, window_height);
}
void App::init(){
    std::cout << "Salut, c'est Léo :) Je voulais vous prévenir qu'en appuyrant sur les chiffres en haut de vos claviers \n vous pouvez maintenant changer de scences (menu, pause etc...) ca va de 1 à 5." << std::endl;
    // CAMERA
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // load models
    // -----------
    Model steve(((std::string)_appPath.dirPath() + "/assets/obj/steve/scene.gltf").c_str());
    _models.push_back(steve);
    std::cout << "Taille de Steve: " << steve.getHeight() << std::endl;
    Model diamond (((std::string)_appPath.dirPath() + "/assets/obj/diamond/scene.gltf").c_str());
    _models.push_back(diamond);
    Model hud(((std::string)_appPath.dirPath() + "/assets/obj/hud/scene.gltf").c_str());
    _models.push_back(hud);
    Model cube(((std::string)_appPath.dirPath() + "/assets/obj/cube/cube.obj").c_str());
    _models.push_back(cube);


    Enemy zombie(((std::string)_appPath.dirPath() + "/assets/obj/zombie/scene.gltf").c_str(),glm::vec3(1.3,0.1,-1),glm::vec3(0.06f, 0.06f, 0.06f));
    _enemies.push_back(zombie);
    Enemy creeper(((std::string)_appPath.dirPath() + "/assets/obj/creeper/scene.gltf").c_str(),glm::vec3(1,0.5,0),glm::vec3(0.06f, 0.06f, 0.06f));
    _enemies.push_back(creeper);
    Enemy enderMan(((std::string)_appPath.dirPath() + "/assets/obj/enderman/scene.gltf").c_str(),glm::vec3(1.8,-0.5,1),glm::vec3(0.05f, 0.05f, 0.05f));
    _enemies.push_back(enderMan);
    std::cout << _map.getSecondFloor().size() << " =? " << 128*128 << std::endl;

    for(unsigned int i = 0; i<10;i++){
        if(i%2){
            _collectibles.emplace_back(((std::string)_appPath.dirPath() + "/assets/obj/diamond/scene.gltf").c_str(), glm::vec3(124.0f-i, 0.6f, 10.0f), 0, 10);
        }
        else
        _collectibles.emplace_back(((std::string)_appPath.dirPath() + "/assets/obj/emerald/scene.gltf").c_str(), glm::vec3(124.0f-i, 0.6f, 10.0f), 0,50);
    }
    _collectibles.emplace_back(((std::string)_appPath.dirPath() + "/assets/obj/apple/scene.gltf").c_str(), glm::vec3(114.0f, 0.6f, 10.0f), 1);

    initButtons();
    // SKYBOX SHADER BINDING
    _skyboxShader.activate();
    glUniform1i(glGetUniformLocation(_skyboxShader._id,"skybox"),0);
}

void App::render(GLFWwindow* window, double FPS) {
    //CODE IN GAMESCENE.cpp

    switch (getScene()) {
        case 0:
            //mENU OF THE GAME
            renderMainMenu(window, FPS);
            break;
        case 1:
            //GAME ITSELF
            renderGame(window, FPS);
            break;
        case 2:
            //PAUSE MENU
            renderPauseMenu(window, FPS);
            break;
        case 3:
            //END GAME (LOOSE CASE)
            renderLooseScreen(window, FPS);
            break;
        case 4:
            //END GAME (WIN CASE)
            renderWinScreen(window, FPS);
            break;
        default:
            assert((bool) "pas possible");
            break;
    }

}

void App::key_callback(int key, /*int scancode,*/ int action/*, int mods*/)
{

    //SCENE SELECTION
    if(action == GLFW_PRESS){
        switch (key) {
            case 49:
                //SET TO MAIN MENU SCENE
                //std::cout << "scene menu" << std::endl;
                setScene(0);
                break;
            case 50:
                //SET GAME SCENE
//                std::cout << "scene jeu" << std::endl;
                setScene(1);
                break;
            case 51:
                //SET PAUSE MENU SCENE
//                std::cout << "scene pause" << std::endl;
                setScene(2);
                break;
            case 52:
                //SET LOOSE SCENE
//                std::cout << "scene loose" << std::endl;
                setScene(3);
                break;
            case 53:
                //SET WIN SCENE
//                std::cout << "scene win" << std::endl;
                setScene(4);
                break;
        }
    }


 std::cout << key << std::endl;
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
    if(key == 292 && action == GLFW_PRESS){
        invertFPSShow();
    }

    if(key == 256 && action == GLFW_PRESS){
        setScene(2);
    }

}

void App::mouse_button_callback(int button, int action, int mods, GLFWwindow* window)
{

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xPos, yPos;
        //getting cursor position
        glfwGetCursorPos(window, &xPos, &yPos);

        for(auto &b:_buttons){
            double y = _height - yPos;
            if(b.isHovered(xPos, y)){
                std::cout << "clicked" << std::endl;
                b._clickCallback();
                b.changeBackgroundColor(glm::vec3(1,0,0));
            } else {
                b.changeBackgroundColor(glm::vec3(0.f));
            }
        }
    }


    switch (getScene()) {
        case 0:
            //mENU OF THE GAME

            break;
        case 1:
            //GAME ITSELF

            break;
        case 2:
            //PAUSE MENU

            break;
        case 3:
            //END GAME (LOOSE CASE)

            break;
        case 4:
            //END GAME (WIN CASE)

            break;
        default:
            assert((bool) "pas possible");
            break;
    }
}

void App::scroll_callback(double xOffset, double yOffset)
{
    switch (getScene()) {
        case 0:
            //mENU OF THE GAME

            break;
        case 1:
            //GAME ITSELF
            if(!_camera.isCamLocked()) {
                _camera.scrollCallback(xOffset, -yOffset);
            }
            break;
        case 2:
            //PAUSE MENU

            break;
        case 3:
            //END GAME (LOOSE CASE)

            break;
        case 4:
            //END GAME (WIN CASE)

            break;
        default:
            assert((bool) "pas possible");
            break;
    }

}

void App::cursor_position_callback(double xPos, double yPos, GLFWwindow* window)
{

    //yPos = _height - yPos;

    for(auto &b:_buttons){
        double y = _height - yPos;
        if(b.isHovered(xPos, y)){
            std::cout << "hovered" << std::endl;

            b.changeBackgroundColor(glm::vec3(0.5f));
        } else {
            b.changeBackgroundColor(glm::vec3(0.f));
        }
    }


    switch (getScene()) {
        case 0:
            //MENU OF THE GAME

            break;
        case 1:
            //GAME ITSELF
            glfwSetCursorPos(window,(float)_width/2,(float)_height/2);
            //IT CAN ONLY ROTATE WHEN THE USER WANT
            if(!_camera.isCamLocked()){
                float rotX = _camera.getSensitivity() * (float)(yPos - ((float)_height/2))/(float)_height;
                float rotY = _camera.getSensitivity() * (float)(xPos- ((float)_width/2))/(float)_width;

                _camera.rotateLeft(rotY);
                _camera.rotateUp(rotX);
            }
            break;
        case 2:
            //PAUSE MENU

            break;
        case 3:
            //END GAME (LOOSE CASE)

            break;
        case 4:
            //END GAME (WIN CASE)

            break;
        default:
            assert((bool) "pas possible");
            break;
    }


}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}



void App::initButtons(){

    std::function<void (void)> functionPlay = [=]() {
        std::cout << 'lel' << std::endl;
        this->setScene(1);
    };
    Button playButton("Launch game !",_height,_width,_width/2,250.f,40.f,20.f,0.7f,glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,1.f,1.f),_textArial,_textShader,_buttonShader, functionPlay );
    _buttons.push_back(playButton);

    std::function<void (void)> functionLeave = [=]() {
        this->closeGame();
    };
    Button leaveButton("Leave game !",_height,_width,_width/2,150.f,40.f,20.f,0.7f,glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,1.f,1.f),_textArial,_textShader,_buttonShader, functionLeave );
    _buttons.push_back(leaveButton);

    Button resumeButton("Go back to game",_height,_width,_width/2,250.f,40.f,20.f,0.7f,glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,1.f,1.f),_textArial,_textShader,_buttonShader, functionPlay );
    _buttons.push_back(resumeButton);
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