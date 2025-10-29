#include "DemoStrategy.hpp"

DemoStrategy::DemoStrategy(const Data& data_)
  : Strategy(data_)
{ }

void DemoStrategy::Next() const
{
  std::cout << "Next" << std::endl;
}

void DemoStrategy::Initialize() const
{
  std::cout << "Initialize" << std::endl;
}