#pragma once

#include "state.h"
#include <array>
#include <string>

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
    const std::array<std::string, 4> menuOptions =
    {
        "Start test",
        "View databse",
        "Edit database",
        "Exit"
    };

    WINDOW* menuMainWindow = nullptr;
    const int menuMainWinWidth = 80;
    const int menuMainWinHeight = 25;

    WINDOW* menuSelectWindow = nullptr;
    const int menuSelectWinWidth = 22;
    const int menuSelectWinHeight = 6;

    const std::string author{"CATDIMA, 2025"};
    const std::string version{"ver 0.0.1, " + std::string{curses_version()}};
};