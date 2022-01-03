//
// Created by valen on 31/12/2021.
//
#include "App.hpp"

void App::KeyBoardListener(GLFWwindow* window){

    if(_key != _keyPressed){
        _i+=1;
        if(_i==50){
            _keyPressed = GLFW_KEY_0;
            _i = 0;
            _key = _keyPressed;
        }
    }

    if(glfwGetKey(window,GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
        if (_keyPressed != GLFW_KEY_BACKSPACE) {
            if (!_pseudo.empty()) {
                _pseudo.erase(_pseudo.size() - 1);
                _keyPressed = GLFW_KEY_BACKSPACE;
            }
        }
    }
        if (_pseudo.size() < 9) {

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_SPACE) {
                    _pseudo += " ";
                    _keyPressed = GLFW_KEY_SPACE;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_Q) {
                    _pseudo += "A";
                    _keyPressed = GLFW_KEY_Q;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_W) {
                    _pseudo += "Z";
                    _keyPressed = GLFW_KEY_W;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_E) {
                    _pseudo += "E";
                    _keyPressed = GLFW_KEY_E;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_R) {
                    _pseudo += "R";
                    _keyPressed = GLFW_KEY_R;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_T) {
                    _pseudo += "T";
                    _keyPressed = GLFW_KEY_T;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_Y) {
                    _pseudo += "Y";
                    _keyPressed = GLFW_KEY_Y;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_U) {
                    _pseudo += "U";
                    _keyPressed = GLFW_KEY_U;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_I) {
                    _pseudo += "I";
                    _keyPressed = GLFW_KEY_I;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_O) {
                    _pseudo += "O";
                    _keyPressed = GLFW_KEY_O;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_P) {
                    _pseudo += "P";
                    _keyPressed = GLFW_KEY_P;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_A) {
                    _pseudo += "Q";
                    _keyPressed = GLFW_KEY_A;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_S) {
                    _pseudo += "S";
                    _keyPressed = GLFW_KEY_S;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_D) {
                    _pseudo += "D";
                    _keyPressed = GLFW_KEY_D;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_F) {
                    _pseudo += "F";
                    _keyPressed = GLFW_KEY_F;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_G) {
                    _pseudo += "G";
                    _keyPressed = GLFW_KEY_G;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_H) {
                    _pseudo += "H";
                    _keyPressed = GLFW_KEY_H;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_J) {
                    _pseudo += "J";
                    _keyPressed = GLFW_KEY_J;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_K) {
                    _pseudo += "K";
                    _keyPressed = GLFW_KEY_K;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_L) {
                    _pseudo += "L";
                    _keyPressed = GLFW_KEY_L;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_SEMICOLON) {
                    _pseudo += "M";
                    _keyPressed = GLFW_KEY_SEMICOLON;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_Z) {
                    _pseudo += "W";
                    _keyPressed = GLFW_KEY_Z;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_X) {
                    _pseudo += "X";
                    _keyPressed = GLFW_KEY_X;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_C) {
                    _pseudo += "C";
                    _keyPressed = GLFW_KEY_C;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_V) {
                    _pseudo += "V";
                    _keyPressed = GLFW_KEY_V;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_B) {
                    _pseudo += "B";
                    _keyPressed = GLFW_KEY_B;
                }
            }
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
                if (_keyPressed != GLFW_KEY_N) {
                    _pseudo += "N";
                    _keyPressed = GLFW_KEY_N;
                }
            }
        }
    }



