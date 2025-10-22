#include "menu_state.h"
#include <thread>
#include <chrono>

void MenuState::init()
{
    curs_set(0);
    noecho();
    int menuMainWindowPosX = (COLS - menuMainWinWidth) / 2;
    int menuMainWindowPosY = (LINES - menuMainWinHeight) / 2;
    int menuSelectWindowPosX = menuMainWindowPosX + (menuMainWinWidth - menuSelectWinWidth) / 2;
    int menuSelectWindowPosY = menuMainWindowPosY + 12;

    if(menuMainWindow)
        delwin(menuMainWindow);
    menuMainWindow = newwin(menuMainWinHeight, menuMainWinWidth, menuMainWindowPosY, menuMainWindowPosX);

    if(menuSelectWindow)
        delwin(menuSelectWindow);
    menuSelectWindow = newwin(menuSelectWinHeight, menuSelectWinWidth, menuSelectWindowPosY, menuSelectWindowPosX);
    
    start_color();
    init_pair(1, 249, 17);
    init_pair(2, 249, 234);
    init_pair(3, COLOR_RED,   196);
    init_pair(4, 249, 25);
    init_pair(5, 249, COLOR_RED);

    wborder(menuMainWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    wborder(menuSelectWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    keypad(menuSelectWindow, TRUE);
    nodelay(menuSelectWindow, TRUE);
}

void MenuState::handleInput()
{
    int c = wgetch(menuSelectWindow);
    wborder(menuSelectWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    switch(c)
    {
        case KEY_UP:
            if(selectedOption > 0)
            {
                --selectedOption;
                wclear(menuSelectWindow);
            }
            break;
        case KEY_DOWN:
            if(selectedOption < 3)
            {
                ++selectedOption;
                wclear(menuSelectWindow);
            }
            break;
        case '\n':
        case '\r':
        case KEY_ENTER:
            enter = true;
            break;
    }
}

void MenuState::process()
{   
    if(enter)
    {
        switch (selectedOption)
        {
        case 0:
            /* code */
            break;
        case 3:
            *is_running = false;
            break;
        }

        enter=false;
    }
}

void MenuState::draw()
{
    bkgd(COLOR_PAIR(1) | ' ');
    wbkgd(menuMainWindow, COLOR_PAIR(2) | ' ');
    wbkgd(menuSelectWindow, COLOR_PAIR(4) | ' ');

    for(int i = 0; i < menuOptions.size(); i++)
    {
        if(i == selectedOption)
        {
            wattron(menuSelectWindow, COLOR_PAIR(5));
            mvwaddch(menuSelectWindow, i + 1, 2, '=');
            mvwaddch(menuSelectWindow, i + 1, 3, '>');
            wattroff(menuSelectWindow, COLOR_PAIR(5));
            mvwaddstr(menuSelectWindow, i + 1, 5, menuOptions.at(i).c_str());
        }
        else
        {
            mvwaddstr(menuSelectWindow, i + 1, 5, menuOptions.at(i).c_str());
        }
    }    

    int xpos = (menuMainWinWidth - 28) / 2;
    int yoffset = 2;

    wattron(menuMainWindow, A_BOLD);
    mvwaddstr(menuMainWindow, 1 + yoffset, xpos, "  ____ _                _ _ ");
    mvwaddstr(menuMainWindow, 2 + yoffset, xpos, " / ___| | ____ _ _ __  (_|_)");
    mvwaddstr(menuMainWindow, 3 + yoffset, xpos, "| |   | |/ / _` | '_ \\ | | |");
    mvwaddstr(menuMainWindow, 4 + yoffset, xpos, "| |___|   < (_| | | | || | |");
    mvwaddstr(menuMainWindow, 5 + yoffset, xpos, " \\____|_|\\_\\__,_|_| |_|/ |_|");
    mvwaddstr(menuMainWindow, 6 + yoffset, xpos, "                    |__/    ");
    wattroff(menuMainWindow, A_BOLD);
    mvwaddstr(menuMainWindow, menuMainWinHeight - 2, 2, version.c_str());
    mvwaddstr(menuMainWindow, menuMainWinHeight - 2, menuMainWinWidth - 1 - author.length(), author.c_str());

    refresh();
    wrefresh(menuMainWindow);
    wrefresh(menuSelectWindow);
}

MenuState::~MenuState()
{
    delwin(menuSelectWindow);
    delwin(menuMainWindow);
    curs_set(1);
}