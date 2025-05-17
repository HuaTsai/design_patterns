#include <gtest/gtest.h>

#include "poker_card.hpp"
#include "uno_card.hpp"


TEST(PokerCard, String) {
  using enum Rank;
  using enum Suit;
  const PokerCard card1(kClub, kAce);
  EXPECT_EQ(card1.string(), "Ace of Clubs");

  auto card2 = std::shared_ptr<Card>(new PokerCard(kSpade, kKing));
  EXPECT_EQ(card2->string(), "King of Spades");

  std::ostringstream oss;
  oss << card2;
  EXPECT_EQ(oss.str(), "King of Spades");

  std::ostringstream oss2;
  oss2 << std::format("{}", card2);
  EXPECT_EQ(oss2.str(), "King of Spades");
}

TEST(UnoCard, String) {
  using enum Color;
  using enum Number;
  const UNOCard card1(kBlue, kZero);
  EXPECT_EQ(card1.string(), "Blue Zero");

  auto card2 = std::shared_ptr<Card>(new UNOCard(kRed, kFour));
  EXPECT_EQ(card2->string(), "Red Four");

  std::ostringstream oss;
  oss << card2;
  EXPECT_EQ(oss.str(), "Red Four");

  std::ostringstream oss2;
  oss2 << std::format("{}", card2);
  EXPECT_EQ(oss2.str(), "Red Four");
}

TEST(PokerCard, Comparison) {
  using enum Rank;
  using enum Suit;
  const PokerCard card1(kClub, kAce);
  const PokerCard card2(kClub, kTwo);
  EXPECT_GT(card1, card2);

  const PokerCard card3(kDiamond, kAce);
  EXPECT_LT(card1, card3);
}
