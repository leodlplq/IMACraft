//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"



void App::renderGame(GLFWwindow *window, double FPS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _player.inMenu(false);
    displayGame(FPS);
    _steveShader.activate();
    //HUD
    if (_player.getDistanceToPlayer() != 0) {
        //INPUTS
        _player.Inputs(window);
        _player.render();
        _hud.DrawHUD(_shaderProgram, _models[2], _models[1], _player.getScore(), _textMinecraft, _textShader,_player.getHp());
    } else { //Switch to GameOver Scene
        setScene(3);
    }
    //PRINTING FPS
    if (_showingFPS) {
        std::string toPrintFPS = "FPS : " + std::to_string(FPS);
        _textArial.renderText(_textShader, toPrintFPS, 25.f, static_cast<float>(_height) - 50.f, 0.5f,
                              glm::vec3(0.5, 0.8f, 0.2f));
    }
    /* VERIF SI ON EST EN TRAIN DE TOURNER
     *
     * SI OUI -- ON AUGMENTE X PAR X JUSQU'A MAX 90
     * SI NON -- ON FAIT RIEN.
     *
     * */
    float valueToRotatePerFrame = 5.f;
    if (_camera.isTurningLeft() && _camera.getCurrentAngleX() < 90) {
        _camera.rotateLeft(-valueToRotatePerFrame);
        _camera.setCurrentAngleX(_camera.getCurrentAngleX() + valueToRotatePerFrame);
    } else if (_camera.isTurningRight() && _camera.getCurrentAngleX() < 90) {
        _camera.rotateLeft(valueToRotatePerFrame);
        _camera.setCurrentAngleX(_camera.getCurrentAngleX() + valueToRotatePerFrame);
    } else {
        _camera.setCurrentAngleX(0.f);
        _camera.setTurningLeft(false);
        _camera.setTurningRight(false);
    }

    if (_player.getHp() == 0) {
        _player.die();
        setScene(3);
    }

    double sizeMap = sqrt((static_cast<double>(_map.getFloor().size())));
    int x = static_cast<int>(round(_player.getPosition().x));
    int y = static_cast<int>(round(_player.getPosition().z));
    int coord = static_cast<int>((x * sizeMap) + y);

    for (auto &me: _map.getSecondFloor()) {

        int xMe = static_cast<int>(round(me.getPosition().x));
        int yMe = static_cast<int>(round(me.getPosition().z));

        int coordMe = static_cast<int>((xMe * sizeMap) + yMe);

        if (coord == coordMe && me.getModel() == 1) {
            _player.die();
        }
    }

    if(_map.getFloor()[static_cast<unsigned long>(coord)].isFinishLine()){
        setScene(4);
    }



}
void App::displayGame(double FPS){
    glm::mat4 model = glm::mat4(1.f);

    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader, _camera, _width, _height);

    _steveShader.activate();
    _camera.Matrix(45.0f, 0.1f, 100.0f);

    //LIGHT
    _light.Draw(_shaderProgram,_models[3],_camera);

    //Player Part
    _steveShader.activate();
    glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(_camera.getProjMatrix() * _camera.getViewMatrix()));
    _player.Draw(_steveShader);

    // Collectibles
    for (auto & _collectible : _collectibles) {
        _collectible.Update(_player);
        _collectible.Draw(_steveShader, _camera);
    }
    //Enemies
    for (auto & _enemie : _enemies) {
        _enemie.DrawEnemy(_player, _camera, _steveShader);
    }


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
    //SECOND FLOOR PART (WALL / DOWN OBSTACLE...)
    for(auto &me:_map.getSecondFloor()){
        if(me.getModel() != -1){
            model = me.getObjectMatrix();
            model = glm::scale(model,glm::vec3(0.5f, 0.5f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
            _modelsMap[static_cast<unsigned long>(me.getModel())].Draw(_steveShader);
        }
    }

    //SECOND FLOOR PART (UP OBSTACLES)
    for(auto &me:_map.getThirdFloor()){
        if(me.getModel() != -1){
            model = me.getObjectMatrix();
            model = glm::scale(model,glm::vec3(0.5f, 0.5f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(_steveShader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
            _modelsMap[static_cast<unsigned long>(me.getModel())].Draw(_steveShader);
        }
    }


    //PRINTING FPS
    if(_showingFPS){
        std::string toPrintFPS = "FPS : " + std::to_string(FPS);
        _textArial.renderText(_textShader, toPrintFPS ,25.f, static_cast<float>(_height) - 50.f, 0.5f, glm::vec3(0.5, 0.8f, 0.2f));
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

}

