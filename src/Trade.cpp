#include "Trade.hpp"

#include <memory>

Trade::Trade(Size size, Price entryPrice, Time entryTime, Price exitPrice, Time exitTime)
  : size_{ size }
  , entryPrice_{ entryPrice }
  , entryTime_{ entryTime }
  , exitPrice_{ exitPrice }
  , exitTime_{ exitTime }
{ }

Trade Trade::FillTrade(Price currentPrice, Time currentTime)
{
  exitPrice_ = currentPrice;
  exitTime_ = currentTime;
  return Trade(size_, entryPrice_, entryTime_, exitPrice_, exitTime_);
}

Trade Trade::PartiallyFillTrade(Size size, Price currentPrice, Time currentTime)
{
  if (IsLong())
    size_ -= size;
  else
    size_ += size;

  return Trade(size, entryPrice_, entryTime_, currentPrice, currentTime);
}