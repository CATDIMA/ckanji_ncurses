#include "db_inspect_state.h"
#include "state_manager.h"

void InspectorState::init()
{
    curs_set(0);
    
    int testMainWindowPosX = (COLS - mainWinWidth) / 2;
    int testMainWindowPosY = (LINES - mainWinHeight) / 2;

    if(mainWindow)
        delwin(mainWindow);
    mainWindow = newwin(mainWinHeight, mainWinWidth, testMainWindowPosY, testMainWindowPosX);

    start_color();
    init_pair(static_cast<short>(COLOR_PAIR::STD_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DEEP_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_DARK_GRAY);
    init_pair(static_cast<short>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND), COLOR_LIGHT_GRAY, COLOR_LIGHT_BLUE);
    init_pair(static_cast<short>(COLOR_PAIR::CURSOR), COLOR_LIGHT_GRAY, COLOR_RED);

    wborder(mainWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    set_escdelay(0);
    keypad(mainWindow, TRUE);
    nodelay(mainWindow, TRUE);
}

void InspectorState::handleInput()
{
    int c = wgetch(mainWindow);

    switch (c)
    {
        case KEY_EXIT_M:
            StateManager::newState<MenuState>(is_running);
            break;
    }
}

void InspectorState::process()
{

}

void InspectorState::draw()
{
    bkgd(COLOR_PAIR(static_cast<short>(COLOR_PAIR::STD_BACKGROUND)) | ' ');
    wbkgd(mainWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND)) | ' ');

    mvwprintw(mainWindow, 0, 2, "Просмотр базы данных");

    refresh();
    wrefresh(mainWindow);
}

InspectorState::~InspectorState()
{
    curs_set(1);
    delwin(mainWindow);
}