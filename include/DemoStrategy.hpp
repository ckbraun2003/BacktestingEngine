#pragma once

#include "Strategy.hpp"

class DemoStrategy : public Strategy
{
public:
  void Next() override;
  void Initialize() override;
};