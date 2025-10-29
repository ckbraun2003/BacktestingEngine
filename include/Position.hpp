#pragma once

#include "Broker.hpp"

class Position
{
public:
  Position(BrokerPointer broker_);

  void Close(Size size_);

  Size GetSize();
  Cash GetPnL();
  

private:
  
};