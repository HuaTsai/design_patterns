#include "card_pattern.hpp"

class PairCardPattern : public CardPattern {
 public:
  using CardPattern::CardPattern;
};

class PairCardPatternRecognizer : public CardPatternRecognizer {
 public:
  using CardPatternRecognizer::CardPatternRecognizer;
  bool Match(std::vector<std::shared_ptr<Card>> cards) const override;
  std::shared_ptr<CardPattern> CreateConcreteCardPatternImpl(
      std::vector<std::shared_ptr<Card>> cards) const override;
};
