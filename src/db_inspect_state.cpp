#include "db_inspect_state.h"
#include "state_manager.h"

void InspectorState::initSpecific()
{
    curs_set(0);
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

void InspectorState::drawSpecific()
{
    mvwprintw(mainWindow, 0, 2, "Просмотр базы данных");
}

InspectorState::~InspectorState()
{
    curs_set(1);
}