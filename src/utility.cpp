#include <utility.h>

namespace rot
{

std::vector<float> rotate(const std::vector<float>& src, RotQuat rot)
{
  // size_t N = src.size() / 2;
  // std::vector<float> dst(src.size());

  // for (size_t i = 0; i < N; i++)
  // {
  //   float x = src[i];
  //   float y = src[i + 1];
  //   dst[i] = std::cos(rot) * x - std::sin(rot) * y;
  //   dst[i + 1] = std::sin(rot) * x + std::cos(rot) * y;
  // }
  // return dst;
  return {};
}

void print(const std::vector<float> src)
{
  size_t N = src.size() / 3;
  for (size_t i = 0; i < N; i++)
  {
    std::cout << "[" << i << "] " << src[i] << ", " << src[i + 1] << ", "
              << src[i + 2] << std::endl;
  }
}
} // namespace rot