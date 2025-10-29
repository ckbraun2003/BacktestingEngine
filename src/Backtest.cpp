#include "Backtest.hpp"

Backtest::Backtest(std::unique_ptr<Strategy> strategy_, const Bars& bars_)
  : strategy_(std::move(strategy_))
  , bars_{ bars_ }
{ }

void Backtest::Run() const
{
  strategy_->Initialize();
  strategy_->Next();
}