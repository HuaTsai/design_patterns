#include "card.hpp"

#include <compare>
#include <iostream>

Card::Card(int rank, Suit suit) : rank_(rank), suit_(suit) {}

auto Card::operator<=>(const Card &other) const {
  if (auto cmp = ((rank_ + 11) % 13) <=> ((other.rank_ + 11) % 13); cmp != 0) return cmp;
  return suit_ <=> other.suit_;
}

std::string Card::string() const {
  std::string ret;

  switch (rank_) {
    case 1:
      ret = "Ace";
      break;
    case 2:
      ret = "Two";
      break;
    case 3:
      ret = "Three";
      break;
    case 4:
      ret = "Four";
      break;
    case 5:
      ret = "Five";
      break;
    case 6:
      ret = "Six";
      break;
    case 7:
      ret = "Seven";
      break;
    case 8:
      ret = "Eight";
      break;
    case 9:
      ret = "Nine";
      break;
    case 10:
      ret = "Ten";
      break;
    case 11:
      ret = "Jack";
      break;
    case 12:
      ret = "Queen";
      break;
    case 13:
      ret = "King";
      break;
    default:
      throw std::runtime_error("Unknown number!");
  }

  ret += " of ";

  switch (suit_) {
    case Suit::Club:
      ret += "Clubs";
      break;
    case Suit::Diamond:
      ret += "Diamonds";
      break;
    case Suit::Heart:
      ret += "Hearts";
      break;
    case Suit::Spade:
      ret += "Spades";
      break;
    default:
      throw std::runtime_error("Unknown suit!");
  }

  return ret;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << card.string();
  return os;
}
