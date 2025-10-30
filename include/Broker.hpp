#pragma once

#include <optional>
#include <iostream>
#include <unordered_map>

#include "DataObject.hpp"
#include "Trade.hpp"
#include "Order.hpp"
#include "Types.hpp"

class Broker
{
public:
  Broker(DataObject data, Cash cash, Cash commission, Margin margin, Cash spread, bool tradeOnClose = false);

  void Next(const OLHCVBar& currentOLHCVBar);
  void NewOrder(Size size);
  Size GetPosition() const;

  Cash GetCash() const { return cash_; }
  Price LastPrice() const;
  bool IsLong() const { return GetPosition() > 0; }
  bool IsShort() const { return GetPosition() < 0; }
  const Equity& GetEquity() const { return equity_; }
  const Orders& GetOrders() const { return orders_; }
  const Trades& GetTrades() const { return trades_; }
  const Trades& GetClosedTrades() const { return closedTrades_; }


private:


  DataObject data_;
  Cash cash_;
  Cash commission_;
  Cash spread_;
  Margin margin_;
  Leverage leverage_;
  bool tradeOnClose_;

  Equity equity_;
  Orders orders_;
  Trades trades_;
  Trades closedTrades_;

  void ProcessOrders(const OLHCVBar& currentOLHCVBar);
  void MatchOrders(Size orderSize, Price price, Time timestamp);
  void OpenTrade(Price price, Size size, Time timestamp);

  Cash CommissionFunction(Size size, Price price);
  Cash GetCurrentEquity(Price price);
  Price AdjustedPrice(OptSize size = std::nullopt, OptPrice price = std::nullopt);

};

using BrokerPointer = std::shared_ptr<Broker>;