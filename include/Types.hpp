#pragma once

#include <iostream>
#include <vector>
#include <chrono>

using Time = std::chrono::system_clock::time_point;
using Price = std::float_t;
using Return = std::float_t;
using Quantity = std::uint16_t;
using Volume = std::uint16_t;

using Size = std::int16_t;
using Cash = std::double_t;
using Margin = std::float_t;
using Leverage = std::float_t;

using OptSize = std::optional<Size>;
using OptPrice = std::optional<Price>;
using OptTime = std::optional<Time>;

using Equity = std::vector<Cash>;