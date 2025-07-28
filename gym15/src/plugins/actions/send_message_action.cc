#include <core/waterball_community.hpp>
#include <plugins/actions/send_message_action.hpp>

SendMessageAction::SendMessageAction(const std::string &message) : message_(message) {}

void SendMessageAction::operator()() const { parent_fsm()->robot()->SendMessage(message_, {}); }