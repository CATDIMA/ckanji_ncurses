#include "menu_state.h"

void MenuState::init()
{
    curs_set(0);
    noecho();

    const int cursorLen = 3;
    int widestOptionLen = std::max_element(menuOptions.begin(), menuOptions.end(), [](const std::string& s1, const std::string& s2)
    {
        return s1.length() < s2.length();
    })->length();
    menuSelectWinWidth = widestOptionLen + cursorLen + fromBorderOffset * 2;

    int menuMainWindowPosX = (COLS - menuMainWinWidth) / 2;
    int menuMainWindowPosY = (LINES - menuMainWinHeight) / 2;
    int menuSelectWindowPosX = menuMainWindowPosX + (menuMainWinWidth - menuSelectWinWidth) / 2;
    int menuSelectWindowPosY = menuMainWindowPosY + 12; /*offset 12 lines*/

    if(menuMainWindow)
        delwin(menuMainWindow);
    menuMainWindow = newwin(menuMainWinHeight, menuMainWinWidth, menuMainWindowPosY, menuMainWindowPosX);

    if(menuSelectWindow)
        delwin(menuSelectWindow);
    menuSelectWindow = newwin(menuSelectWinHeight, menuSelectWinWidth, menuSelectWindowPosY, menuSelectWindowPosX);
    
    start_color();

    init_pair(static_cast<short>(COLOR_PAIR::STD_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DEEP_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DARK_GRAY);
    init_pair(static_cast<short>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_LIGHT_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::CURSOR), COLOR_LIGHT_GRAY, COLOR_RED);

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
            if(selectedOption < menuOptions.size() - 1)
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
        case 4: //Exit option index
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
    wbkgd(menuSelectWindow, COLOR_PAIR(3) | ' ');

    const int optionTextPosX = 5;
    for(int i = 0; i < menuOptions.size(); i++)
    {
        if(i == selectedOption)
        {
            wattron(menuSelectWindow, COLOR_PAIR(4));
            /*2, 3 are arrow (=>) chars x positions*/
            mvwaddch(menuSelectWindow, i + 1, 2, '=');
            mvwaddch(menuSelectWindow, i + 1, 3, '>');
            wattroff(menuSelectWindow, COLOR_PAIR(4));
            mvwaddstr(menuSelectWindow, i + 1, optionTextPosX, menuOptions.at(i).c_str());
        }
        else
        {
            mvwaddstr(menuSelectWindow, i + 1, optionTextPosX, menuOptions.at(i).c_str());
        }
    }    

    const int titleWidth = 28;
    int titlePosX = (menuMainWinWidth - titleWidth) / 2;

    wattron(menuMainWindow, A_BOLD);
    mvwaddstr(menuMainWindow, 1 + fromBorderOffset, titlePosX, "  ____ _                _ _ ");
    mvwaddstr(menuMainWindow, 2 + fromBorderOffset, titlePosX, " / ___| | ____ _ _ __  (_|_)");
    mvwaddstr(menuMainWindow, 3 + fromBorderOffset, titlePosX, "| |   | |/ / _` | '_ \\ | | |");
    mvwaddstr(menuMainWindow, 4 + fromBorderOffset, titlePosX, "| |___|   < (_| | | | || | |");
    mvwaddstr(menuMainWindow, 5 + fromBorderOffset, titlePosX, " \\____|_|\\_\\__,_|_| |_|/ |_|");
    mvwaddstr(menuMainWindow, 6 + fromBorderOffset, titlePosX, "                    |__/    ");
    wattroff(menuMainWindow, A_BOLD);
    mvwaddstr(menuMainWindow, menuMainWinHeight - fromBorderOffset, fromBorderOffset, version.c_str());
    mvwaddstr(menuMainWindow, menuMainWinHeight - fromBorderOffset, menuMainWinWidth - fromBorderOffset - author.length(), author.c_str());

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