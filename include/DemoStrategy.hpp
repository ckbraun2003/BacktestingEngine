#pragma once

#include "Strategy.hpp"

class DemoStrategy : public Strategy
{
public:
  void Next() const override;
  void Initialize() const override;
};