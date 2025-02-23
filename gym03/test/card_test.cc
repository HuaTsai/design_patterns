#include <gtest/gtest.h>

#include "poker_card.hpp"
#include "uno_card.hpp"

TEST(PokerCard, String) {
  PokerCard card1(Suit::kClub, Rank::kAce);
  EXPECT_EQ(card1.string(), "Ace of Clubs");

  auto card2 = std::shared_ptr<Card>(new PokerCard(Suit::kSpade, Rank::kKing));
  EXPECT_EQ(card2->string(), "King of Spades");

  std::ostringstream oss;
  oss << card2;
  EXPECT_EQ(oss.str(), "King of Spades");

  std::ostringstream oss2;
  oss2 << std::format("{}", card2);
  EXPECT_EQ(oss2.str(), "King of Spades");
}

TEST(UnoCard, String) {
  UNOCard card1(Color::kBlue, Number::kZero);
  EXPECT_EQ(card1.string(), "Blue Zero");

  auto card2 = std::shared_ptr<Card>(new UNOCard(Color::kRed, Number::kFour));
  EXPECT_EQ(card2->string(), "Red Four");

  std::ostringstream oss;
  oss << card2;
  EXPECT_EQ(oss.str(), "Red Four");

  std::ostringstream oss2;
  oss2 << std::format("{}", card2);
  EXPECT_EQ(oss2.str(), "Red Four");
}

TEST(PokerCard, Comparison) {
  PokerCard card1(Suit::kClub, Rank::kAce);
  PokerCard card2(Suit::kClub, Rank::kTwo);
  EXPECT_GT(card1, card2);

  PokerCard card3(Suit::kDiamond, Rank::kAce);
  EXPECT_LT(card1, card3);
}
