#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "log.h"
#include "engine.h"
#include "internal/eventpump.h"

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 675;
float GAMESCALE_X = 1, GAMESCALE_Y = 1, TEXTSCALE_X = 1, TEXTSCALE_Y = 1;
int GAME_WIDTH = 1200 / GAMESCALE_X;
int GAME_HEIGHT = 675 / GAMESCALE_Y;
static float localGScale = 1, localTScale = 1;

static GLFWwindow* window = NULL;

static void updateScale() {
    GAMESCALE_X = localGScale * SCREEN_WIDTH / 1200.0;
    GAMESCALE_Y = localGScale * SCREEN_HEIGHT / 675.0;

    TEXTSCALE_X = localTScale * SCREEN_WIDTH / 1200.0;
    TEXTSCALE_Y = localTScale * SCREEN_HEIGHT / 675.0;

    GAME_WIDTH = SCREEN_WIDTH / GAMESCALE_X;
    GAME_HEIGHT = SCREEN_HEIGHT / GAMESCALE_Y;
}

static void linkInputCallbacks() {
    glfwSetKeyCallback(window, key::keyevent);
    glfwSetCursorPosCallback(window, mouse::moveevent);
    glfwSetMouseButtonCallback(window, mouse::keyevent);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    updateScale();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool initWindow(int w, int h, const char* name) {

    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;
    updateScale();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(w, h, name, NULL, NULL);
    if (window == NULL)
    {
        flog::out << flog::err << "failed to create GLFW window" << flog::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        flog::out << flog::err << "Failed to initialize GLAD" << flog::endl;
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    linkInputCallbacks();

    return true;
}

void closeWindow() {
	glfwDestroyWindow(window);
	window = NULL;

	glfwTerminate();
}

void engine::setGameScale(float gamescale) {
    localGScale = gamescale;
    updateScale();
}

void engine::setTextScale(float textscale) {
    localTScale = textscale;
    updateScale();
}

