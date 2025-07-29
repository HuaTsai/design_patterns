#include <core/waterball_community.hpp>
#include <plugins/states/knowledge_king_state.hpp>
#include <plugins/states/questioning_state.hpp>
#include <plugins/states/thanks_for_joining_state.hpp>

KnowledgeKingState::KnowledgeKingState(std::shared_ptr<FiniteStateMachine> child_fsm)
    : State(child_fsm), scores_(std::make_shared<std::unordered_map<std::string, int>>()) {}

void KnowledgeKingState::OnEnter() {
  parent_fsm()->robot()->SendMessage("KnowledgeKing is started!", {});

  std::shared_ptr<QuestioningState> questioning_state;
  std::shared_ptr<ThanksForJoiningState> thanks_for_joining_state;

  for (const auto &state : child_fsm()->states()) {
    if (auto qs = std::dynamic_pointer_cast<QuestioningState>(state)) {
      questioning_state = qs;
    }
    if (auto ts = std::dynamic_pointer_cast<ThanksForJoiningState>(state)) {
      thanks_for_joining_state = ts;
    }
  }

  questioning_state->set_scores(scores_);
  thanks_for_joining_state->set_scores(scores_);

  child_fsm()->Initialize(questioning_state);
}

Event KnowledgeKingState::OnDo(Event event) { return event; }

void KnowledgeKingState::OnExit() { /* nop */
}