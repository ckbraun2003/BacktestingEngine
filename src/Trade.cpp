#include "Trade.hpp"

Trade::Trade(Size size, Price entryPrice, Time entryTime)
  : size_{ size }
  , entryPrice_{ entryPrice }
  , entryTime_{ entryTime }
{ }