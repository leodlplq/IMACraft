//
// Created by leodlplq on 30/12/2021.
//

#include "LibCraft/renderEngine/include/Button.hpp"

Button::Button(std::string text,
               int &windowHeight,
               int &windowWidth,
               int x,
               int y,
               float paddingWidth,
               float paddingHeight,
               float scale,
               glm::vec3 colorBackground,
               glm::vec3 colorText,
               Text &font,
               Shader &shaderText,
               Shader &shaderBackground
                ) :
    _windowHeight(windowHeight),
    _windowWidth(windowWidth),
    _x(x),
    _y(y),
    _paddingWidth(paddingWidth),
    _paddingHeight(paddingHeight),
    _scale(scale),
    _text(text),
    _backgroundColor(colorBackground),
    _textColor(colorText),
    _font(font),
    _shaderText(shaderText),
    _shaderBackground(shaderBackground),
    _vao(),
    _vbo(),
    _ibo()
{
}

void Button::render() {

    int nbSpace = countSpaceInString(_text);

    float spaceWidth = 30.f;
    float missingWidth = spaceWidth * static_cast<float>(nbSpace) * _scale;

    float textHeightTitle = _font.textHeight(_text, _scale);
    float textWidthTitle = _font.textWidth(_text, _scale) + missingWidth;

    float xLeft = (_x) - (textWidthTitle / 2) - _paddingWidth;
    float yLeft = (_y) - (textHeightTitle / 4) - 2*_paddingHeight;

    float width = textWidthTitle + (2*_paddingWidth);
    float height = textHeightTitle + (2*_paddingHeight);

    //CREATE THE BACKGROUND OF THE BUTTON
    //Rectangle backgroundButton(-10, -10, 20, 20,_backgroundColor, _windowWidth, _windowWidth);
    Rectangle backgroundButton(xLeft, yLeft, width, height, _backgroundColor);
    setup(backgroundButton);
    draw(backgroundButton);

    //CREATE THE TEXT OF THE BUTTON
    float yPosTitle = (_y - textHeightTitle);
    float xPosTitle = (_x) - (textWidthTitle / 2);
    _font.renderText(_shaderText, _text, xPosTitle, yPosTitle , _scale, _textColor);

}

void Button::setup(Rectangle &rectangle) {

    std::vector<Vertex> vertices = rectangle.getVertices();
    std::vector<GLuint> indices = rectangle.getIndices();



    _vao.bind();
    _vbo = vbo(&vertices[0], static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)));
    //_ibo = ibo(&indices[0], static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Normal));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, TexCoords));
    _vao.unbind();
    _vbo.unbind();
    //_ibo.unbind();

}

void Button::draw(Rectangle &rect) {

    _shaderBackground.activate();
    float scale = 1;
    float widthProj = (static_cast<float>(_windowWidth) / scale);
    float heightProj = (static_cast<float>(_windowHeight) / scale);

    //glm::mat4 projection = glm::mat4(1.f);
    glm::mat4 projection = glm::ortho(0.f, widthProj,0.f, heightProj, -1.f,1.f);
    glUniformMatrix4fv(glGetUniformLocation(_shaderBackground._id, "projection"), 1, GL_FALSE,glm::value_ptr(projection));
    _vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);
    _vao.unbind();
}

bool Button::isHovered(double& xPos, double& yPos) {
    float width = getWidth();
    float height = getHeight();

    glm::vec2 cornerTopLeft = {_x - width/2, _y - (height/2) - _paddingHeight};
    glm::vec2 cornerBottomRight = {_x + width/2, _y + (height/2) - _paddingHeight};

//    std::cout << "x : " << xPos << " y : " << yPos << std::endl;
//    std::cout << "x Corner1 " << cornerTopLeft.x << " y : " << cornerTopLeft.y << std::endl;
//    std::cout << "x Corner2 " << cornerBottomRight.x << " y : " << cornerBottomRight.y << std::endl;


    if(
        (xPos > cornerTopLeft.x && xPos < cornerBottomRight.x) &&
        (yPos > cornerTopLeft.y && yPos < cornerBottomRight.y)
    ){
        return true;
    }

    return false;
}

float Button::getWidth(){
    int nbSpace = countSpaceInString(_text);
    float spaceWidth = 30.f;
    float missingWidth = spaceWidth * static_cast<float>(nbSpace) * _scale;
    float textWidthTitle = _font.textWidth(_text, _scale) + missingWidth;
    return textWidthTitle + (2*_paddingWidth);
}

float Button::getHeight()  {
    float textHeightTitle = _font.textHeight(_text, _scale);
    return textHeightTitle + (2*_paddingHeight);
}
