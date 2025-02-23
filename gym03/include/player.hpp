#pragma once

#include <string>

#include "deck.hpp"

class Player {
 public:
  enum class Type { kShowdown, kUNO };

  explicit Player(Type type);
  virtual ~Player() = default;

  virtual void NameSelf() = 0;
  void Draw(std::shared_ptr<Deck> deck);
  void UpdateTopCard(std::shared_ptr<Card> card);
  void AddPoint();
  virtual std::shared_ptr<Card> Show() = 0;
  bool IsEmptyHand() const;

  std::string name() const;
  int points() const;

 protected:
  Type type_;
  int points_;
  std::string name_;
  std::shared_ptr<Card> topcard_;
  std::vector<std::shared_ptr<Card>> hand_;
};
