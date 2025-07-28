#pragma once

#include <fsm/state.hpp>
#include <unordered_map>

class KnowledgeKingState : public State {
 public:
  KnowledgeKingState() = default;
  KnowledgeKingState(std::shared_ptr<FiniteStateMachine> child_fsm);

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;

 private:
  std::shared_ptr<std::unordered_map<std::string, int>> scores_;
};