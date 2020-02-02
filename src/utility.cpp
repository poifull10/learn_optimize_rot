#include <utility.h>
#include <fstream>

namespace rot
{
void print(const std::vector<float> src)
{
  size_t N = src.size() / 3;
  for (size_t i = 0; i < N; i++)
  {
    std::cout << "[" << i << "] " << src[i] << ", " << src[i + 1] << ", "
              << src[i + 2] << std::endl;
  }
}

void write(const std::string& path, const RotQuat& rotQuat)
{
  std::ofstream ofs(path);

  ofs << rotQuat[0] << " " << rotQuat[1] << " " << rotQuat[2] << " "
      << rotQuat[3];
}
} // namespace rot