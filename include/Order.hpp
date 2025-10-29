#pragma once

#include <vector>

#include "Broker.hpp"

class Order
{
public:
  Order(BrokerPointer broker_, Size size_);

  void Cancel();

  Size GetSize() const { return size_; };
  bool IsLong() const { return size_ > 0; }
  bool IsShort() const { return size_ < 0; }

private:
  BrokerPointer broker_;
  Size size_;
};

using Orders = std::vector<Order>;