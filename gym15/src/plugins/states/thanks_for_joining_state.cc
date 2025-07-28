#include <core/waterball_community.hpp>
#include <plugins/states/thanks_for_joining_state.hpp>

void ThanksForJoiningState::OnEnter() {
  elapsed_time_ = 0;

  std::vector<std::string> winners;
  int max_score = 0;
  for (const auto &[player_id, score] : *scores_) {
    if (score > max_score) {
      max_score = score;
      winners = {player_id};
    } else if (score == max_score) {
      winners.push_back(player_id);
    }
  }

  std::string result_message;
  if (winners.size() == 1) {
    result_message = "The winner is " + winners[0];
  } else {
    result_message = "Tie!";
  }

  auto robot = parent_fsm()->robot();
  if (robot->community()->broadcast()->speaker()) {
    robot->SendMessage(result_message, {});
  } else {
    robot->GoBroadcasting();
    robot->Speak(result_message);
    robot->StopBroadcasting();
  }
}

Event ThanksForJoiningState::OnDo(Event event) {
  if (event == Event::kWait) {
    elapsed_time_ += parent_fsm()->robot()->community()->last_elapsed_time();
    if (elapsed_time_ >= 20) {
      parent_fsm()->set_final_state(true);
      return Event::kStateEnd;
    }
  }
  return event;
}

void ThanksForJoiningState::OnExit() {}