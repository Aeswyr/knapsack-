#include "internal/screen.h"
#include <boost/thread.hpp>
#include "log.h"
#include "engine.h"
#include <GLFW/glfw3.h>
#include "internal/resource.h"
#include "internal/handler.h"
#include "internal/eventpump.h"
#include <climits>


int ENGINE_Z = INT_MAX;
unsigned long long ENGINE_TICK = 0;
bool ENGINE_DEV_MODE = false;
unsigned int ENGINE_UPS = 0, ENGINE_FPS = 0, ENGINE_MS = 0;

static bool running = false;
static unsigned int fps, ups;
static double avgu;
static boost::thread* eThread;

static void checkEvents() {
    glfwPollEvents();
}

void tick() {
    hnd::update();
    spr::update();
}

bool flag_reswait = true;

int update() {
    while(flag_reswait);

    double lastu = glfwGetTime();
    double lastp = glfwGetTime();
    flog::out << flog::alert << "Starting game" << flog::endl;

    double startu = 0;
    double pdel = 0;

    double delta = 1 / 60;
    double deltap = 1;

    fps = 0;
    ups = 0;
    avgu = 0;

    while (running)
    {
        if ((glfwGetTime() - lastu) >= delta) {
            ups++;
            startu = glfwGetTime();
            tick();
            ENGINE_TICK++;
            avgu += glfwGetTime() - startu;

            if ((pdel = glfwGetTime() - lastp) >= deltap) {
                sfx::clean();
                ENGINE_FPS = (int)(fps * deltap / pdel);
                ENGINE_UPS = (int)(ups * deltap / pdel);
                ENGINE_MS = (avgu * 1000.000 / ups);
                flog::out << pdel * 1.000 << "s since last update" << "\n\tFPS: " << ENGINE_FPS
                 << "\n\tUPS: " << ENGINE_UPS << "\n\tAvg utime: " << ENGINE_MS << "ms" << flog::endl;

                ups = 0;
                fps = 0;
                avgu = 0;
                lastp = glfwGetTime();
            }
            lastu = glfwGetTime();
        }
    }
    return 0;
}

void render() {
        hnd::render();
        spr::push();

        spr::flush();
		fps++;
}

int run() {
    double curr;
    double last = glfwGetTime();
    double delta = 1;
	while (running && !glfwWindowShouldClose(getWindow())) {
        curr = glfwGetTime();
        checkEvents();
        render();
        if (curr - last >= delta) {
            last = glfwGetTime();
            spr::clean();
        }
	}
    return 0;
}

void engine::start(int w, int h, const char* name, void (*initfunc)()) {
    if (!initWindow(w, h, name)) {
        flog::out << flog::err << "Window initialization failed" << flog::endl;
        return;
    }
    //gamepad::locateControllers();
    key::init();
    running = true;
    eThread = new boost::thread(update);
    res::init();
    initfunc();
    flag_reswait = false;
    run();
}

void engine::stop() {
    flog::out << flog::alert << "Closing game" << flog::endl;
    running = false;
    int threadReturn;
    eThread->join();
    res::close();
    closeWindow();
}



