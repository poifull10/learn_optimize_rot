#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace rot
{

using RotQuat = std::array<float, 4>;

std::vector<float> rotate(const std::vector<float>& src, RotQuat rot);
void print(const std::vector<float> src);
} // namespace rot
