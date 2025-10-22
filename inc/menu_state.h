#pragma once

#include "colors.h"
#include "state.h"
#include <vector>
#include <string>
#include <algorithm>

class MenuState : public State
{
public:
    MenuState(bool* runningFlag) : State(runningFlag) {}
    ~MenuState() override;
    MenuState(const MenuState&) = delete;
    MenuState& operator=(const MenuState&) = delete;
    MenuState(MenuState&&) = delete;
    MenuState& operator=(MenuState&&) = delete;

    void init() override;
    void handleInput() override;
    void process() override;
    void draw() override;

private:
    bool enter = false;
    int selectedOption = 0;
    const std::vector<std::string> menuOptions =
    {
        "Start kanji test",
        "Start vocabulary test",
        "View databse",
        "Edit database",
        "Exit"
    };

    WINDOW* menuMainWindow = nullptr;
    const int menuMainWinWidth = 80;
    const int menuMainWinHeight = 25;

    WINDOW* menuSelectWindow = nullptr;
    int menuSelectWinWidth = 22;
    const int menuSelectWinHeight = 7;

    const std::string author{"CATDIMA, 2025"};
    const std::string version{"ver 0.0.2, " + std::string{curses_version()}};
};