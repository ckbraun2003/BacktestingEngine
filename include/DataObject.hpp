#pragma once

#include <list>

#include "Types.hpp"

struct OLHCVBar
{
public:
  Time timestamp_;
  Price close_;
  Price open_;
  Price high_;
  Price low_;
  Volume volume_;
};

struct DataObject
{
public:
  std::vector<OLHCVBar> olhcv_data_;
};
