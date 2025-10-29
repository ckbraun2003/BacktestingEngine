#include "Strategy.hpp"


void Strategy::Buy(Size size_)
{
  assert(((size_ > 0 && size_ < 1) || (std::round(size_) == size_ && size_ >= 1)));

  return broker_.new_order(size_);
}