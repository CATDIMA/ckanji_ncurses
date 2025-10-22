#include <iostream>
#include <ncurses.h>
#include <memory>
#include <errno.h>
#include <signal.h>
#include "states.h"

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
    signal(SIGWINCH, resizeHandler);

    bool isRunning = true;
    std::unique_ptr<State> state;
    state = std::make_unique<MenuState>(&isRunning);

    initscr();
    checkTermSize();

    if(!has_colors())
    {
        endwin();
        std::cout << "Error: your terminal doesn't support colors! Aborting...\n";
        exit(ENOTTY);
    }

    state->init();

    while(isRunning)
    {
        if(resized)
        {   
            endwin();
            initscr();
            checkTermSize();
            refresh();
            clear();
            state->init();
            resized = false;
        }
        state->handleInput();
        state->process();
        state->draw();
    }

    endwin();
    return 0;
}