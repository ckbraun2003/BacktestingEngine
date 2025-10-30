#pragma once

#include <vector>

#include "Types.hpp"

class Trade
{
public:
  Trade(Size size_, Price entryPrice_, Time entryTime);

  Size GetSize() const { return size_; }
  Price GetEntryPrice() const { return entryPrice_; }
  Price GetExitPrice() const { return exitPrice_; }
  Time GetEntryTime() const { return entryTime_; }
  Time GetExitTime() const { return exitTime_; }
  void CloseTrade(BrokerPointer& broker, Size size);

private:
  Size size_;
  Price entryPrice_;
  Price exitPrice_;
  Time entryTime_;
  Time exitTime_;

  Cash commissions = 0.0;
};

using TradePointer = std::shared_ptr<Trade>;
using Trades = std::vector<TradePointer>;