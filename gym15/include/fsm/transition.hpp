#pragma once

#include <core/event.hpp>
#include <fsm/action.hpp>
#include <fsm/guard.hpp>
#include <fsm/state.hpp>
#include <memory>
#include <vector>

class Transition {
 public:
  Transition(std::shared_ptr<State> from_state, Event event,
             const std::vector<std::shared_ptr<Guard>> &guards,
             const std::vector<std::shared_ptr<Action>> &actions, std::shared_ptr<State> to_state)
      : from_state_(from_state),
        event_(event),
        guards_(guards),
        actions_(actions),
        to_state_(to_state) {}

  std::shared_ptr<State> from_state() const { return from_state_; }
  Event event() const { return event_; }
  std::vector<std::shared_ptr<Guard>> guards() const { return guards_; }
  std::vector<std::shared_ptr<Action>> actions() const { return actions_; }
  std::shared_ptr<State> to_state() const { return to_state_; }

 private:
  std::shared_ptr<State> from_state_;
  Event event_;
  std::vector<std::shared_ptr<Guard>> guards_;
  std::vector<std::shared_ptr<Action>> actions_;
  std::shared_ptr<State> to_state_;
};