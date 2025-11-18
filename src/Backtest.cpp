#include "Backtest.hpp"

Backtest::Backtest(DataObject data, StrategyPointer strategy, Cash cash, Cash commission, Margin margin, Cash spread, Return riskFreeRate, bool tradeOnClose)
  : riskFreeRate_{ riskFreeRate }
  , data_{ data }
  , broker_(std::make_shared<Broker>(data_, cash, commission, margin, spread, tradeOnClose))
  , strategy_(std::move(strategy))
{
  strategy_->SetBroker(broker_);
  strategy_->SetData(data_);
}

void Backtest::RunBacktest()
{
  strategy_->Initialize();

  for (int i = 0; i < data_.size(); ++i)
  {
    if (i != 0)
      broker_->Next(data_.at(i));

    strategy_->Next();
  }
  statistics_ = ComputeStatistics(broker_->GetClosedTrades(), broker_->GetEquity(), riskFreeRate_, data_);
}

void Backtest::PrintStatistics()
{
  std::cout << "Start Time        : " << timepointToString(statistics_.startTime_) << '\n';
  std::cout << "End Time          : " << timepointToString(statistics_.endTime_) << '\n';
  std::cout << "Duration (days)   : " << std::fixed << std::setprecision(2) << statistics_.duration_ << '\n';

  std::cout << "Equity Initial    : " << std::fixed << std::setprecision(2) << statistics_.equityInitial_ << '\n';
  std::cout << "Equity Final      : " << std::fixed << std::setprecision(2) << statistics_.equityFinal_ << '\n';
  std::cout << "Equity Peak       : " << statistics_.equityPeak_ << '\n';

  std::cout << "Final Return      : " << statistics_.finalReturn_ * 100.0 << " %\n";
  std::cout << "Annualized Return : " << statistics_.annualizedReturn_ * 100.0 << " %\n";

  std::cout << "Sharpe Ratio      : " << statistics_.sharpeRatio_ << '\n';
  std::cout << "Sortino Ratio     : " << statistics_.sortinoRatio_ << '\n';

  std::cout << "Number of Trades  : " << statistics_.numberOfTrades_ << '\n';
}

Stats Backtest::ComputeStatistics(const Trades& trades, const Equity& equity, const Return riskFreeRate, const DataObject& olhcvBars)
{
  Stats statistics;

  statistics.startTime_ = olhcvBars.front().timestamp_;
  statistics.endTime_ = olhcvBars.back().timestamp_;
  statistics.duration_ = std::chrono::duration_cast<std::chrono::hours>((statistics.endTime_ - statistics.startTime_)).count() / 24.0;

  statistics.equityInitial_ = equity.front();
  statistics.equityFinal_ = equity.back();
  statistics.equityPeak_ = *std::max_element(equity.begin(), equity.end());

  statistics.finalReturn_ = (statistics.equityFinal_ - statistics.equityInitial_) / statistics.equityInitial_;
  statistics.annualizedReturn_ = std::pow(1.0 + statistics.finalReturn_, 252.0 / statistics.duration_) - 1.0;

  statistics.sharpeRatio_;
  statistics.sortinoRatio_;

  statistics.numberOfTrades_ = trades.size();

  return statistics;

}

std::string Backtest::timepointToString(Time timepoint)
{
    std::time_t time = std::chrono::system_clock::to_time_t(timepoint);
    std::tm* tm = std::localtime(&time);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
    return std::string(buffer);
}