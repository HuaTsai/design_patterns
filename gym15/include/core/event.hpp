#pragma once

enum class Event {
  kStateEnd,
  kLogin,
  kLogout,
  kSendMessage,
  kNewPost,
  kGoBroadcasting,
  kSpeak,
  kStopBroadcasting,
  kWait
};