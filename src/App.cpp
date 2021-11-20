#include "App.hpp"
#include "GLFW/glfw3.h"
#include "Cube.hpp"
#include <iostream>
#include <valarray>

App::App(int window_width, int window_height, FilePath appPath) :
 _vao(),
 _vbo({}, 0),
 _ibo({}, 0),
 _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath),
 _uniId(0),
 _appPath(appPath),
 _textures()
{
    size_callback(window_width, window_height);
}
void App::init(){

    Cube cube;
    _vao.bind();
    _vbo = vbo(cube.getDataPointer(),sizeof(cube.getDataPointer()));
    _ibo = ibo(cube.getIndices(), sizeof(cube.getIndices()));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*)0);
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3* sizeof(float)));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6* sizeof(float)));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();

    _uniId = glGetUniformLocation(_shaderProgram._id, "scale");

    //TEXTURE
    //std::string filePathDirt = ((std::string)_appPath.dirPath() + "/assets/textures/dirt.jpg");

    //Texture dirt(&filePathDirt[0], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE); //GL_RGB == JPG file, GL_RGBA == PNG file
    //dirt.texUnit(_shaderProgram, "tex0", 0);
    //_textures.push_back(dirt);
}

void App::render()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    _shaderProgram.activate();
    glUniform1f(_uniId, 0.5f);
    //_textures[0].bind();
    // Bind the VAO so OpenGL knows to use it
    _vao.bind();
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

App::~App(){
    _vao.deleteVao();
    _vbo.deleteVbo();
    _ibo.deleteIbo();
    for(auto &item : _textures){
        item.deleteTex();
    }
    _shaderProgram.deleteShader();

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