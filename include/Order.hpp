#pragma once

#include <vector>

#include "Types.hpp"

class Order
{
public:
  Order(Size size);

  void Cancel();

  Size GetSize() const { return size_; };
  bool IsLong() const { return size_ > 0; }
  bool IsShort() const { return size_ < 0; }

private:
  Size size_;
};

using OrderPointer = std::shared_ptr<Order>;
using Orders = std::vector<OrderPointer>;