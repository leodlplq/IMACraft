#include "App.hpp"
#include "GLFW/glfw3.h"

#include <iostream>
#include <valarray>

App::App(int window_width, int window_height, FilePath appPath) :
 _vao(), _vbo({}, 0), _ibo({}, 0), _shaderProgram("assets/shaders/shader.vs.glsl","assets/shaders/shader.fs.glsl" , appPath), _uniId(0)
{
    size_callback(window_width, window_height);
}
void App::init(){


    // Vertices coordinates
    GLfloat vertices[] =
            {               //POSITION                                              //COLORS
                    -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
                    0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
                    0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
                    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
                    0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
                    0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
            };

    GLuint indices[] = {
            0, 3, 5,
            3, 2, 4,
            5, 4, 1
    };



    _vao.bind();

    _vbo = vbo(vertices, sizeof(vertices));
    _ibo = ibo(indices, sizeof(indices));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, 6 * sizeof (float), (void*)0);
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, 6 * sizeof (float), (void*)(3* sizeof(float)));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();

    _uniId = glGetUniformLocation(_shaderProgram._id, "scale");

}

void App::render()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    _shaderProgram.activate();
    glUniform1f(_uniId, 0.5f);
    // Bind the VAO so OpenGL knows to use it
    _vao.bind();
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


}

App::~App(){

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