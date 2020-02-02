#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace rot
{

using RotQuat = std::array<float, 4>;

void print(const std::vector<float> src);
void write(const std::string& path, const RotQuat& rotQuat);

} // namespace rot
