#include "Backtest.hpp"

Backtest::Backtest(DataObject data, StrategyPointer strategy, Cash cash, Cash commission, Margin margin, Cash spread, bool tradeOnClose)
  : data_{ data }
  , broker_(std::make_shared<Broker>(data_, cash, commission, margin, spread, tradeOnClose))
  , strategy_(std::move(strategy))
{
  strategy_->SetBroker(broker_);
  strategy_->SetData(data_);
}

void Backtest::RunBacktest()
{
  strategy_->Initialize();

  for (int i = 0; i < data_.size(); ++i)
  {
    if (i != 0)
      broker_->Next(data_.at(i));

    strategy_->Next();
  }
  backtestStats_ = strategy_->ComputeStatistics();
}

void Backtest::PrintStats()
{
  std::cout << std::format("Final Return [%] : {}\nNumber of Trades : {}", backtestStats_.finalReturns_, backtestStats_.numberOfTrades_);
}