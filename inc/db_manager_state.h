#pragma once

#include "state.h"

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
};