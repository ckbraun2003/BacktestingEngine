#include <iostream>
#include <chrono>
#include <thread>

#include "Backtest.hpp"
#include "DemoStrategy.hpp"


int main()
{
	DataObject data_;

	for (int i = 0; i < 11; ++i)
	{
		data_.push_back(OLHCVBar(std::chrono::system_clock::now(), 100+i, 101+i, 100, 100, 100));
	}

	Backtest backtest_(data_, std::make_unique<DemoStrategy>(), 10000, 0.0, 0.0, 0.1, 0.0, false);

	backtest_.RunBacktest();
	backtest_.PrintStatistics();
	return 0;
}
