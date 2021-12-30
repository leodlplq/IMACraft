//
// Created by leodlplq on 29/12/2021.
//

#include "include/Text.hpp"

Text::Text(const FilePath &filePath, const int width, const int height, const std::string fontName):
_wHeight(height), _wWidth(width), _fontName(fontName)
{
    init(filePath);
}

void Text::init(const FilePath &filePath) {


    std::cout << "init text broo" << std::endl;
    FT_Library _ft;
    FT_Face _face;

    if (FT_Init_FreeType(&_ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        assert("Freetype error - ERROR::FREETYPE: Could not init FreeType Library");
    } else {
        std::cout << "freetype loaded" <<std::endl;
    }


    std::string fontDirectory = "/assets/fonts/"+_fontName+".ttf";

    std::string pathToFont = filePath.dirPath() + fontDirectory;
    std::cout << pathToFont<<std::endl;
    if (FT_New_Face(_ft, &pathToFont[0], 0, &_face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font " << _fontName << std::endl;
        assert("Freetype error - ERROR::FREETYPE: Failed to load font");
    } else {
        std::cout << "freetype : arial font loaded " <<std::endl;
    }

    FT_Set_Pixel_Sizes(_face, 0, 48);

    if (FT_Load_Char(_face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        assert("Freetype error - ERROR::FREETYTPE: Failed to load Glyph");
    } else {
        std::cout << "freetype : glyph loaded " <<std::endl;
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                _face->glyph->bitmap.width,
                _face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                _face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
                texture,
                glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<unsigned int>(_face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }


    FT_Done_Face(_face);
    FT_Done_FreeType(_ft);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void Text::renderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color)
{

    //GL MODE TO GET TO RIGHT ONE
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // activate corresponding render state
    s.activate();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_wWidth), 0.0f, static_cast<float>(_wHeight));
    glUniformMatrix4fv(glGetUniformLocation(s._id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(s._id, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //GL MODE TO GET TO RIGHT ONE
    glEnable(GL_DEPTH_TEST);
    glDepthMask(1);
    glDisable(GL_BLEND);
}

float Text::textWidth(std::string text,const float scale){
    float totalWidth = 0;

    std::string::const_iterator c;
    int i = 0;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        float w = static_cast<float>(ch.Size.x) * scale;
        /*std::cout << "|"<<text[i] << "| size : " << w << std::endl;
        i++;*/
        totalWidth += w;
    }

    return totalWidth;
}

float Text::textHeight(std::string text,const float scale){
    float totalHeight = 0;

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        float h = static_cast<float>(ch.Size.y) * scale;

        if(totalHeight < h) totalHeight = h;
    }

    return totalHeight;
}

