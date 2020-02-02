#pragma once

#include <array>
#include <memory>
#include <tuple>
#include <vector>

#include "utility.h"

namespace rot
{

class RotationOptimizer
{

public:
  RotationOptimizer(const std::vector<float>& src,
                    const std::vector<float>& dst);

  RotQuat GetQuat() const { return R_; }

  std::tuple<float, RotQuat> Optimize(size_t N);

  float Error() const;

  RotQuat InitialGuess();

private:
  std::vector<float> src_;
  std::vector<float> dst_;

  RotQuat R_;
};
} // namespace rot
