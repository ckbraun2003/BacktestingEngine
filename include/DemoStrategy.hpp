#pragma once

#include "Strategy.hpp"

class DemoStrategy : public Strategy
{
public:
  DemoStrategy(const Data& data_);
  void Next() const override;
  void Initialize() const override;
};