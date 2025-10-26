#pragma once

#include "state.h"

class VocabulatyTestState : public State
{
public:
    VocabulatyTestState(bool* runningFlag) : State(runningFlag) {}
    ~VocabulatyTestState();
    VocabulatyTestState(const VocabulatyTestState&) = delete;
    VocabulatyTestState(VocabulatyTestState&&) = delete;
    VocabulatyTestState& operator=(const VocabulatyTestState&) = delete;
    VocabulatyTestState& operator=(VocabulatyTestState&&) = delete;

    void initSpecific() override;
    void handleInput() override;
    void process() override;
    void drawSpecific() override;

private:
};