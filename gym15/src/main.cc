#include <fstream>
#include <plugins/actions/consume_constant_quota_action.hpp>
#include <plugins/actions/send_message_action.hpp>
#include <plugins/guards/message_content_equal_guard.hpp>
#include <plugins/guards/message_is_sent_by_admin_guard.hpp>
#include <plugins/guards/message_is_sent_by_recorder_guard.hpp>
#include <plugins/guards/message_tag_user_guard.hpp>
#include <plugins/guards/online_users_count_guard.hpp>
#include <plugins/guards/quota_count_guard.hpp>
#include <plugins/states/default_conversation_state.hpp>
#include <plugins/states/interacting_state.hpp>
#include <plugins/states/knowledge_king_state.hpp>
#include <plugins/states/normal_state.hpp>
#include <plugins/states/questioning_state.hpp>
#include <plugins/states/record_state.hpp>
#include <plugins/states/recording_state.hpp>
#include <plugins/states/thanks_for_joining_state.hpp>
#include <plugins/states/waiting_state.hpp>
#include <print>
#include <waterball_community_facade.hpp>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::print("Usage: {} <input_file>\n", argv[0]);
    return 1;
  }

  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::print("Could not open file: {}\n", argv[1]);
    return 1;
  }

  WaterballCommunityFacade waterball_community_facade;

  // clang-format off
  auto robot = waterball_community_facade.CreateRobot("bot");

  // 1. Normal State: Default Conversation State and Interacting State
  auto default_conversation_state = std::make_shared<DefaultConversationState>();
  auto interacting_state = std::make_shared<InteractingState>();
  auto normal_states = std::vector<std::shared_ptr<State>>{default_conversation_state, interacting_state};
  auto online_users_at_least_ten_guard = std::make_shared<OnlineUsersCountGuard>(10, std::greater_equal<>());
  auto online_users_less_than_ten_guard = std::make_shared<OnlineUsersCountGuard>(10, std::less<>());
  auto normal_transitions = std::vector<Transition>{
      Transition(default_conversation_state, Event::kLogin, {online_users_at_least_ten_guard}, {}, interacting_state),
      Transition(interacting_state, Event::kLogout, {online_users_less_than_ten_guard}, {}, default_conversation_state)};
  auto normal_fsm = std::make_shared<FiniteStateMachine>(robot, normal_states, normal_transitions);

  default_conversation_state->set_parent_fsm(normal_fsm);
  interacting_state->set_parent_fsm(normal_fsm);
  online_users_at_least_ten_guard->set_parent_fsm(normal_fsm);
  online_users_less_than_ten_guard->set_parent_fsm(normal_fsm);
  auto normal_state = std::make_shared<NormalState>(normal_fsm);

  // 2. Record State: Waiting State and Recording State
  auto waiting_state = std::make_shared<WaitingState>();
  auto recording_state = std::make_shared<RecordingState>();
  auto record_states = std::vector<std::shared_ptr<State>>{waiting_state, recording_state};
  auto record_transitions = std::vector<Transition>{
      Transition(waiting_state, Event::kGoBroadcasting, {}, {}, recording_state),
      Transition(recording_state, Event::kStopBroadcasting, {}, {}, waiting_state)};
  auto record_fsm = std::make_shared<FiniteStateMachine>(robot, record_states, record_transitions);

  waiting_state->set_parent_fsm(record_fsm);
  recording_state->set_parent_fsm(record_fsm);
  auto record_state = std::make_shared<RecordState>(record_fsm);

  // 3. Knowledge King State: Questioning State and Thanks for Joining State
  auto questioning_state = std::make_shared<QuestioningState>();
  auto thanks_for_joining_state = std::make_shared<ThanksForJoiningState>();
  auto knowledge_king_states = std::vector<std::shared_ptr<State>>{questioning_state, thanks_for_joining_state};
  auto message_is_play_again_guard = std::make_shared<MessageContentEqualGuard>("play again");
  auto quota_at_least_five_guard = std::make_shared<QuotaCountGuard>(5, std::greater_equal<>());
  auto consume_five_quota_action = std::make_shared<ConsumeConstantQuotaAction>(5);
  auto send_start_again_message_action = std::make_shared<SendMessageAction>("KnowledgeKing is gonna start again!");
  auto knowledge_king_transitions = std::vector<Transition>{
      Transition(questioning_state, Event::kStateEnd, {}, {}, thanks_for_joining_state),
      Transition(thanks_for_joining_state, Event::kSendMessage, {message_is_play_again_guard, quota_at_least_five_guard}, {consume_five_quota_action, send_start_again_message_action}, questioning_state)
  };
  auto knowledge_king_fsm = std::make_shared<FiniteStateMachine>(robot, knowledge_king_states, knowledge_king_transitions);
  
  questioning_state->set_parent_fsm(knowledge_king_fsm);
  thanks_for_joining_state->set_parent_fsm(knowledge_king_fsm);
  message_is_play_again_guard->set_parent_fsm(knowledge_king_fsm);
  quota_at_least_five_guard->set_parent_fsm(knowledge_king_fsm);
  consume_five_quota_action->set_parent_fsm(knowledge_king_fsm);
  send_start_again_message_action->set_parent_fsm(knowledge_king_fsm);
  auto knowledge_king_state = std::make_shared<KnowledgeKingState>(knowledge_king_fsm);

  // Root FSM
  auto root_states = std::vector<std::shared_ptr<State>>{normal_state, record_state, knowledge_king_state};
  auto message_tag_robot_guard = std::make_shared<MessageTagUserGuard>("bot");
  auto message_is_record_guard = std::make_shared<MessageContentEqualGuard>("record");
  auto quota_at_least_three_guard = std::make_shared<QuotaCountGuard>(3, std::greater_equal<>());
  auto consume_three_quota_action = std::make_shared<ConsumeConstantQuotaAction>(3);
  auto message_is_stop_record_guard = std::make_shared<MessageContentEqualGuard>("stop-recording");
  auto message_is_sent_by_recorder_guard = std::make_shared<MessageIsSentByRecorderGuard>();
  auto message_is_king_guard = std::make_shared<MessageContentEqualGuard>("king");
  auto message_is_sent_by_admin_guard = std::make_shared<MessageIsSentByAdminGuard>();
  auto quota_at_least_five_guard2 = std::make_shared<QuotaCountGuard>(5, std::greater_equal<>());
  auto consume_five_quota_action2 = std::make_shared<ConsumeConstantQuotaAction>(5);
  auto message_is_king_stop_guard = std::make_shared<MessageContentEqualGuard>("king-stop");
  auto root_transitions = std::vector<Transition>{
      Transition(normal_state, Event::kSendMessage, {message_tag_robot_guard, message_is_record_guard, quota_at_least_three_guard}, {consume_three_quota_action}, record_state),
      Transition(record_state, Event::kSendMessage, {message_tag_robot_guard, message_is_stop_record_guard, message_is_sent_by_recorder_guard}, {}, normal_state),
      Transition(normal_state, Event::kSendMessage, {message_tag_robot_guard, message_is_king_guard, message_is_sent_by_admin_guard, quota_at_least_five_guard2}, {consume_five_quota_action2}, knowledge_king_state),
      Transition(knowledge_king_state, Event::kSendMessage, {message_tag_robot_guard, message_is_king_stop_guard, message_is_sent_by_admin_guard}, {}, normal_state),
      Transition(knowledge_king_state, Event::kStateEnd, {}, {}, normal_state)
  };
  auto root_fsm = std::make_shared<FiniteStateMachine>(robot, root_states, root_transitions);

  normal_state->set_parent_fsm(root_fsm);
  record_state->set_parent_fsm(root_fsm);
  knowledge_king_state->set_parent_fsm(root_fsm);
  message_tag_robot_guard->set_parent_fsm(root_fsm);
  message_is_record_guard->set_parent_fsm(root_fsm);
  quota_at_least_three_guard->set_parent_fsm(root_fsm);
  consume_three_quota_action->set_parent_fsm(root_fsm);
  message_is_stop_record_guard->set_parent_fsm(root_fsm);
  message_is_sent_by_recorder_guard->set_parent_fsm(root_fsm);
  message_is_king_guard->set_parent_fsm(root_fsm);
  message_is_sent_by_admin_guard->set_parent_fsm(root_fsm);
  quota_at_least_five_guard2->set_parent_fsm(root_fsm);
  consume_five_quota_action2->set_parent_fsm(root_fsm);
  message_is_king_stop_guard->set_parent_fsm(root_fsm);

  // Initialize FSM
  root_fsm->Initialize(normal_state);
  WaterballCommunityFacade::AssociateRobotWithFSM("bot", root_fsm);
  // clang-format on

  std::string line;
  while (std::getline(ifs, line)) {
    auto bracket_end = line.find(']');
    const std::string action = line.substr(1, bracket_end - 1);
    if (action == "end") {
      break;
    }

    if (action.ends_with("elapsed")) {
      waterball_community_facade.Input(action);
    } else {
      const nlohmann::json j = nlohmann::json::parse(line.substr(bracket_end + 2));
      waterball_community_facade.Input(action, j);
    }
  }

  ifs.close();
}
