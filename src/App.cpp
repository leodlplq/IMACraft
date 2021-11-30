#include "App.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include <valarray>


App::App(int window_width, int window_height, FilePath appPath) :
 _vao(),
 _vbo({}, 0),
 _ibo({}, 0),
 _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
 _skyboxShader("assets/shaders/skybox.vs.glsl","assets/shaders/skybox.fs.glsl",appPath),
 _uniId(0),
 _appPath(appPath),
 _textures(),
 _rotation(0.0f),
 _prevTime(0.0f),
 _camera(window_width,window_height,glm::vec3(0.0f,0.0f,0.0f)),
 _width(window_width),
 _height(window_height),
 _player()
{
    size_callback(window_width, window_height);
}
void App::init(){

    _map = Map(_appPath.dirPath() + "/assets/maps/map3.pgm");

    Cube cube;
    _vao.bind();
    _vbo = vbo(cube.getDataPointer(),cube.getVertexCount()*sizeof(Vertex));
    _ibo = ibo(cube.getIndices(), cube.getVertexCount()*sizeof (GLuint));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, texCoords));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();

    //PLAYER
    _player = Player(cube, glm::vec3(0.f, 0.0f, 0.f));

    //TEXTURE
    std::string filePathGrassSide = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/side.jpg");
    std::string filePathGrassTop = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/top.jpg");
    std::string filePathGrassBottom = ((std::string)_appPath.dirPath() + "/assets/textures/grass_cube/bottom.jpg");
    TextureCube grass(&filePathGrassSide[0],&filePathGrassSide[0],&filePathGrassTop[0],&filePathGrassBottom[0],&filePathGrassSide[0],&filePathGrassSide[0], GL_RGB);
    grass.texUnit(_shaderProgram,"tex0",0);
    _textures.push_back(grass);

    std::string filePathWood = ((std::string)_appPath.dirPath() + "/assets/textures/player/side.png");
    TextureCube player(&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0],&filePathWood[0], GL_RGBA);
    player.texUnit(_shaderProgram,"tex0",0);
    _textures.push_back(player);

    glEnable(GL_DEPTH_TEST);
    std::cout << _width << _height << std::endl;
    _camera = Camera(_width,_height,glm::vec3(0.0f,0.0f,0.0f));

    _skyboxShader.activate();
    glUniform1i(glGetUniformLocation(_skyboxShader._id,"skybox"),0);
}

void App::render(GLFWwindow* window)
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    _shaderProgram.activate();
    _camera.Inputs(window);
    _player.Inputs(window);
    _player.render();
    _camera.Matrix(45.0f,0.1f,100.0f,_shaderProgram);

    int matrixID = glGetUniformLocation(_shaderProgram._id,"camMatrix");
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(_camera.getModelMatrix()));
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(_camera.getProjMatrix()*_camera.getViewMatrix()));

    // Bind the VAO so OpenGL knows to use it
    _vao.bind();

    _textures[1].bind();
    // DRAW OUR PLAYER FOR TESTING
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,_player.getPosition());
    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    _textures[0].bind();

    for(auto &cube:_map.getMap()){
        glm::mat4 model = glm::mat4 (1.0f);
        model = cube.getObjectMatrix();
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));

        _textures[0].bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    // DRAW ANOTHER CUBE FOR TESTING
    //glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model,glm::vec3(2.0f,0.0f,0.0f));
    //glUniformMatrix4fv(glGetUniformLocation(_shaderProgram._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);





    // SKYBOX PART
    glDepthFunc(GL_LEQUAL);
    _skyboxShader.activate();
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(glm::lookAt(_camera._position, _camera._position + _camera._orientation, _camera._up)));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)_width / _height, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(_skyboxShader._id, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(_skyboxShader._id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
    // where an object is present (a depth of 1.0f will always fail against any object's depth value)

    _vao.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox._cubemapTexture);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Switch back to the normal depth function
    glDepthFunc(GL_LESS);
}

App::~App(){
    _vao.deleteVao();
    _vbo.deleteVbo();
    _ibo.deleteIbo();
    for(auto &item : _textures){
        item.deleteTex();
    }
    _shaderProgram.deleteShader();
    _skyboxShader.deleteShader();

}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/)
{
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}