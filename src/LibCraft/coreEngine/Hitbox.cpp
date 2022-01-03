//
// Created by leodlplq on 22/12/2021.
//

#include "LibCraft/coreEngine/include/Hitbox.hpp"

Hitbox::Hitbox(Model &model,const glm::vec3 &position, const float &scale)
{
    //TODO : define the good position of each corner.
    float heightModel = model.getHeight()*scale;
    float widthModel = model.getWidth()*scale;

    _corner1 = glm::vec3(
            position.x + (widthModel / 2),
            position.y + (heightModel / 2),
            position.z + (widthModel / 2));

    _corner2 = glm::vec3(
            position.x - (widthModel / 2),
            position.y - (heightModel / 2),
            position.z - (widthModel / 2));

    std::vector<Vertex> vertices = {
            Vertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 0        7--------6
            Vertex(glm::vec3(0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 1        /|       /|
            Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 2      4--------5 |
            Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 3     | |      | |
            Vertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 4       | 3------|-2
            Vertex(glm::vec3(0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)), // SOMMET 5        |/       |/
            Vertex(glm::vec3(0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 6       0--------1
            Vertex(glm::vec3(-0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)) // SOMMET 7
    };
}


bool Hitbox::pointInBox(const glm::vec3 &point) const{
    return (point.x <= _corner1.x && point.x >= _corner2.x) &&
           (point.y <= _corner1.y && point.y >= _corner2.y) &&
           (point.z <= _corner1.z && point.z >= _corner2.z);
}

bool Hitbox::intersect(const Hitbox &otherBox) const {
    return (otherBox.pointInBox(_corner2) || otherBox.pointInBox(_corner1));
}



