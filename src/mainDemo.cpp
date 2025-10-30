#include <iostream>

#include "Backtest.hpp"
#include "DemoStrategy.hpp"

DataObject data_;


Backtest backtest_(data_, std::make_unique<DemoStrategy>(), 0.0, 0.0, 0.0, 0.0, false);

int main()
{
	backtest_.RunBacktest();
	return 0;
}
