#pragma once

#include <memory>
#include <type_traits>
#include "states.h"

class StateManager
{
public:
    StateManager() = default;
    ~StateManager();
    StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;
    StateManager(StateManager&&) = delete;
    StateManager& operator=(StateManager&&) = delete;

    static State* getState();

    template<typename T>
    static void newState(bool* runningFlag)
    {
        static_assert(std::is_base_of<State, T>::value, "StateManager::newState: T must be derived from State");

        if(state)
        {
            state.reset();
        }

        state = std::make_unique<T>(runningFlag);
        state->init();
    }

private:
    static std::unique_ptr<State> state;
};