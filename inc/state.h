#pragma once

#include <ncurses.h>

class State
{
public:
    State(bool* runningFlag) : is_running{runningFlag} {}
    virtual ~State() = default;
    State(const State&) = default;
    State& operator=(const State&) = default;
    State(State&&) = default;
    State& operator=(State&&) = default;

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void process() = 0;
    virtual void draw() = 0;

protected:
    bool* is_running = nullptr;
    const int fromBorderOffset = 2; //to print text next to the window borders
};