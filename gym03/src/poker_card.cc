#include "poker_card.hpp"

std::string PokerCard::string() const {
  std::string ret;
  switch (rank_) {
    case Rank::kAce:
      ret = "Ace";
      break;
    case Rank::kTwo:
      ret = "Two";
      break;
    case Rank::kThree:
      ret = "Three";
      break;
    case Rank::kFour:
      ret = "Four";
      break;
    case Rank::kFive:
      ret = "Five";
      break;
    case Rank::kSix:
      ret = "Six";
      break;
    case Rank::kSeven:
      ret = "Seven";
      break;
    case Rank::kEight:
      ret = "Eight";
      break;
    case Rank::kNine:
      ret = "Nine";
      break;
    case Rank::kTen:
      ret = "Ten";
      break;
    case Rank::kJack:
      ret = "Jack";
      break;
    case Rank::kQueen:
      ret = "Queen";
      break;
    case Rank::kKing:
      ret = "King";
      break;
    default:
      throw std::runtime_error("Invalid rank");
  }

  ret += " of ";

  switch (suit_) {
    case Suit::kClub:
      ret += "Clubs";
      break;
    case Suit::kDiamond:
      ret += "Diamonds";
      break;
    case Suit::kHeart:
      ret += "Hearts";
      break;
    case Suit::kSpade:
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
