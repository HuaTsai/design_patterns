#pragma once

#include <fsm/state.hpp>
#include <unordered_map>

class QuestioningState : public State {
 public:
  using State::State;

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;

  void set_scores(std::shared_ptr<std::unordered_map<std::string, int>> scores) {
    scores_ = scores;
  }

 private:
  int question_id_;
  int elapsed_time_;
  std::shared_ptr<std::unordered_map<std::string, int>> scores_;
};