#pragma once

#include "Broker.hpp"

class Strategy
{
public:
  Strategy(BrokerPointer broker_, DataObject data_);

  virtual void Next() const = 0;
  virtual void Initialize() const = 0;

  void Buy(Size size_);
  void Sell(Size size_);

  const Equity& GetEquity() const { return broker_->GetEquity(); }
  const Position& GetPosition() const { return broker_->GetPosition(); }
  const Orders& GetOrders() const { return broker_->GetOrders(); }
  const Trades& GetTrades() const { return broker_->GetTrades(); }
  const Trades& GetClosedTrades() const { return broker_->GetClosedTrades(); }

  ~Strategy() = default;

private:
  BrokerPointer broker_;
  DataObject data_;
};

using StrategyPointer = std::unique_ptr<Strategy>;