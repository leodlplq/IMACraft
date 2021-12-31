//
// Created by valen on 31/12/2021.
//
#include "App.hpp"

void App::KeyBoardListener(GLFWwindow* window){

    if(_key != _keypressed){
        _i+=1;
        if(_i==50){
            _keypressed = GLFW_KEY_0;
            _i = 0;
            _key = _keypressed;
        }
    }

    if(glfwGetKey(window,GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
        if (_keypressed != GLFW_KEY_BACKSPACE) {
            if (!_pseudo.empty()) {
                _pseudo.erase(_pseudo.size() - 1);
                _keypressed = GLFW_KEY_BACKSPACE;
            }
        }
    }
        if (_pseudo.size() < 9) {

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_SPACE) {
                    _pseudo += " ";
                    _keypressed = GLFW_KEY_SPACE;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_Q) {
                    _pseudo += "A";
                    _keypressed = GLFW_KEY_Q;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_W) {
                    _pseudo += "Z";
                    _keypressed = GLFW_KEY_W;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_E) {
                    _pseudo += "E";
                    _keypressed = GLFW_KEY_E;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_R) {
                    _pseudo += "R";
                    _keypressed = GLFW_KEY_R;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_T) {
                    _pseudo += "T";
                    _keypressed = GLFW_KEY_T;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_Y) {
                    _pseudo += "Y";
                    _keypressed = GLFW_KEY_Y;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_U) {
                    _pseudo += "U";
                    _keypressed = GLFW_KEY_U;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_I) {
                    _pseudo += "I";
                    _keypressed = GLFW_KEY_I;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_O) {
                    _pseudo += "O";
                    _keypressed = GLFW_KEY_O;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_P) {
                    _pseudo += "P";
                    _keypressed = GLFW_KEY_P;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_A) {
                    _pseudo += "Q";
                    _keypressed = GLFW_KEY_A;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_S) {
                    _pseudo += "S";
                    _keypressed = GLFW_KEY_S;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_D) {
                    _pseudo += "D";
                    _keypressed = GLFW_KEY_D;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_F) {
                    _pseudo += "F";
                    _keypressed = GLFW_KEY_F;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_G) {
                    _pseudo += "G";
                    _keypressed = GLFW_KEY_G;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_H) {
                    _pseudo += "H";
                    _keypressed = GLFW_KEY_H;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_J) {
                    _pseudo += "J";
                    _keypressed = GLFW_KEY_J;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_K) {
                    _pseudo += "K";
                    _keypressed = GLFW_KEY_K;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_L) {
                    _pseudo += "L";
                    _keypressed = GLFW_KEY_L;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_SEMICOLON) {
                    _pseudo += "M";
                    _keypressed = GLFW_KEY_SEMICOLON;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_Z) {
                    _pseudo += "W";
                    _keypressed = GLFW_KEY_Z;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_X) {
                    _pseudo += "X";
                    _keypressed = GLFW_KEY_X;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_C) {
                    _pseudo += "C";
                    _keypressed = GLFW_KEY_C;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_V) {
                    _pseudo += "V";
                    _keypressed = GLFW_KEY_V;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_B) {
                    _pseudo += "B";
                    _keypressed = GLFW_KEY_B;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
                if (_keypressed != GLFW_KEY_N) {
                    _pseudo += "N";
                    _keypressed = GLFW_KEY_N;
                }
            }
        }
    }



