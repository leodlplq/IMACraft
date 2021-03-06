//
// Created by leodlplq on 22/12/2021.
//

#pragma once

#include <glm/glm.hpp>

//RENDER ENGINE
#include "LibCraft/renderEngine/include/Model.hpp"
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/renderEngine/include/vao.hpp"
#include "LibCraft/renderEngine/include/vbo.hpp"


class Hitbox {
private:
    glm::vec3 _corner1;
    glm::vec3 _corner2;

//      7--------6
//     /|       /|
//    4--------5 |
//    | |      | |
//    | 3------|-2
//    |/       |/
//    0--------1

// 5 is TOPRIGHT corner and correspond to _corner1
// 3 is BOTTOMLEFT corner and correspond to _corner2


public:
    //CONSTRUCTORS & DESTRUCTORS
    Hitbox() =default;
    Hitbox(Model &model, const glm::vec3 &position, const float &scale);
    //Hitbox(const Cube &model, const glm::vec3 &position);
    ~Hitbox() = default;

    //METHODS
    bool pointInBox(const glm::vec3 &point) const;
    bool intersect(const Hitbox &otherBox) const;
    inline void display() const{
        std::cout << "Hitbox corner1 : " << " x : " << _corner1.x  <<" y : " << _corner1.y << " z : " << _corner1.z << std::endl;
        std::cout << "Hitbox corner2 : " << " x : " << _corner2.x  <<" y : " << _corner2.y << " z : " << _corner2.z << std::endl;
    }

    inline glm::vec3 setCorner1(glm::vec3 newCorner){ return _corner1 = newCorner; }
    inline glm::vec3 getCorner1() const{ return _corner1; }

    inline glm::vec3 setCorner2(glm::vec3 newCorner){ return _corner2 = newCorner; }
    inline glm::vec3 getCorner2() const{ return _corner2; }
};

