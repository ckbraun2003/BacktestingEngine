#pragma once

#include "Broker.hpp"
#include "Stats.hpp"

class Strategy
{
public:

  virtual void Next() = 0;
  virtual void Initialize() = 0;

  void Buy(Size size);
  void Sell(Size size);
  void ClosePosition();
  void ReducePosition(Size size);

  const Cash GetRemainingCash() const { return broker_->GetRemainingCash(); }
  const Size GetPosition() const { return broker_->GetPosition(); }
  const Equity& GetEquity() const { return broker_->GetEquity(); }
  const Orders& GetOrders() const { return broker_->GetOrders(); }
  const Trades& GetTrades() const { return broker_->GetTrades(); }
  const Trades& GetClosedTrades() const { return broker_->GetClosedTrades(); }

  void SetBroker(BrokerPointer broker) { broker_ = broker; }
  void SetData(DataObject data) { data_ = data; }
  Stats ComputeStatistics();

  ~Strategy() = default;

private:

  BrokerPointer broker_;
  DataObject data_;
};

using StrategyPointer = std::unique_ptr<Strategy>;