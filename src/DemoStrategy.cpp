#include <format>

#include "DemoStrategy.hpp"

void DemoStrategy::Next()
{
  Equity equity = GetEquity();
  Cash currentEquity;

  if (!equity.empty())
    currentEquity = equity.back();
  else
    currentEquity = GetRemainingCash();

  Cash cash = GetRemainingCash();
  auto position = GetPosition();

  if (position)
    ClosePosition();
  else
    Buy(1);

  // std::cout << std::format("Position: {} | Remaining Cash: ${} | Equity: ${}\n", position, cash, currentEquity);
}

void DemoStrategy::Initialize()
{
}