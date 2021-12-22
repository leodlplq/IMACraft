//
// Created by leodlplq on 22/12/2021.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Hitbox.hpp"


//RENDER ENGINE
#include "LibCraft/renderEngine/include/Model.hpp"

class MapElement {
private:
    //WHAT KIND OF MODEL IT IS?
    //ex : (not acual)
    //    1 = Grass
    //    2 = Diamond
    //    3 = ...
    //    etc....

    int _modelType;
    glm::vec3 _position;
    Hitbox _hitbox;

public:
    //CONSTRUCTORS
    MapElement() = default;
    /*inline MapElement(int type, int texture, glm::vec3 position) :
        _type(type), _texture(texture), _position(position)
    {};*/
    inline MapElement(int modelType, glm::vec3 position, Model model)
    {
        _modelType = int(modelType);
        _position = glm::vec3(position);

        if(modelType != -1){
            _hitbox = Hitbox(model, position);
        } else {
            //getting rid of void hitbox
            glm::vec3 voidPosition(10000.f, 10000.f, 10000.f);
            _hitbox = Hitbox(model, voidPosition);
        }
    };
    ~MapElement() = default;

    //USEFUL THINGS
    void displayPosition() const{
        std::cout << "element's position is : " <<
            "x" <<_position.x << " | " <<
            "y" <<_position.y << " | " <<
            "z" <<_position.z <<
        std::endl;
    }

    //RETURNING ALL ATTRIBUTES
    /*inline int getType() const{
        return _type;
    }

    inline int getTexture() const{
        return _texture;
    }*/

    inline int getModel() const{
        return _modelType;
    }

    inline glm::vec3 getPosition() const{
        return _position;
    }

    inline glm::mat4 getObjectMatrix() const{
        return glm::translate(glm::mat4(1.f), _position);
    }

    inline Hitbox getHitbox() const{
        return _hitbox;
    }



};

