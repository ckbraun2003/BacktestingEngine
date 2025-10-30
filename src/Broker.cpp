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

void Broker::Next(const OLHCVBar& currentOLHCVBar))
{

}

void Broker::NewOrder(Size size)
{
  if (size != 0)
  {
    orders_.push_back(std::make_shared<Order>(size));
  }
}

void Broker::ProcessOrders()
{
  for (size_t i = 0; i < orders_.size(); )
  {
    OrderPointer order = orders_.back();
  }
}

void Broker::CloseTrade(Trade trade, Price price, Time timestamp)
{

}

void Broker::OpenTrade(Price price, Size size, Time timestamp)
{

}

Cash Broker::CommissionFunction(Size size, Price price)
{
  return 0;
}

Cash Broker::GetCurrentEquity()
{
  Cash totalPnL = std::accumulate(
    trades_.begin(), trades_.end(), 0.0,
    [](Cash sum, const TradePointer trade) {
      return sum;
    }
  );
  return 0;
}

Price Broker::AdjustedPrice(OptSize size, OptPrice price)
{
  return 0;
}
