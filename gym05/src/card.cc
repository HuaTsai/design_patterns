#include "card.hpp"

#include <iostream>
#include <unordered_map>

namespace {
const std::unordered_map<char, Suit> char_to_suit_map = {
    {'C', Suit::kClubs}, {'D', Suit::kDiamonds}, {'H', Suit::kHearts}, {'S', Suit::kSpades}};

const std::unordered_map<std::string, Rank> str_to_rank_map = {
    {"3", Rank::kThree}, {"4", Rank::kFour},  {"5", Rank::kFive}, {"6", Rank::kSix},
    {"7", Rank::kSeven}, {"8", Rank::kEight}, {"9", Rank::kNine}, {"10", Rank::kTen},
    {"J", Rank::kJack},  {"Q", Rank::kQueen}, {"K", Rank::kKing}, {"A", Rank::kAce},
    {"2", Rank::kTwo}};

const std::unordered_map<Suit, char> suit_to_char_map = {
    {Suit::kClubs, 'C'}, {Suit::kDiamonds, 'D'}, {Suit::kHearts, 'H'}, {Suit::kSpades, 'S'}};

const std::unordered_map<Rank, std::string> rank_to_str_map = {
    {Rank::kThree, "3"}, {Rank::kFour, "4"},  {Rank::kFive, "5"}, {Rank::kSix, "6"},
    {Rank::kSeven, "7"}, {Rank::kEight, "8"}, {Rank::kNine, "9"}, {Rank::kTen, "10"},
    {Rank::kJack, "J"},  {Rank::kQueen, "Q"}, {Rank::kKing, "K"}, {Rank::kAce, "A"},
    {Rank::kTwo, "2"}};
}  // namespace

Card::Card(const std::string& card) {
  suit_ = char_to_suit_map.at(card[0]);
  rank_ = str_to_rank_map.at(card.substr(2, card.size() - 3));
}

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

std::strong_ordering Card::operator<=>(const Card &other) const {
  if (auto cmp = (rank_ <=> other.rank_); cmp != 0) return cmp;
  return suit_ <=> other.suit_;
}

std::string Card::string() const {
  std::string ret;
  ret += suit_to_char_map.at(suit_);
  ret += "[" + rank_to_str_map.at(rank_) + "]";
  return ret;
};

Suit Card::suit() { return suit_; }

Rank Card::rank() { return rank_; }

std::ostream &operator<<(std::ostream &os, std::shared_ptr<Card> card) {
  return os << card->string();
}
