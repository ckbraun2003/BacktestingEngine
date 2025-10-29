#pragma once

#include "Strategy.hpp"
#include "Broker.hpp"

class Backtest
{
public:
  Backtest(std::unique_ptr<Strategy> strategy_, const Bars& bars_);
  void Run() const;

private:
  std::unique_ptr<Strategy> strategy_;
  Bars bars_;
};