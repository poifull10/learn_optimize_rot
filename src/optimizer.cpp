
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <optimizer.h>

#include <iostream>

namespace rot
{

static Eigen::MatrixXd StdVecToMat(const std::vector<float>& vec)
{
  Eigen::MatrixXd mat(3, vec.size() / 3);
  for (size_t ic = 0; ic < vec.size() / 3; ic++)
  {
    mat(0, ic) = vec[ic * 3];
    mat(1, ic) = vec[ic * 3 + 1];
    mat(2, ic) = vec[ic * 3 + 2];
  }

  return mat;
}

RotationOptimizer::RotationOptimizer(const std::vector<float>& src,
                                     const std::vector<float>& dst)
  : src_(src), dst_(dst)
{
}

RotQuat RotationOptimizer::InitialGuess()
{
  Eigen::MatrixXd src_mat = StdVecToMat(src_);
  Eigen::MatrixXd dst_mat = StdVecToMat(dst_);
  Eigen::Matrix4d R4 = Eigen::umeyama(src_mat, dst_mat);
  Eigen::Matrix3d R3 = R4.block(0, 0, 3, 3);
  Eigen::Quaterniond R_quat(R3);

  R_ = {static_cast<float>(R_quat.x()), static_cast<float>(R_quat.y()),
        static_cast<float>(R_quat.z()), static_cast<float>(R_quat.w())};
  return R_;
}

std::tuple<float, RotQuat> RotationOptimizer::Optimize(size_t N)
{
  return {};
}

} // namespace rot
