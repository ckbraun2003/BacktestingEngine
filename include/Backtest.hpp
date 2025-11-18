#pragma once

#include "Strategy.hpp"


class Backtest
{
public:
  Backtest(DataObject data, StrategyPointer strategy, Cash cash, Cash commission, Margin margin, Cash spread, Return riskFreeRate, bool tradeOnClose = false);

  void RunBacktest();
  void PrintStatistics();

private:

  Return riskFreeRate_;
  DataObject data_;
  BrokerPointer broker_;
  StrategyPointer strategy_;
  Stats statistics_;

  Stats ComputeStatistics(const Trades& trades, const Equity& equity, const Return riskFreeRate, const DataObject& olhcvBars);
  std::string timepointToString(Time timepoint);

};