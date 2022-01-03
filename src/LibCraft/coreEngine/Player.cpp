//
// Created by leodlplq on 26/11/2021.
//
#include "include/Player.hpp"

Player::Player( Model model, const glm::vec3 &spawnPos, float scale, const Map& map,Model modelDead):
_position(spawnPos), _spawnPos(spawnPos), _scale(scale), _facingDirection('N'), _model(model),_modelDead(modelDead),_modelAlive(model), _hitbox(model, spawnPos,scale), _hitbox2(model, spawnPos + glm::vec3(0,1,0),scale),_hp(10),_map(map)
{
}

void Player::die() {
    _hp = 0;
    _model = _modelDead;
}

void Player::Draw(Shader &shader) {
    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0));
    switch(_facingDirection){
        case 'N':
            model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 0, 1));
            break;
        case 'S':
            model = glm::rotate(model, glm::radians(90.f), glm::vec3(0, 0, 1));
            break;
        case 'E':
            model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));
            break;
    }
    if(_hp == 0){
        model = glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));
        model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
        model = glm::scale(model,glm::vec3(0.07f));
    }
    else{
        model = glm::scale(model,glm::vec3(_scale));
    }

    if(_sliding){
        model = glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));
        model = glm::rotate(model, glm::radians(-180.f), glm::vec3(0, 1, 0));
    }

    glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    _model.Draw(shader);
}



void Player::startJump(){
    if(_onGround){
        _velocityY = 10.f;
        _onGround = false;
        _sliding = false;
    }
    //_position -= glm::vec3(0.f, 1.f, 0.f);
}

void Player::slide() {
    if(!_sliding && _onGround){
        _velocitySlide = 10.f;
        _sliding = true;
    }
}


//MOVEMENT OF THE PLAYER
void Player::moveRight() {
    glm::vec3 displacementRight = _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
    _position += displacementRight;

    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementRight;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementRight;
    _hitbox.setCorner2( newCorner2 );

    glm::vec3 newCorner12 = _hitbox2.getCorner1() + displacementRight;
    _hitbox2.setCorner1( newCorner12 );
    glm::vec3 newCorner22 = _hitbox2.getCorner2() + displacementRight;
    _hitbox2.setCorner2( newCorner22 );
}

void Player::moveLeft() {
    glm::vec3 displacementLeft = _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
    _position -= displacementLeft;

    glm::vec3 newCorner1 = _hitbox.getCorner1() - displacementLeft;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() - displacementLeft;
    _hitbox.setCorner2( newCorner2 );

    glm::vec3 newCorner12 = _hitbox2.getCorner1() - displacementLeft;
    _hitbox2.setCorner1( newCorner12 );
    glm::vec3 newCorner22= _hitbox2.getCorner2() - displacementLeft;
    _hitbox2.setCorner2( newCorner22 );
}

void Player::moveForward(){

    //PLAYER MOVEMENT
    glm::vec3 displacementForward = _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    _position += displacementForward;

    //PLAYER'S HITBOX MOVEMENT
    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementForward;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementForward;
    _hitbox.setCorner2( newCorner2 );

    glm::vec3 newCorner12 = _hitbox2.getCorner1() + displacementForward;
    _hitbox2.setCorner1( newCorner12 );
    glm::vec3 newCorner22 = _hitbox2.getCorner2() + displacementForward;
    _hitbox2.setCorner2( newCorner22);
}

/*void Player::moveBackward(){
    glm::vec3 displacementBackward = _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    _position -= displacementBackward;

    //PLAYER'S HITBOX MOVEMENT
    glm::vec3 newCorner1 = _hitbox.getCorner1() - displacementBackward;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() - displacementBackward;
    _hitbox.setCorner2( newCorner2 );

    glm::vec3 newCorner12 = _hitbox2.getCorner1() - displacementBackward;
    _hitbox2.setCorner1( newCorner12 );
    glm::vec3 newCorner22 = _hitbox2.getCorner2() - displacementBackward;
    _hitbox2.setCorner2( newCorner22 );
}*/

