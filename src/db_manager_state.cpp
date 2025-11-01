#include <regex>
#include <iterator>
#include "db_manager_state.h"
#include "state_manager.h"

static std::regex inputRegex{"[a-z]"};

void ManagerState::initSpecific()
{
    curs_set(0);
    noecho();
    nodelay(mainWindow, TRUE);
    keypad(mainWindow, TRUE);

    bottomBarWindowPosX = mainWindowPosX + 1;
    bottomBarWindowPosY = mainWindowPosY + mainWinHeight - bottomBarWinHeight - 1;

    if(bottomBarWindow)
        delwin(bottomBarWindow);
    bottomBarWindow = newwin(bottomBarWinHeight, bottomBarWinWidth, bottomBarWindowPosY, bottomBarWindowPosX);

    wborder(bottomBarWindow, ' ', ' ', ACS_HLINE, ' ', ' ', ' ', ' ', ' ');

    bottomBarInputFields.emplace(std::string{"kanji"}, InputField("Кандзи:", 1, 0));
    bottomBarInputFields.emplace(std::string{"translation"}, InputField("Перевод:", 1, 15));
    bottomBarInputFields.emplace(std::string{"on"}, InputField("Онъёми:", 3, 1));
    bottomBarInputFields.emplace(std::string{"kun"}, InputField("Кунъёми:", 5, 0));
    bottomBarInputFields.begin()->second.setSelected(true);
    selectedInputField = bottomBarInputFields.begin();
}

void ManagerState::handleInput()
{
    int c = wgetch(mainWindow);

    switch (c)
    {
        case KEY_EXIT_M:
            StateManager::newState<MenuState>(is_running);
            break;
        case KEY_BTAB:
            for(auto itr = bottomBarInputFields.begin(); itr != bottomBarInputFields.end(); ++itr)
            {
                if(itr->second.getSelected() && (std::next(itr) != bottomBarInputFields.end()))
                {
                    itr->second.setSelected(false);
                    std::next(itr)->second.setSelected(true);
                    selectedInputField = std::next(itr);
                    break;
                }
                else if(itr->second.getSelected() && (std::next(itr) == bottomBarInputFields.end()))
                {
                    itr->second.setSelected(false);
                    bottomBarInputFields.begin()->second.setSelected(true);
                    selectedInputField = bottomBarInputFields.begin();
                    break;
                }
            }
            break;
        case KEY_TAB_M:
            for(auto itr = bottomBarInputFields.begin(); itr != bottomBarInputFields.end(); ++itr)
            {
                if(itr->second.getSelected() && (itr != bottomBarInputFields.begin()))
                {
                    itr->second.setSelected(false);
                    std::prev(itr)->second.setSelected(true);
                    selectedInputField = std::prev(itr);
                    break;
                }
                else if(itr->second.getSelected() && (itr == bottomBarInputFields.begin()))
                {
                    bottomBarInputFields.begin()->second.setSelected(false);
                    std::prev(bottomBarInputFields.end())->second.setSelected(true);
                    selectedInputField = std::prev(bottomBarInputFields.end());
                    break;
                }
            }
            break;
        case KEY_BACKSPACE:
            selectedInputField->second.popBackInputText();
        break;
        case ERR:
            break;
        default:
            if(c >= 'a' && c <= 'z')
            {
                selectedInputField->second.setInputText(selectedInputField->second.getInputText() + static_cast<char>(c));
            }
            break;
    }
}

void ManagerState::process()
{

}

void ManagerState::drawSpecific()
{
    wbkgd(bottomBarWindow, COLOR_PAIR(static_cast<short>(COLOR_PAIR::MAIN_WIN_BACKGROUND)) | ' ');

    mvwprintw(bottomBarWindow, 0, 3, " Добавление нового кандзи ");

    for(auto& itr : bottomBarInputFields)
    {
        itr.second.print(bottomBarWindow);
    }

    mvwhline(bottomBarWindow,  4, 9, ACS_HLINE, 8);

    mvwprintw(mainWindow, 0, 2, "Редактор базы данных");
    wrefresh(bottomBarWindow);
}

ManagerState::~ManagerState()
{
    delwin(bottomBarWindow);
    curs_set(1);
}