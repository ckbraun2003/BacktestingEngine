#include <numeric>

#include "Broker.hpp"

Broker::Broker(DataObject data, Cash cash, Cash commission, Margin margin, Cash spread, bool tradeOnClose)
  : data_{ data }
  , cash_{ cash }
  , commission_{ commission }
  , margin_{ margin }
  , spread_{ spread }
  , tradeOnClose_{ tradeOnClose }
  , leverage_{ (1/margin) }
{ }

Price Broker::LastPrice() const
{
  OLHCVBar currentOLHCVBar = data_.back();
  return currentOLHCVBar.close_;
}

void Broker::Next(const OLHCVBar& currentOLHCVBar)
{
  ProcessOrders(currentOLHCVBar);

  equity_.push_back(GetCurrentEquity(currentOLHCVBar.close_));
}

void Broker::NewOrder(Size size)
{
  if (size != 0)
  {
    orders_.push_back(std::make_shared<Order>(size));
  }
}

Size Broker::GetPosition() const
{
  Size size = 0;

  if (trades_.empty())
    return size;

  for (const auto& trade : trades_)
    size += trade->GetSize();

  return size;
}

void Broker::ProcessOrders(const OLHCVBar& currentOLHCVBar)
{
  if (orders_.empty())
    return;

  for (auto it = orders_.begin(); it != orders_.end(); )
  {
    OrderPointer order = *it;
    Size orderSize = order->GetSize();
    if (((GetPosition() >= 0) && (orderSize > 0)) || ((GetPosition() <= 0) && (orderSize < 0)))
    {
      OpenTrade(currentOLHCVBar.open_, orderSize, currentOLHCVBar.timestamp_);
    }
    else
    {
      MatchOrders(orderSize, currentOLHCVBar.open_, currentOLHCVBar.timestamp_);
    }
    it = orders_.erase(it);
  }
}

void Broker::MatchOrders(Size orderSize, Price price, Time timestamp)
{
  while (orderSize != 0)
    for (auto it = trades_.begin(); it != trades_.end(); )
    {
      TradePointer currentTrade = *it;
      Size tradeSize = std::abs(currentTrade->GetSize());

      if (tradeSize <= std::abs(orderSize))
      {
        closedTrades_.push_back(std::make_shared<Trade>(currentTrade->FillTrade(price, timestamp)));
        orderSize += currentTrade->GetSize();
        it = trades_.erase(it);
      }
      else
      {
        closedTrades_.push_back(std::make_shared<Trade>(currentTrade->PartiallyFillTrade(orderSize, price, timestamp)));
        orderSize = 0;
        ++it;
      }
    }
}

void Broker::OpenTrade(Price price, Size size, Time timestamp)
{
  trades_.push_back(std::make_shared<Trade>(size, price, timestamp));
}

Cash Broker::CommissionFunction(Size size, Price price)
{
  return 0;
}

Cash Broker::GetCurrentEquity(Price price)
{
  Cash cash = cash_;

  if (!trades_.empty())
    for (const auto& trade : trades_)
      cash += trade->GetUnrealizedPnL(price);
  if (!closedTrades_.empty())
    for (const auto& trade : closedTrades_)
      cash += trade->GetRealizedPnL();

  return cash;
}

Price Broker::AdjustedPrice(OptSize size, OptPrice price)
{
  return 0;
}
