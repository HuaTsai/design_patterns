#include <core/waterball_community.hpp>
#include <plugins/states/questioning_state.hpp>

namespace {
const std::array<std::string, 3> questions = {
    R"(0. 請問哪個 SQL 語句用於選擇所有的行？
A) SELECT *
B) SELECT ALL
C) SELECT ROWS
D) SELECT DATA)",
    R"(1. 請問哪個 CSS 屬性可用於設置文字的顏色？
A) text-align
B) font-size
C) color
D) padding)",
    R"(2. 請問在計算機科學中，「XML」代表什麼？
A) Extensible Markup Language
B) Extensible Modeling Language
C) Extended Markup Language
D) Extended Modeling Language)"};

const std::array<std::string, 3> answers = {"A", "C", "A"};
}  // namespace

void QuestioningState::OnEnter() {
  question_id_ = 0;
  elapsed_time_ = 0;
  scores_->clear();
  parent_fsm()->robot()->SendMessage(questions.at(question_id_), {});
}

Event QuestioningState::OnDo(Event event) {
  if (event == Event::kSendMessage) {
    auto message = parent_fsm()->robot()->community()->chat_room()->last_message();
    bool tagged = false;
    for (const auto &tag : message.tags) {
      if (tag.IsRobot()) {
        tagged = true;
        break;
      }
    }
    if (!tagged) {
      return event;
    }

    if (message.content == answers.at(question_id_)) {
      auto user_id = message.user.lock()->id();
      parent_fsm()->robot()->SendMessage("Congrats! you got the answer!", {Tag(user_id)});
      (*scores_)[user_id] += 1;
      if (++question_id_ == static_cast<int>(questions.size())) {
        return Event::kStateEnd;
      }
      parent_fsm()->robot()->SendMessage(questions.at(question_id_), {});
    }
  } else if (event == Event::kWait) {
    elapsed_time_ += parent_fsm()->robot()->community()->last_elapsed_time();
    if (elapsed_time_ >= 3600) {
      return Event::kStateEnd;
    }
  }
  return event;
}

void QuestioningState::OnExit() {}