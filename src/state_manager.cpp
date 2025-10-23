#include "state_manager.h"

std::unique_ptr<State> StateManager::state = nullptr;

State* StateManager::getState()
{
    return state.get();
}

StateManager::~StateManager()
{
    if(state)
        state.reset();
}