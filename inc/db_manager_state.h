#pragma once

#include "state.h"
#include <map>
#include <string>
#include "input_field.h"

class ManagerState : public State
{
public:
    ManagerState(bool* runningFlag) : State(runningFlag) {}
    ~ManagerState();
    ManagerState(const ManagerState&) = delete;
    ManagerState(ManagerState&&) = delete;
    ManagerState& operator=(const ManagerState&) = delete;
    ManagerState& operator=(ManagerState&&) = delete;

    void initSpecific() override;
    void handleInput() override;
    void process() override;
    void drawSpecific() override;

private:
    WINDOW* bottomBarWindow = nullptr;
    int bottomBarWindowPosX = 0;
    int bottomBarWindowPosY = 0;
    int bottomBarWinWidth = mainWinWidth - 2;
    int bottomBarWinHeight = 7;

    std::map<std::string, InputField> bottomBarInputFields;
    std::map<std::string, InputField>::iterator selectedInputField;
};
