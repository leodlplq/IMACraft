//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"



void App::renderGame(GLFWwindow *window, double FPS) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // SKYBOX PART | SETUP AND DRAWING
    _skybox.setup(_skyboxShader, _camera, _width, _height);

    _steveShader.activate();
    _camera.Matrix(45.0f, 0.1f, 100.0f);


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
    glUniform3f(glGetUniformLocation(_steveShader._id, "camPos"), _camera.getPosition().x, _camera.getPosition().y,_camera.getPosition().z);

    //HUD
    if (_player.getDistanceToPlayer() != 0) {
        //INPUTS
        _player.Inputs(window);
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
    _player.Draw(_steveShader);

// Collectibles
    for (unsigned int i = 0; i < _collectibles.size(); i++) {
        _collectibles[i].Update(_player);
        _collectibles[i].Draw(_steveShader, _camera);
    }

    //Enemies
    for (unsigned int i = 0; i < _enemies.size(); i++) {
        _enemies[i].DrawEnemy(_player, _camera, _steveShader);
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

    //SECOND FLOOR PART (WALL / JUMP OBSTACLE...)
    for(auto &me:_map.getSecondFloor()){
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

