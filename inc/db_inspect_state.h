#pragma once

#include "state.h"

class InspectorState : public State
{
public:
    InspectorState(bool* runningFlag) : State(runningFlag) {}
    ~InspectorState();
    InspectorState(const InspectorState&) = delete;
    InspectorState(InspectorState&&) = delete;
    InspectorState& operator=(const InspectorState&) = delete;
    InspectorState& operator=(InspectorState&&) = delete;

    void init() override;
    void handleInput() override;
    void process() override;
    void draw() override;

private:
};