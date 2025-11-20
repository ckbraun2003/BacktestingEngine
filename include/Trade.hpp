#pragma once

#include <vector>
#include <memory>

#include "Types.hpp"

class Trade
{
public:
  Trade(Size size, Price entryPrice, Time entryTime, Price exitPrice = 0.0, Time exitTime = std::chrono::system_clock::now());

  Size GetSize() const { return size_; }
  Cash GetTradeCost() const { return std::abs(size_ * entryPrice_); }
  Price GetEntryPrice() const { return entryPrice_; }
  Price GetExitPrice() const { return exitPrice_; }
  Time GetEntryTime() const { return entryTime_; }
  Time GetExitTime() const { return exitTime_; }
  Cash GetRealizedPnL() const { return size_ * (exitPrice_ - entryPrice_); }
  Cash GetUnrealizedPnL(Price currentPrice) const { return size_ * (currentPrice - entryPrice_); }
  Cash GetCurrentValue(Price currentPrice) const { return GetUnrealizedPnL(currentPrice) + GetEntryPrice(); }

  bool IsLong() const { return size_ > 0; }
  bool IsShort() const { return size_ < 0; }
  Trade FillTrade(Price currentPrice, Time currentTime);
  Trade PartiallyFillTrade(Size size, Price currentPrice, Time currentTime);

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