#include <valarray>
#include "App.hpp"
#include "LibCraft/tools/include/filePath.hpp"

#include <iostream>



static App& get_app(GLFWwindow* window)
{
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}

int main(__attribute__((unused)) int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(1280, 720, "IMACraft", NULL , nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    FilePath appPath(argv[0]);
    /* Create the App */
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    App app{w, h, appPath};

    /* Hook user inputs to the App */
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(&app));
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        get_app(window).key_callback(key, /*scancode,*/ action/*, mods*/);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        get_app(window).mouse_button_callback(button, action, mods, window);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        get_app(window).scroll_callback(xoffset, yoffset);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        get_app(window).cursor_position_callback(xpos, ypos, window);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        get_app(window).size_callback(width, height);
    });

    app.init();
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    double FPS = 0;
    std::cout << w << h << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && app.isGameRunning()) {


        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            FPS = 1000.0/double(nbFrames);
            nbFrames = 0;
            lastTime += 1.0;
        }
        app.render(window, FPS);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            app.closeGame();
        }

    }

    glfwTerminate();
    app.~App();
    return 0;
}