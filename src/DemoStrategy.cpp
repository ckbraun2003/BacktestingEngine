#include <format>

#include "DemoStrategy.hpp"

void DemoStrategy::Next()
{
  if (GetPosition() == 0)
    Buy(1);

  auto& equity = GetEquity();
  auto currentEquity = GetCash();
  if (!equity.empty())
    currentEquity = equity.back();

  auto position = GetPosition();

  std::cout << std::format("Position: {} | Equity: ${}\n", position, currentEquity);
}

void DemoStrategy::Initialize()
{
}