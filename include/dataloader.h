#pragma once

#include <string>
#include <vector>

namespace rot
{
class DataLoader
{
public:
  DataLoader(const std::string& path);
  std::vector<float> points() const { return points_; }

private:
  std::vector<float> points_;
};
} // namespace rot
