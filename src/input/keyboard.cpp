#include "internal/eventpump.h"
#include "input.h"
#include <string.h>
#include <climits>

#define INPUT_SCANCODES GLFW_KEY_LAST + GLFW_MOUSE_BUTTON_LAST + 2

static bool keys[INPUT_SCANCODES];
static bool keys0[INPUT_SCANCODES];
static int map[INPUT_SCANCODES];

int mouseCode(int code) {
    return GLFW_KEY_LAST + 1 + code;
}

void key::update() {
    for (int i = 0; i < INPUT_SCANCODES; i++)
        keys0[i] = keys[i];
}

void key::init() {
    for (int i = 0; i < INPUT_SCANCODES; i++) 
        map[i] = i;
}

void mouse::keyevent(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        keys[map[mouseCode(button)]] = 1;
    else if (action == GLFW_RELEASE)
        keys[map[mouseCode(button)]] = 0;
}

bool mouse::down(int code) {
    return keys[mouseCode(code)];
}

bool mouse::press(int code) {
    return !keys0[mouseCode(code)] && keys[mouseCode(code)];
}

bool mouse::release(int code) {
    return keys0[mouseCode(code)] && !keys[mouseCode(code)];
}

void key::keyevent(GLFWwindow* window, int key, int scancode, int action, int mod) {
    if (action == GLFW_PRESS)
        keys[map[scancode]] = 1;
    else if (action == GLFW_RELEASE)
        keys[map[scancode]] = 0;
}

bool key::down(int code) {
    return keys[code];
}

bool key::press(int code) {
    return !keys0[code] && keys[code];
}

bool key::release(int code) {
    return keys0[code] && !keys[code];
}

void key::remap(int phys, int vir) {
    if (phys <= GLFW_MOUSE_BUTTON_LAST)
        phys = mouseCode(phys);
    if (vir <= GLFW_MOUSE_BUTTON_LAST)
        vir = mouseCode(vir);
    map[phys] = vir;
}