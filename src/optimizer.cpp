
#include <Eigen/Core>

#include <optimizer.h>

namespace rot
{

RotationOptimizer::RotationOptimizer(const std::vector<float>& src,
                                     const std::vector<float>& dst)
  : src_(src), dst_(dst)
{
}

RotQuat RotationOptimizer::InitialGuess()
{
  return R_;
}

std::tuple<float, RotQuat> RotationOptimizer::Optimize(size_t N)
{
  return {};
}

} // namespace rot
