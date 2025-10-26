#include <iostream>
#include <memory>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include "colors.h"
#include "states.h"
#include "state_manager.h"

static volatile sig_atomic_t resized = false;

static void resizeHandler(int a)
{
    resized = true;
}

static void checkTermSize()
{
    if(COLS < 80 || LINES < 25)
    {
        endwin();
        std::cout << "Error: your terminal is too small! Aborting...\n";
        std::cout << "Terminal should be at least 80x25 chars in size\n";
        exit(ENOTTY);
    }
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");

    signal(SIGWINCH, resizeHandler);

    initscr();
    set_escdelay(0);
    checkTermSize();

    if(!has_colors())
    {
        endwin();
        std::cout << "Error: your terminal doesn't support colors! Aborting...\n";
        exit(ENOTTY);
    }

    start_color();
    init_pair(static_cast<short>(COLOR_PAIR::STD_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DEEP_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DARK_GRAY);
    init_pair(static_cast<short>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_LIGHT_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::CURSOR), COLOR_LIGHT_GRAY, COLOR_RED);

    bool isRunning = true;
    StateManager::newState<MenuState>(&isRunning);

    while(isRunning)
    {
        if(resized)
        {   
            endwin();
            initscr();
            checkTermSize();
            refresh();
            clear();
            StateManager::getState()->init();
            resized = false;
        }
        StateManager::getState()->handleInput();
        StateManager::getState()->process();
        StateManager::getState()->draw();
    }

    endwin();
    return 0;
}