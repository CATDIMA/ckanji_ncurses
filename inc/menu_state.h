#pragma once

#include "state.h"
#include <vector>
#include <string>
#include <algorithm>

class MenuState : public State
{
public:
    MenuState(bool* runningFlag) : State(runningFlag) {}
    ~MenuState() override;
    MenuState(const MenuState&) = default;
    MenuState& operator=(const MenuState&) = default;
    MenuState(MenuState&&) = default;
    MenuState& operator=(MenuState&&) = default;

    void init() override;
    void handleInput() override;
    void process() override;
    void draw() override;

private:
    bool enter = false;
    static int selectedOption;
    const std::vector<std::string> menuOptions =
    {
        "Начать кандзи тест",
        "Начать словарный тест",
        "Просмотреть базу данных",
        "Редактировать базу данных",
        "Выход"
    };

    WINDOW* menuSelectWindow = nullptr;
    int menuSelectWinWidth = 22;
    const int menuSelectWinHeight = 7;

    const std::string author{"CATDIMA, 2025"};
    const std::string version{"Ckanji: 0.0.5, " + std::string{curses_version()}};
};