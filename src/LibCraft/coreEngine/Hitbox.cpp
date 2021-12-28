//
// Created by leodlplq on 22/12/2021.
//

#include "LibCraft/coreEngine/include/Hitbox.hpp"

Hitbox::Hitbox(ModelCube &model,const glm::vec3 &position) {
    //TODO : define the good position of each corner.
    float heightModel = model.getHeight();
    float widthModel = 1;

    _corner1 = glm::vec3(
            position.x + (widthModel / 2),
            position.y + (heightModel / 2),
            position.z + (widthModel / 2));

    _corner2 = glm::vec3(
            position.x - (widthModel / 2),
            position.y - (heightModel / 2),
            position.z - (widthModel / 2));
}

Hitbox::Hitbox(const Cube &model, const glm::vec3 &position) {
    float heightModel = model.getHeight();
    float widthModel = 1;

    _corner1 = glm::vec3(
            position.x + (widthModel / 2),
            position.y + (heightModel / 2),
            position.z + (widthModel / 2));

    _corner2 = glm::vec3(
            position.x - (widthModel / 2),
            position.y - (heightModel / 2),
            position.z - (widthModel / 2));
}

bool Hitbox::pointInBox(const glm::vec3 &point) const{
    return (point.x <= _corner1.x && point.x >= _corner2.x) &&
           (point.y <= _corner1.y && point.y >= _corner2.y) &&
           (point.z <= _corner1.z && point.z >= _corner2.z);
}

bool Hitbox::intersect(const Hitbox &otherBox) const {
    return (otherBox.pointInBox(_corner2) || otherBox.pointInBox(_corner1));
}



