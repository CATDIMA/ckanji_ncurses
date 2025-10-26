#include "db_manager_state.h"
#include "state_manager.h"

void ManagerState::initSpecific()
{
    curs_set(0);
    keypad(mainWindow, TRUE);
    nodelay(mainWindow, TRUE);
}

void ManagerState::handleInput()
{
    int c = wgetch(mainWindow);

    switch (c)
    {
        case KEY_EXIT_M:
            StateManager::newState<MenuState>(is_running);
            break;
    }
}

void ManagerState::process()
{

}

void ManagerState::drawSpecific()
{
    mvwprintw(mainWindow, 0, 2, "Редактор базы данных");
}

ManagerState::~ManagerState()
{
    curs_set(1);
}