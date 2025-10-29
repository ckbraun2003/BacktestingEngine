#pragma once

#include <vector>

#include "Broker.hpp"

class Trade
{
public:
  Trade(BrokerPointer broker_, Size size_, Price entryPrice_, Time entryTime);

private:
  BrokerPointer broker_;
  Size size_;
  Price entryPrice_;
  Price exitPrice_;
  Time entryTime_;
  Time exitTime_;

  Cash commissions = 0;
};

using Trades = std::vector<Trade>;