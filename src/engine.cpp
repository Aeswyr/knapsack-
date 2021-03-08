#include "knapsack/engine.h"

#include <climits>

#include <boost/thread.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include <ft2build.h>
#include FT_FREETYPE_H

#include <knapsack/internal/screen.h>
#include <knapsack/internal/resource.h>
#include <knapsack/internal/handler.h>
#include <knapsack/internal/eventpump.h>

#include <knapsack/log.h>

int ENGINE_Z = INT_MAX;
unsigned long long ENGINE_TICK = 0;
bool ENGINE_DEV_MODE = false;
unsigned int ENGINE_UPS = 0, ENGINE_FPS = 0, ENGINE_MS = 0;

static FT_Library  library;

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
    out::log << out::alert << "Starting game" << out::endl;

    double startu = 0;
    double pdel = 0;

    double delta = 1.0 / 60;
    double deltap = 1;

    fps = 0;
    ups = 0;
    avgu = 0;

    while (running)
    {
        if ((glfwGetTime() - lastu) > delta) {
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
                out::log << pdel * 1.000 << "s since last update" << "\n\tFPS: " << ENGINE_FPS
                 << "\n\tUPS: " << ENGINE_UPS << "\n\tAvg utime: " << ENGINE_MS << "ms" << out::endl;

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
        out::log << out::err << "Window initialization failed" << out::endl;
        return;
    }

    FT_Error error = FT_Init_FreeType( &library );
    if ( error )
    {
        out::log << out::err << "Freetype initialization failed" << out::endl;
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
    out::log << out::alert << "Closing game" << out::endl;
    running = false;
    int threadReturn;
    eThread->join();
    res::close();
    closeWindow();
}



