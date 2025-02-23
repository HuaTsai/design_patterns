#include "strategy.hpp"

Strategy::Strategy(const std::vector<std::shared_ptr<Individual>> &individuals)
    : individuals_(individuals), reverse_(false), rng_(std::random_device{}()) {}
