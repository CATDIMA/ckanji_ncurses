#include "kanji_test_state.h"
#include "state_manager.h"

void KanjiTestState::initSpecific()
{
    curs_set(0);
    keypad(mainWindow, TRUE);
}

void KanjiTestState::handleInput()
{
    int c = wgetch(mainWindow);

    switch (c)
    {
        case KEY_EXIT_M:
            StateManager::newState<MenuState>(is_running);
            break;
    }
}

void KanjiTestState::process()
{

}

void KanjiTestState::drawSpecific()
{
    mvwprintw(mainWindow, 0, 2, "Кандзи тест");
}

KanjiTestState::~KanjiTestState()
{
    curs_set(1);
}