void Player::render(){

    //JUMP PART
    _velocityY -= _gravity;
    glm::vec3 displacementJump = (_speedJump * _velocityY) * glm::vec3(0.f, 1.f, 0.f);
    _position += displacementJump;

    //PLAYER'S HITBOX PART
    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementJump;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementJump;
    _hitbox.setCorner2( newCorner2 );

    glm::vec3 newCorner12 = _hitbox2.getCorner1() + displacementJump;
    _hitbox2.setCorner1( newCorner12 );
    glm::vec3 newCorner22 = _hitbox2.getCorner2() + displacementJump;
    _hitbox2.setCorner2( newCorner22 );


    if(_position.y < 1.3f){ //STAYING ON THE GROUND AND NOT FALLING INTO INFINTY

        glm::vec3 newCorner1 = glm::vec3(_hitbox.getCorner1().x, 1.5f, _hitbox.getCorner1().z);
        _hitbox.setCorner1( newCorner1 );
        glm::vec3 newCorner2 = glm::vec3(_hitbox.getCorner2().x, 0.5f, _hitbox.getCorner2().z);
        _hitbox.setCorner2( newCorner2 );

        glm::vec3 newCorner11 = glm::vec3(_hitbox2.getCorner1().x, 2.5f, _hitbox2.getCorner1().z);
        _hitbox2.setCorner1( newCorner11 );
        glm::vec3 newCorner21 = glm::vec3(_hitbox2.getCorner2().x, 1.5f, _hitbox2.getCorner2().z);
        _hitbox2.setCorner2( newCorner21 );

        _position.y = 1.3f;
        _velocityY = 0.f;
        _onGround = true;
    }

    if(_sliding){
        _velocitySlide -= _friction;

        glm::vec3 newCorner1 = glm::vec3(_hitbox.getCorner1().x, 1.3f, _hitbox.getCorner1().z);
        _hitbox.setCorner1( newCorner1 );
        glm::vec3 newCorner2 = glm::vec3(_hitbox.getCorner2().x, 0.5f, _hitbox.getCorner2().z);
        _hitbox.setCorner2( newCorner2 );

        glm::vec3 newCorner11 = glm::vec3(_hitbox2.getCorner1().x, 1.3f, _hitbox2.getCorner1().z);
        _hitbox2.setCorner1( newCorner11 );
        glm::vec3 newCorner21 = glm::vec3(_hitbox2.getCorner2().x, 1.3f, _hitbox2.getCorner2().z);
        _hitbox2.setCorner2( newCorner21 );

        if(_velocitySlide <= 0.f ){
            _sliding = false;
            _velocityY = 0.f;
        }

    }

    if(_isColliding){
        if(_hasCollided != _isColliding){
            looseHP();
            _hasCollided = _isColliding;
        }
    }
    else{
        _hasCollided = false;
    }


}

