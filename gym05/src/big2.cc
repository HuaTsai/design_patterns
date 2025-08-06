#include "big2.hpp"

#include <iostream>

#include "full_house_card_pattern.hpp"
#include "human_player.hpp"
#include "pair_card_pattern.hpp"
#include "single_card_pattern.hpp"
#include "straight_card_pattern.hpp"

void Big2::GameStart() {
  recognizer_ = std::make_shared<SingleCardPatternRecognizer>(
      std::make_shared<PairCardPatternRecognizer>(std::make_shared<StraightCardPatternRecognizer>(
          std::make_shared<FullHouseCardPatternRecognizer>())));

  PrepareSuffledDeck();
  // PrepareDeck();  // create normal deck
  EnterNames();
  // ShuffleCards();  // shuffle normal deck
  DealCards();
  while (!winner_) {
    RoundStart();
  }
  ShowWinner();
}

void Big2::PrepareDeck() { deck_ = std::make_shared<Deck>(); }

void Big2::PrepareSuffledDeck() {
  std::vector<std::shared_ptr<Card>> cards;
  for (int i = 0; i < 52; ++i) {
    std::string card;
    std::cin >> card;
    cards.push_back(std::make_shared<Card>(card));
  }
  std::cin.ignore();  // ignore the newline character
  deck_ = std::make_shared<Deck>(cards);
}

void Big2::EnterNames() {
  for (int i = 0; i < 4; ++i) {
    std::string name;
    std::getline(std::cin, name);
    players_.push_back(std::make_shared<HumanPlayer>(name, recognizer_));
  }
}

void Big2::ShuffleCards() { deck_->Shuffle(); }

void Big2::DealCards() {
  int i = 0;
  while (!deck_->IsEmpty()) {
    players_[i]->AddCard(deck_->Deal());
    i = (i + 1) % 4;
  }
}

void Big2::RoundStart() {
  static int round = 1;
  static int id = -1;

  std::cout << "新的回合開始了。\n";

  if (round == 1) {
    for (int i = 0; i < 4; ++i) {
      if (players_[i]->HasClubThreeInHand()) {
        top_player_ = players_[i];
        id = i;
        break;
      }
    }
    top_play_ = top_player_->FirstPlay(true);
    while (!top_play_) {
      top_play_ = top_player_->FirstPlay(true);
    }
  } else {
    top_play_ = top_player_->FirstPlay(false);
    while (!top_play_) {
      top_play_ = top_player_->FirstPlay(false);
    }
  }
  if (top_player_->IsEmptyHandCards()) {
    winner_ = top_player_;
    return;
  }

  id = (id + 1) % 4;
  top_player_ = players_[id];

  int consecutive_passes = 0;
  while (consecutive_passes != 3) {
    auto play = top_player_->FollowPlay(top_play_);
    if (play && top_player_->IsEmptyHandCards()) {
      winner_ = top_player_;
      break;
    }
    if (play) {
      top_play_ = play;
      consecutive_passes = 0;
    } else {
      ++consecutive_passes;
    }
    id = (id + 1) % 4;
    top_player_ = players_[id];
  }

  ++round;
}

void Big2::ShowWinner() {
  std::cout << std::format("遊戲結束，遊戲的勝利者為 {}\n", winner_->name());
}
