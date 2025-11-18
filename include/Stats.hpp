#pragma once

#include "Types.hpp"

struct Stats
{
public:
  Time startTime_;
  Time endTime_;
  double duration_;

  Cash equityInitial_;
  Cash equityFinal_;
  Cash equityPeak_;
  Cash maximumDrawdown_;

  Return finalReturn_;
  Return annualizedReturn_;

  float sharpeRatio_;
  float sortinoRatio_;

  Quantity numberOfTrades_;

};