void Player::Inputs(GLFWwindow *window) {

    //(x * 128)+y TO GET 2D VECTOR WITH JUST 1D VECTOR.
    //glfwGetKey(window,87) == GLFW_PRESS  OR TRUE

    //GOING FORWARD
    if(_hp!=0){ //GOING FORWARD
        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourRX;
        int nextBlockNeighbourRY;
        int nextBlockNeighbourLX;
        int nextBlockNeighbourLY;

        switch (getFacingDirection()) {
            case 'N':
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                //RIGHT
                nextBlockNeighbourRX = -1;
                nextBlockNeighbourRY = -1;
                //LEFT
                nextBlockNeighbourLX = -1;
                nextBlockNeighbourLY = 1;
                break;
            case 'S':
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                //RIGHT
                nextBlockNeighbourRX = 1;
                nextBlockNeighbourRY = 1;
                //LEFT
                nextBlockNeighbourLX = 1;
                nextBlockNeighbourLY = -1;
                break;
            case 'W':
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                //RIGHT
                nextBlockNeighbourRX = -1;
                nextBlockNeighbourRY = 1;
                //LEFT
                nextBlockNeighbourLX = 1;
                nextBlockNeighbourLY = 1;
                break;

            case 'E':
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                //RIGHT
                nextBlockNeighbourRX = 1;
                nextBlockNeighbourRY = -1;
                //LEFT
                nextBlockNeighbourLX = -1;
                nextBlockNeighbourLY = -1;
                break;
            default:
                assert("y'a autres choses frro");

                break;
        } // WHICH DIRECTION IT GOES

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(getPosition().x));
        int yPlayer = static_cast<int>(round(getPosition().z));
        int x =  xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;

        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();
        Hitbox blockHitboxUp = _map.getThirdFloor()[static_cast<unsigned long>(coord)].getHitbox();

        //RIGHT NEIGHBOUR
        int neiX = xPlayer + nextBlockNeighbourRX;
        int neiY = yPlayer + nextBlockNeighbourRY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();
        Hitbox neiBlockHitboxUp = _map.getThirdFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();
        //LEFT NEIGHBOUR
        int neiX2 = xPlayer + nextBlockNeighbourLX;
        int neiY2 = yPlayer + nextBlockNeighbourLY;
        int neiCoord2 = static_cast<int>((neiX2 * sizeMap) + neiY2);
        Hitbox neiBlockHitbox2 = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord2)].getHitbox();
        Hitbox neiBlockHitbox2Up = _map.getThirdFloor()[static_cast<unsigned long>(neiCoord2)].getHitbox();




        bool playerBlock = !getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !getHitbox().intersect(neiBlockHitbox);
        bool playerBlockNei2 = !getHitbox().intersect(neiBlockHitbox2);

        bool playerBlockUp = !getHitbox2().intersect(blockHitboxUp);
        bool playerBlockNeiUp = !getHitbox2().intersect(neiBlockHitboxUp);
        bool playerBlockNei2Up = !getHitbox2().intersect(neiBlockHitbox2Up);

        bool playerBlockUp2 = !getHitbox().intersect(blockHitboxUp);
        bool playerBlockNeiUp2 = !getHitbox().intersect(neiBlockHitboxUp);
        bool playerBlockNei2Up2 = !getHitbox().intersect(neiBlockHitbox2Up);


        bool noCollisionBottom = (playerBlock && playerBlockNei  && playerBlockNei2) ||
                               (playerBlock && playerBlockNei  && !playerBlockNei2 && blockHitbox.getCorner1().x == 10000.5) ||
                               (playerBlock && !playerBlockNei  && playerBlockNei2 && blockHitbox.getCorner1().x == 10000.5);

        bool noCollisionUp = (playerBlockUp && playerBlockNeiUp  && playerBlockNei2Up) ||
                               (playerBlockUp && playerBlockNeiUp  && !playerBlockNei2Up && blockHitboxUp.getCorner1().x == 10000.5) ||
                               (playerBlockUp && !playerBlockNeiUp  && playerBlockNei2Up && blockHitboxUp.getCorner1().x == 10000.5);

        bool noCollisionUp2 = (playerBlockUp2 && playerBlockNeiUp2  && playerBlockNei2Up2) ||
                             (playerBlockUp2 && playerBlockNeiUp2  && !playerBlockNei2Up2 && blockHitboxUp.getCorner1().x == 10000.5) ||
                             (playerBlockUp2 && !playerBlockNeiUp2  && playerBlockNei2Up2 && blockHitboxUp.getCorner1().x == 10000.5);

        //std::cout << "bot : " << (noCollisionBottom ? "yes ": "no ") << "|" << "up : " <<( noCollisionUp ?"yes ": "no ") << "|" << "up2 : " <<( noCollisionUp2 ?"yes ": "no ") << "|" << std::endl;

        if(noCollisionUp && noCollisionBottom && noCollisionUp2){
            moveForward();
            _isColliding = false;
        } else {
            _isColliding = true;

        }


    }

    //GOING LEFT
    if(glfwGetKey(window, 65) == GLFW_PRESS && _hp!=0){ // MOVEMENT TO THE LEFT
        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourX;
        int nextBlockNeighbourY;
        switch (getFacingDirection()) {
            case 'N':
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'S':
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'W':
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'E':
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            default:
                assert("y'a pas a etre ici ????!");
                break;
        }

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(getPosition().x));
        int yPlayer = static_cast<int>(round(getPosition().z));

        int x = xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;
        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();
        int neiX = xPlayer + nextBlockNeighbourX;
        int neiY = yPlayer + nextBlockNeighbourY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();

        bool playerBlock = !getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !getHitbox().intersect(neiBlockHitbox);

        /*if(playerBlock &&  playerBlockNei){
            _player.moveLeft();
        }*/
        if(
                (playerBlock &&  playerBlockNei) ||
                (playerBlock &&  !playerBlockNei && blockHitbox.getCorner1().x == 10000.5)
                ){
            if(!_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
                moveLeft();
            }

        }



    }
    if(glfwGetKey(window, 68) == GLFW_PRESS && _hp!=0){ //GOING RIGHT

        int nextBlockPosX;
        int nextBlockPosY;
        int nextBlockNeighbourX;
        int nextBlockNeighbourY;
        switch (getFacingDirection()) {
            case 'N': //WHEN GOING LEFT Z INCREASE
                nextBlockPosX = 0;
                nextBlockPosY = -1;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'S': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = 0;
                nextBlockPosY = 1;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            case 'W': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = -1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = -1;
                nextBlockNeighbourY = -1;
                break;
            case 'E': //WHEN GOING LEFT Z DECREASE
                nextBlockPosX = 1;
                nextBlockPosY = 0;
                nextBlockNeighbourX = 1;
                nextBlockNeighbourY = 1;
                break;
            default: // if it is not N or S then it's W or E and it's a 0;
                assert("y'a pas a etre ici ????!");
                break;
        }

        double sizeMap = sqrt((static_cast<double>(_map.getSecondFloor().size())));

        int xPlayer = static_cast<int>(round(getPosition().x));
        int yPlayer = static_cast<int>(round(getPosition().z));
        //std::cout << "-------------DIRECTION : " << getFacingDirection() << " -------------"<< std::endl;
        int x = xPlayer + nextBlockPosX;
        int y = yPlayer + nextBlockPosY;
        int coord = static_cast<int>((x * sizeMap) + y);
        Hitbox blockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(coord)].getHitbox();

        int neiX = xPlayer + nextBlockNeighbourX;
        int neiY = yPlayer + nextBlockNeighbourY;
        int neiCoord = static_cast<int>((neiX * sizeMap) + neiY);
        Hitbox neiBlockHitbox = _map.getSecondFloor()[static_cast<unsigned long>(neiCoord)].getHitbox();

        bool playerBlock = !getHitbox().intersect(blockHitbox);
        bool playerBlockNei = !getHitbox().intersect(neiBlockHitbox);

        if(
                (playerBlock &&  playerBlockNei) ||
                (playerBlock &&  !playerBlockNei && blockHitbox.getCorner1().x == 10000.5)
                ){
            if(!_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
                moveRight();
            }
        }

    }

