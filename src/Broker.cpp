#include "Broker.hpp"

Broker::Broker(DataObject data, Cash cash, Cash commission, Margin margin, Cash spread, bool tradeOnClose)
  : data_{ data }
  , initialCash_{ cash }
  , commission_{ commission }
  , margin_{ margin }
  , spread_{ spread }
  , tradeOnClose_{ tradeOnClose }
  , leverage_{ (1/margin) }
{
  equity_.push_back(cash);
}

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

  if (openTrades_.empty())
    return size;

  for (const auto& trade : openTrades_)
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

    Cash currentPrice = currentOLHCVBar.open_;
    Cash adjustedPrice = SpreadFunction(orderSize, currentPrice);

    if (((GetPosition() >= 0) && (orderSize > 0)) || ((GetPosition() <= 0) && (orderSize < 0)))
    {
      if (CanAffordTrade(orderSize, adjustedPrice))
        OpenTrade(adjustedPrice, orderSize, currentOLHCVBar.timestamp_);
    }
    else
    {
      MatchOrders(orderSize, adjustedPrice, currentOLHCVBar.timestamp_);
    }

    UpdateRemainingCash();
    it = orders_.erase(it);
  }
}

void Broker::MatchOrders(Size orderSize, Price price, Time timestamp)
{
  Size remainingSize = FillTrades(orderSize, price, timestamp);
  if (std::abs(remainingSize))
    OpenTrade(price, remainingSize, timestamp);

}

Size Broker::FillTrades(Size orderSize, Price price, Time timestamp)
{
  for (auto it = openTrades_.begin(); it != openTrades_.end(); )
  {
    TradePointer currentTrade = *it;
    if (std::abs(orderSize) >= std::abs(currentTrade->GetSize()))
    {
      closedTrades_.push_back(std::make_shared<Trade>(currentTrade->FillTrade(price, timestamp)));

      if (orderSize > 0)
        orderSize -= std::abs(currentTrade->GetSize());
      else
        orderSize += std::abs(currentTrade->GetSize());

      it = openTrades_.erase(it);
    }
    else
    {
      closedTrades_.push_back(std::make_shared<Trade>(currentTrade->PartiallyFillTrade(orderSize, price, timestamp)));
      return 0;
    }
  }
  return orderSize;
}

void Broker::OpenTrade(Price price, Size size, Time timestamp)
{
  openTrades_.push_back(std::make_shared<Trade>(size, price, timestamp));
  UpdateRemainingCash();
}

Cash Broker::CommissionFunction(Size size, Price price)
{
  return commission_ + abs(size) * price;
}

Cash Broker::SpreadFunction(Size size, Price price)
{
  return price * (1.0 + std::copysign(spread_, size));
}

Cash Broker::GetCurrentEquity(Price price)
{
  Cash cash = remainingCash_;

  if (!openTrades_.empty())
    for (const auto& trade : openTrades_)
      cash += trade->GetUnrealizedPnL(price);

  return cash;
}

Price Broker::AdjustedPrice(OptSize size, OptPrice price)
{
  return 0;
}

void Broker::UpdateRemainingCash()
{
  remainingCash_ = initialCash_;
  for (const auto& trade : openTrades_)
    remainingCash_ -= GetTradeCost(trade->GetSize(), trade->GetEntryPrice());
  for (const auto& trade : closedTrades_)
    remainingCash_ += trade->GetRealizedPnL();
}