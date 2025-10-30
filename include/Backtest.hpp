#pragma once

#include "Strategy.hpp"


class Backtest
{
public:
  Backtest(DataObject data, StrategyPointer strategy, Cash cash, Cash commission, Margin margin, Cash spread, bool tradeOnClose = false);

  void RunBacktest();

private:

  DataObject data_;
  BrokerPointer broker_;
  StrategyPointer strategy_;

};