#include "Strategy.hpp"

void Strategy::Buy(Size size)
{
  if (size > 0)
    return broker_->NewOrder(size);
}

void Strategy::Sell(Size size)
{
  if (size > 0)
    return broker_->NewOrder(-size);
}

void Strategy::ClosePosition()
{
  return broker_->NewOrder(-(broker_->GetPosition()));
}

void Strategy::ReducePosition(Size size)
{
  if (broker_->IsLong())
    return broker_->NewOrder(-size);
  return broker_->NewOrder(size);
}