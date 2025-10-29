#pragma once

#include <iostream>
#include <vector>
#include <vector>
#include <chrono>

using Time = std::chrono::system_clock::time_point;
using Price = std::double_t;
using Quantity = std::uint16_t;
using Volume = std::uint16_t;

using Size = std::double_t;
using Cash = std::double_t;
using Margin = std::double_t;
using Leverage = std::double_t;

using OptSize = std::optional<Size>;
using OptPrice = std::optional<Price>;

using Equity = std::vector<Cash>;