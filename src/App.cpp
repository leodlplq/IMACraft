#include "App.hpp"
#include "GLFW/glfw3.h"

App::App(int window_width, int window_height)
{
    size_callback(window_width, window_height);
}
void App::init(){
    glGenBuffers(1, &vbo);

    //binding the vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //vertex of the triangle
    GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(1, 0);

    //VAO
    glGenVertexArrays(1, &vao);

    //binding the vao;
    glBindVertexArray(vao);
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(1, 0);

    glBindVertexArray(0);
}

void App::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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