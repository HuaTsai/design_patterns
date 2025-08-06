#include <algorithm>
#include <iostream>
#include <random>

#include "ai_player.hpp"
#include "deck.hpp"
#include "human_player.hpp"
#include "showdown_card_game.hpp"
#include "uno_card_game.hpp"

int main() {
  std::cout << "Welcome to Card Game!\nShowdown(0) or UNO(1)? ";
  int gametype = 0;
  std::cin >> gametype;

  std::shared_ptr<Deck> deck;
  if (gametype == 0) {
    deck = Deck::CreatePokerDeck();
  } else if (gametype == 1) {
    deck = Deck::CreateUNODeck();
  } else {
    throw std::runtime_error("Invalid game type");
  }

  std::cout << "Enter number of ai players (0-4)? ";
  int num_ai = 0;
  std::cin >> num_ai;
  if (num_ai < 0 || num_ai > 4) {
    throw std::runtime_error("Invalid number of AI players");
  }
  std::vector<std::shared_ptr<Player>> players(4);

  for (int i = 0; i < num_ai; ++i) {
    if (gametype == 0) {
      players[i] = std::make_shared<AIPlayer>(Player::Type::kShowdown);
    } else if (gametype == 1) {
      players[i] = std::make_shared<AIPlayer>(Player::Type::kUNO);
    }
  }
  for (int i = num_ai; i < 4; ++i) {
    if (gametype == 0) {
      players[i] = std::make_shared<HumanPlayer>(Player::Type::kShowdown);
    } else if (gametype == 1) {
      players[i] = std::make_shared<HumanPlayer>(Player::Type::kUNO);
    }
  }

  std::ranges::shuffle(players, std::mt19937{std::random_device{}()});

  std::shared_ptr<CardGame> card_game;
  if (gametype == 0) {
    card_game = std::make_shared<ShowdownCardGame>(deck, players);
  } else if (gametype == 1) {
    card_game = std::make_shared<UNOCardGame>(deck, players);
  }
  card_game->PreparePhase();
  card_game->DrawPhase();
  card_game->PlayPhase();
  card_game->ScorePhase();
}
