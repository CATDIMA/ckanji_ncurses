#pragma once

#include "state.h"

class KanjiTestState : public State
{
public:
    KanjiTestState(bool* runningFlag) : State(runningFlag) {}
    ~KanjiTestState() override;
    KanjiTestState(const KanjiTestState&) = delete;
    KanjiTestState& operator=(const KanjiTestState&) = delete;
    KanjiTestState(KanjiTestState&&) = delete;
    KanjiTestState& operator=(KanjiTestState&&) = delete;

    void init() override;
    void handleInput() override;
    void process() override;
    void draw() override;

private:
    
};