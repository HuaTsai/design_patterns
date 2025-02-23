#pragma once

#include <string>
#include <vector>

#include "card.hpp"
#include "card_pattern.hpp"

class Player {
 public:
  explicit Player(std::string name, std::shared_ptr<CardPatternRecognizer> recognizer);
  virtual ~Player() = default;
  void AddCard(std::shared_ptr<Card> card);
  bool HasClubThreeInHand();
  bool IsEmptyHandCards() const;
  void PrintHandCards() const;
  virtual std::shared_ptr<CardPattern> FirstPlay(bool club_three_required = false) = 0;
  virtual std::shared_ptr<CardPattern> FollowPlay(std::shared_ptr<CardPattern> top_play) = 0;

  std::string name() const;

 protected:
  std::string name_;
  std::vector<std::shared_ptr<Card>> hand_cards_;
  std::shared_ptr<CardPatternRecognizer> recognizer_;
};
