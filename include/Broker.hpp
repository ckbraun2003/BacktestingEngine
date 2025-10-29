#include <optional>
#include <iostream>

#include "DataObject.hpp"
#include "Position.hpp"
#include "Trade.hpp"
#include "Order.hpp"

class Broker
{
public:
  Broker(DataObject data_, Cash cash_, Cash commision_, Margin margin_, Cash spread_, bool tradeOnClose_ = false);

  void Next();
  void NewOrder(Size size_);

  Price LastPrice();
  const Equity& GetEquity() const { return equity_; }
  const Position& GetPosition() const { return position_; }
  const Orders& GetOrders() const { return orders_; }
  const Trades& GetTrades() const { return trades_; }
  const Trades& GetClosedTrades() const { return closedTrades_; }


private:


  DataObject data_;
  Cash cash_;
  Cash commision_;
  Cash spread_;
  Margin margin_;
  Leverage leverage_;
  bool tradeOnClose_;

  Position position_;
  Equity equity_;
  Orders orders_;
  Trades trades_;
  Trades closedTrades_;

  void ProcessOrders();
  void CloseTrade(Trade trade_, Price price_, Time timestamp_);
  void OpenTrade(Price price_, Size size_, Time timestamp_);

  Cash ComissionFunction(Size size_, Price price);
  Cash GetCurrentEquity();
  Price AdjustedPrice(OptSize size_ = std::nullopt, OptPrice price_ = std::nullopt);

};

using BrokerPointer = std::shared_ptr<Broker>;