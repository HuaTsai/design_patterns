#include "card_pattern.hpp"

class SingleCardPattern : public CardPattern {
 public:
  using CardPattern::CardPattern;
};

class SingleCardPatternRecognizer : public CardPatternRecognizer {
 public:
  using CardPatternRecognizer::CardPatternRecognizer;
  bool Match(const std::vector<std::shared_ptr<Card>> &cards) const override;
  std::shared_ptr<CardPattern> CreateConcreteCardPatternImpl(
      const std::vector<std::shared_ptr<Card>> &cards) const override;
};