//    if(glfwGetKey(window,83) == GLFW_PRESS && _hp!=0){ //GOING BACKWARD
//        moveBackward();
//    }

}

void Player::turnLeft() {
    int xPlayer = static_cast<int>(round(getPosition().x));
    int yPlayer = static_cast<int>(round(getPosition().z));

    int coord = static_cast<int>((xPlayer * _map.getSize()) + yPlayer);

    if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection() && _isInMenu == false) {
        setOrientationRotation(90.f);
        switch (getFacingDirection()) {
            case 'N':
                setFacingOrientation('W');
                break;
            case 'W':
                setFacingOrientation('S');
                break;
            case 'S':
                setFacingOrientation('E');
                break;
            case 'E':
                setFacingOrientation('N');
                break;
        }
    }
}

void Player::turnRight() {
    int xPlayer = static_cast<int>(round(getPosition().x));
    int yPlayer = static_cast<int>(round(getPosition().z));

    int coord = static_cast<int>((xPlayer * _map.getSize()) + yPlayer);

    if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection() && _isInMenu == false) {
        setOrientationRotation(-90.f);
        switch (getFacingDirection()) {
            case 'N':
                setFacingOrientation('E');
                break;
            case 'W':
                setFacingOrientation('N');
                break;
            case 'S':
                setFacingOrientation('W');
                break;
            case 'E':
                setFacingOrientation('S');
                break;
        }
    }
}






/*--------------------- PRESSE PAPIER ------------------*/

/*display();
        //std::cout << "-------------DIRECTION : " << getFacingDirection() << " -------------"<< std::endl;
        std::cout << "------------ PLAYER H2-------------" << std::endl;
        getHitbox2().display();
        std::cout << "------------ BLOCK -------------" << std::endl;
        blockHitboxUp.display();
        std::cout << (getHitbox2().intersect(blockHitboxUp) ? "collision" : "no collision")<< std::endl;
        std::cout << "------------ BLOCK B -------------" << std::endl;
        blockHitbox.display();
        std::cout << (getHitbox().intersect(blockHitbox) ? "collision" : "no collision")<< std::endl;

        std::cout << "------------ OTHER BLOCK -------------" << std::endl;
        neiBlockHitboxUp.display();
        std::cout << (getHitbox2().intersect(neiBlockHitboxUp) ? "collision" : "no collision")<< std::endl;
        std::cout << "------------ OTHER BLOCK B -------------" << std::endl;
        neiBlockHitbox.display();
        std::cout << (getHitbox().intersect(neiBlockHitbox) ? "collision" : "no collision")<< std::endl;

        std::cout << "------------ OTHER BLOCK -------------" << std::endl;
        neiBlockHitbox2Up.display();
        std::cout << (getHitbox2().intersect(neiBlockHitbox2Up) ? "collision" : "no collision")<< std::endl;
        std::cout << "------------ OTHER BLOCK B -------------" << std::endl;
        neiBlockHitbox2.display();
        std::cout << (getHitbox().intersect(neiBlockHitbox2) ? "collision" : "no collision")<< std::endl;*/

