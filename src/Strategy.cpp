#include "Strategy.hpp"

void Strategy::Buy(Size size)
{
  if (0 < size < 1 || std::round(size) == (size >= 1))
    return broker_->NewOrder(size);
}

void Strategy::Sell(Size size)
{
  if (0 < size < 1 || std::round(size) == (size >= 1))
    return broker_->NewOrder(-size);
}