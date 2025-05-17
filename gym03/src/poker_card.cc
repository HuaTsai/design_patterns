#include "poker_card.hpp"

std::string PokerCard::string() const {
  std::string ret;
  switch (rank_) {
    using enum Rank;
    case kAce:
      ret = "Ace";
      break;
    case kTwo:
      ret = "Two";
      break;
    case kThree:
      ret = "Three";
      break;
    case kFour:
      ret = "Four";
      break;
    case kFive:
      ret = "Five";
      break;
    case kSix:
      ret = "Six";
      break;
    case kSeven:
      ret = "Seven";
      break;
    case kEight:
      ret = "Eight";
      break;
    case kNine:
      ret = "Nine";
      break;
    case kTen:
      ret = "Ten";
      break;
    case kJack:
      ret = "Jack";
      break;
    case kQueen:
      ret = "Queen";
      break;
    case kKing:
      ret = "King";
      break;
    default:
      throw std::runtime_error("Invalid rank");
  }

  ret += " of ";

  switch (suit_) {
    using enum Suit;
    case kClub:
      ret += "Clubs";
      break;
    case kDiamond:
      ret += "Diamonds";
      break;
    case kHeart:
      ret += "Hearts";
      break;
    case kSpade:
      ret += "Spades";
      break;
    default:
      throw std::runtime_error("Invalid suit");
  }

  return ret;
}

std::strong_ordering PokerCard::operator<=>(const PokerCard &other) const {
  if (auto cmp = (rank_ <=> other.rank_); cmp != 0) return cmp;
  return suit_ <=> other.suit_;
}
