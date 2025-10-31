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
    return Sell(size);
  else
    return Buy(size);
}

Stats Strategy::ComputeStatistics()
{
  Stats backtestStats;
  auto& equity = broker_->GetEquity();
  auto& trades = broker_->GetClosedTrades();

  backtestStats.finalReturns_ = (equity.back() - equity.front()) / (equity.front());
  backtestStats.numberOfTrades_ = trades.size();

  return backtestStats;
}