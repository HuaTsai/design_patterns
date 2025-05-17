#pragma once

#include <string>

#include "deck.hpp"

class Player {
 public:
  enum class Type { kShowdown, kUNO };

  explicit Player(Type type);

  virtual ~Player() = default;
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player(Player &&) = delete;
  Player &operator=(Player &&) = delete;

  virtual void NameSelf() = 0;
  void Draw(std::shared_ptr<Deck> deck);
  void UpdateTopCard(std::shared_ptr<Card> card);
  void AddPoint();
  virtual std::shared_ptr<Card> Show() = 0;
  bool IsEmptyHand() const;

  void set_name(const std::string &name) { name_ = name; }
  Type type() const;
  int points() const;
  std::string name() const;
  std::shared_ptr<Card> topcard() const;
  std::vector<std::shared_ptr<Card>> hand() const;
  std::vector<std::shared_ptr<Card>> &hand();

 private:
  Type type_;
  int points_;
  std::string name_;
  std::shared_ptr<Card> topcard_;
  std::vector<std::shared_ptr<Card>> hand_;
};
