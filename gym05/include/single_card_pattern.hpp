#include "card_pattern.hpp"

class SingleCardPattern : public CardPattern {
 public:
  using CardPattern::CardPattern;
};

class SingleCardPatternRecognizer : public CardPatternRecognizer {
 public:
  using CardPatternRecognizer::CardPatternRecognizer;
  bool Match(std::vector<std::shared_ptr<Card>> cards) const override;
  std::shared_ptr<CardPattern> CreateConcreteCardPatternImpl(
      std::vector<std::shared_ptr<Card>> cards) const override;
};
