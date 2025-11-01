#include "vocabulaty_test_state.h"
#include "state_manager.h"

void VocabulatyTestState::initSpecific()
{
    curs_set(0);
    keypad(mainWindow, TRUE);
}

void VocabulatyTestState::handleInput()
{
    int c = wgetch(mainWindow);

    switch (c)
    {
        case KEY_EXIT_M:
            StateManager::newState<MenuState>(is_running);
            break;
    }
}

void VocabulatyTestState::process()
{

}

void VocabulatyTestState::drawSpecific()
{
    mvwprintw(mainWindow, 0, 2, "Словарный тест");
}

VocabulatyTestState::~VocabulatyTestState()
{
    curs_set(1);
}