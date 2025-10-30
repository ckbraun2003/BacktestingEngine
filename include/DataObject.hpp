#pragma once

#include <vector>

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

using DataObject = std::vector<OLHCVBar>;
