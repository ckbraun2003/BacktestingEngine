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

  for (size_t i = 1; i < data_.size(); ++i)
  {
    broker_->Next(data_.at(i));
  }
}