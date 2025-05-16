#include <gtest/gtest.h>

#include "ai_player.hpp"
#include "human_player.hpp"
#include "poker_card.hpp"
#include "uno_card.hpp"

TEST(AIPlayerTest, UNODrawThenShow) {
  auto deck = Deck::CreateUNODeck();
  for (int i = 0; i < 40; i++) deck->Deal();
  std::vector<std::shared_ptr<Card>> cards = {std::make_shared<UNOCard>(Color::kRed, Number::kTwo)};
  deck->AddCards(cards);
  auto topcard = std::make_shared<UNOCard>(Color::kRed, Number::kOne);

  AIPlayer player(Player::Type::kUNO);
  player.Draw(deck);
  player.UpdateTopCard(topcard);
  auto card = player.Show();
  EXPECT_EQ(card->string(), "Red Two");
}

TEST(AIPlayerTest, ShowdownDrawThenShow) {
  auto deck = Deck::CreatePokerDeck();
  for (int i = 0; i < 52; i++) deck->Deal();
  std::vector<std::shared_ptr<Card>> cards = {
      std::make_shared<PokerCard>(Suit::kHeart, Rank::kFour)};
  deck->AddCards(cards);

  AIPlayer player(Player::Type::kShowdown);
  player.Draw(deck);
  auto card = player.Show();
  EXPECT_EQ(card->string(), "Four of Hearts");
}

TEST(HumanPlayerTest, UNODrawThenShow) {
  std::ostringstream output;
  std::streambuf *original_cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());
  std::istringstream input("p1\n1\n");
  std::streambuf *original_cin_buffer = std::cin.rdbuf();
  std::cin.rdbuf(input.rdbuf());

  auto deck = Deck::CreateUNODeck();
  for (int i = 0; i < 40; i++) deck->Deal();
  std::vector<std::shared_ptr<Card>> cards = {std::make_shared<UNOCard>(Color::kRed, Number::kTwo)};
  deck->AddCards(cards);
  auto topcard = std::make_shared<UNOCard>(Color::kRed, Number::kOne);

  HumanPlayer player(Player::Type::kUNO);
  player.Draw(deck);
  player.NameSelf();
  player.UpdateTopCard(topcard);
  auto card = player.Show();
  EXPECT_EQ(card->string(), "Red Two");

  std::cin.rdbuf(original_cin_buffer);
  std::cout.rdbuf(original_cout_buffer);
}

TEST(HumanPlayerTest, ShowdownDrawThenShow) {
  std::ostringstream output;
  std::streambuf *original_cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());
  std::istringstream input("p1\n1\n");
  std::streambuf *original_cin_buffer = std::cin.rdbuf();
  std::cin.rdbuf(input.rdbuf());

  auto deck = Deck::CreatePokerDeck();
  for (int i = 0; i < 52; i++) deck->Deal();
  std::vector<std::shared_ptr<Card>> cards = {
      std::make_shared<PokerCard>(Suit::kHeart, Rank::kFour)};
  deck->AddCards(cards);

  HumanPlayer player(Player::Type::kShowdown);
  player.Draw(deck);
  player.NameSelf();
  auto card = player.Show();
  EXPECT_EQ(card->string(), "Four of Hearts");

  std::cin.rdbuf(original_cin_buffer);
  std::cout.rdbuf(original_cout_buffer);
}
