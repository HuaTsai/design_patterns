#include <core/waterball_community.hpp>
#include <plugins/states/waiting_state.hpp>

void WaitingState::OnEnter() { /* nop */ }

Event WaitingState::OnDo(Event event) { return event; }

void WaitingState::OnExit() { /* nop */ }