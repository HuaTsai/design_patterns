#include "deck.hpp"

#include <gtest/gtest.h>

#include "poker_card.hpp"
#include "uno_card.hpp"

TEST(Deck, CreateUNODeck) {
  auto deck = Deck::CreateUNODeck();
  for (int i = 0; i < 40; ++i) {
    deck->Deal();
  }
  EXPECT_THROW(deck->Deal(), std::out_of_range);

  auto card = std::make_shared<UNOCard>(Color::kRed, Number::kZero);
  std::vector<std::shared_ptr<Card>> cards{card};
  deck->AddCards(cards);
  auto dealt_card = deck->Deal();
  EXPECT_EQ(dealt_card->string(), "Red Zero");
}

TEST(Deck, CreatePokerDeck) {
  auto deck = Deck::CreatePokerDeck();
  for (int i = 0; i < 52; ++i) {
    deck->Deal();
  }
  EXPECT_THROW(deck->Deal(), std::out_of_range);

  auto card = std::make_shared<PokerCard>(Suit::kSpade, Rank::kSix);
  std::vector<std::shared_ptr<Card>> cards{card};
  deck->AddCards(cards);
  auto dealt_card = deck->Deal();
  EXPECT_EQ(dealt_card->string(), "Six of Spades");
}
