#pragma once

#include <ncursesw/ncurses.h>
#include <string>
#include <memory>
#include "colors.h"

const int KEY_EXIT_M = 27;

class State
{
public:
    State(bool* runningFlag) : is_running{runningFlag} {}

    virtual ~State()
    {
        if(mainWindow)
            delwin(mainWindow);
    }
    State(const State&) = default;
    State& operator=(const State&) = default;
    State(State&&) = default;
    State& operator=(State&&) = default;

    virtual void init() final
    {
        mainWindowPosX = (COLS - mainWinWidth) / 2;
        mainWindowPosY = (LINES - mainWinHeight) / 2;
    
        if(mainWindow)
            delwin(mainWindow);
        mainWindow = newwin(mainWinHeight, mainWinWidth, mainWindowPosY, mainWindowPosX);
    
        wborder(mainWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

        initSpecific();
    }
    virtual void handleInput() = 0;
    virtual void process() = 0;
    virtual void draw() final
    {
        bkgd(COLOR_PAIR(static_cast<short>(COLOR_PAIR::STD_BACKGROUND)) | ' ');
        wbkgd(mainWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND)) | ' ');

        drawSpecific();

        refresh();
        wrefresh(mainWindow);
    }

protected:
    virtual void initSpecific() = 0;
    virtual void drawSpecific() = 0;
    
    bool* is_running = nullptr;
    const int fromBorderOffset = 2; //to print text next to the window borders

    WINDOW* mainWindow = nullptr;
    const int mainWinWidth = 80;
    const int mainWinHeight = 25;
    int mainWindowPosX = 0;
    int mainWindowPosY = 0;

    size_t utf8Length(const std::string& str) 
    {
        size_t len = 0;
        
        for (char c : str)
        {
            if ((c & 0xC0) != 0x80)
                len++;
        }
        
        return len;
    }
};