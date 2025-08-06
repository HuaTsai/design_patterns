#include "human_player.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

std::shared_ptr<CardPattern> HumanPlayer::FirstPlay(bool club_three_required) {
  std::cout << std::format("輪到{}了\n", name_);
  std::string cmd;

  std::shared_ptr<CardPattern> ret;
  std::vector<std::shared_ptr<Card>> cards;

  PrintHandCards();
  std::getline(std::cin, cmd);

  while (true) {
    if (cmd == "-1") {
      std::cout << "你不能在新的回合中喊 PASS\n";
      PrintHandCards();
      std::getline(std::cin, cmd);
      continue;
    }

    std::stringstream ss(cmd);
    int num = 0;
    cards.clear();
    while (ss >> num) {
      cards.push_back(hand_cards_[num]);
    }

    if (club_three_required && !std::ranges::any_of(cards, [](auto card) {
          return card->suit() == Suit::kClubs && card->rank() == Rank::kThree;
        })) {
      std::cout << "此牌型不合法，請再嘗試一次。\n";
      PrintHandCards();
      std::getline(std::cin, cmd);
      continue;
    }

    ret = recognizer_->CreateConcreteCardPattern(cards);
    if (ret) {
      break;
    }

    std::cout << "此牌型不合法，請再嘗試一次。\n";
    PrintHandCards();
    std::getline(std::cin, cmd);
  }

  for (const auto &card : cards) {
    std::erase(hand_cards_, card);
  }

  std::cout << std::format("玩家 {} 打出了 {}\n", name_, ret->string());
  return ret;
}

std::shared_ptr<CardPattern> HumanPlayer::FollowPlay(std::shared_ptr<CardPattern> top_play) {
  std::cout << std::format("輪到{}了\n", name_);

  std::shared_ptr<CardPattern> ret;
  std::vector<std::shared_ptr<Card>> cards;
  std::string cmd;

  PrintHandCards();
  std::getline(std::cin, cmd);

  while (true) {
    if (cmd == "-1") {
      std::cout << std::format("玩家 {} PASS.\n", name_);
      return nullptr;
    }
    cards.clear();

    std::stringstream ss(cmd);
    int num = 0;
    while (ss >> num) {
      cards.push_back(hand_cards_[num]);
    }

    ret = recognizer_->CreateConcreteCardPattern(cards);

    auto &type1 = *top_play;
    auto &type2 = *ret;
    if (ret && typeid(type1) == typeid(type2) && *ret > *top_play) {
      break;
    }

    std::cout << "此牌型不合法，請再嘗試一次。\n";
    PrintHandCards();
    std::getline(std::cin, cmd);
  }

  for (const auto &card : cards) {
    std::erase(hand_cards_, card);
  }

  std::cout << std::format("玩家 {} 打出了 {}\n", name_, ret->string());
  return ret;
}
