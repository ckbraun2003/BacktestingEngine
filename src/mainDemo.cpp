#include <iostream>
#include <chrono>
#include <thread>

#include "Backtest.hpp"
#include "DemoStrategy.hpp"


int main()
{
	DataObject data_;

	for (int i = 0; i < 10; ++i)
	{
		data_.push_back(OLHCVBar(std::chrono::system_clock::now(), 100+i, 100, 100, 100, 100));
	}

	Backtest backtest_(data_, std::make_unique<DemoStrategy>(), 10000, 0.0, 0.0, 0.0, false);
	backtest_.RunBacktest();
	return 0;
}
