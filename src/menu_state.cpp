#include "menu_state.h"
#include "states.h"
#include "state_manager.h"

int MenuState::selectedOption = 0;

void MenuState::initSpecific()
{
    curs_set(0);
    noecho();

    const int cursorLen = 3;
    int widestOptionLen = utf8Length(*std::max_element(menuOptions.begin(), menuOptions.end(), [this](const std::string& s1, const std::string& s2)
    {
        return s1.length() < s2.length();
    }));
    menuSelectWinWidth = widestOptionLen + cursorLen + fromBorderOffset * 2;

    int menuSelectWindowPosX = mainWindowPosX + (mainWinWidth - menuSelectWinWidth) / 2;
    int menuSelectWindowPosY = mainWindowPosY + 12; /*offset 12 lines*/


    if(menuSelectWindow)
        delwin(menuSelectWindow);
    menuSelectWindow = newwin(menuSelectWinHeight, menuSelectWinWidth, menuSelectWindowPosY, menuSelectWindowPosX);

    wborder(menuSelectWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    keypad(mainWindow, TRUE);
    nodelay(mainWindow, TRUE);
}

void MenuState::handleInput()
{
    int c = wgetch(mainWindow);
    wborder(menuSelectWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

    switch(c)
    {
        case 'w':
        case KEY_UP:
            if(selectedOption == 0)
                selectedOption = menuOptions.size() - 1;
            else
                --selectedOption;
            wclear(menuSelectWindow);
            break;
        case 's':
        case KEY_DOWN:
            if(selectedOption == menuOptions.size() - 1)
                selectedOption = 0;
            else
                ++selectedOption;
            wclear(menuSelectWindow);
            break;
        case KEY_EXIT_M:
            *is_running = false;
            break;
        case ERR:
            return;
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
            StateManager::newState<KanjiTestState>(is_running);
            break;
        case 1:
            StateManager::newState<VocabulatyTestState>(is_running);
            break;
        case 2:
            StateManager::newState<InspectorState>(is_running);
            break;
        case 3:
            StateManager::newState<ManagerState>(is_running);
            break;
        case 4: //Exit option index
            *is_running = false;
            break;
        }

        enter=false;
    }
}

void MenuState::drawSpecific()
{
    wbkgd(menuSelectWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::SECONDARY_WIN_BACKGROUND)) | ' ');

    const int optionTextPosX = 5;
    for(int i = 0; i < menuOptions.size(); i++)
    {
        if(i == selectedOption)
        {
            wattron(menuSelectWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::CURSOR)));
            /*2, 3 are arrow (=>) chars x positions*/
            mvwaddch(menuSelectWindow, i + 1, 2, '=');
            mvwaddch(menuSelectWindow, i + 1, 3, '>');
            wattroff(menuSelectWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::CURSOR)));
            mvwaddstr(menuSelectWindow, i + 1, optionTextPosX, menuOptions.at(i).c_str());
        }
        else
        {
            mvwaddstr(menuSelectWindow, i + 1, optionTextPosX, menuOptions.at(i).c_str());
        }
    }    

    const int titleWidth = 28;
    int titlePosX = (mainWinWidth - titleWidth) / 2;

    wattron(mainWindow, A_BOLD);
    mvwaddstr(mainWindow, 1 + fromBorderOffset, titlePosX, "  ____ _                _ _ ");
    mvwaddstr(mainWindow, 2 + fromBorderOffset, titlePosX, " / ___| | ____ _ _ __  (_|_)");
    mvwaddstr(mainWindow, 3 + fromBorderOffset, titlePosX, "| |   | |/ / _` | '_ \\ | | |");
    mvwaddstr(mainWindow, 4 + fromBorderOffset, titlePosX, "| |___|   < (_| | | | || | |");
    mvwaddstr(mainWindow, 5 + fromBorderOffset, titlePosX, " \\____|_|\\_\\__,_|_| |_|/ |_|");
    mvwaddstr(mainWindow, 6 + fromBorderOffset, titlePosX, "                    |__/    ");
    wattroff(mainWindow, A_BOLD);
    mvwaddstr(mainWindow, mainWinHeight - fromBorderOffset, fromBorderOffset, version.c_str());
    mvwaddstr(mainWindow, mainWinHeight - fromBorderOffset, mainWinWidth - fromBorderOffset - author.length(), author.c_str());

    wrefresh(menuSelectWindow);
}

MenuState::~MenuState()
{
    delwin(menuSelectWindow);
    curs_set(1);
}