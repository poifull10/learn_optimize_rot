
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <optimizer.h>

#include <iostream>
#include <numeric>

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

static RotQuat MatToQuat(const Eigen::Matrix3d& R)
{
  Eigen::Quaterniond q(R);
  return {static_cast<float>(q.x()), static_cast<float>(q.y()),
          static_cast<float>(q.z()), static_cast<float>(q.w())};
}

static Eigen::Matrix3d RToRotMat(const RotQuat& quat)
{
  Eigen::Quaterniond quat_(quat[3], quat[0], quat[1], quat[2]);
  return Eigen::Matrix3d(quat_);
}

static Eigen::Matrix3d toCross(const Eigen::Vector3d& omega)
{
  Eigen::Matrix3d Omega = Eigen::Matrix3d::Zero();
  Omega(0, 1) = -omega(2);
  Omega(1, 0) = omega(2);
  Omega(0, 2) = omega(1);
  Omega(2, 0) = -omega(1);
  Omega(1, 2) = -omega(0);
  Omega(2, 1) = omega(0);
  return Omega;
}

static Eigen::Matrix3d expMap(const Eigen::Vector3d& omega)
{
  Eigen::Matrix3d Omega = toCross(omega);
  Omega = Omega / omega.norm();

  Eigen::Matrix3d ret = Eigen::Matrix3d::Identity();
  ret += Omega * std::sin(omega.norm()) +
         Omega * Omega * (1 - std::cos(omega.norm()));
  return ret;
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
  R_ = MatToQuat(R3);
  return GetQuat();
}

float RotationOptimizer::Error() const
{
  Eigen::Matrix3d rot = RToRotMat(GetQuat());

  Eigen::MatrixXd src_mat = rot * StdVecToMat(src_);
  Eigen::MatrixXd dst_mat = StdVecToMat(dst_);

  float error = 0;
  for (size_t i = 0; i < src_mat.cols(); i++)
  {
    error += (src_mat.col(i) - dst_mat.col(i)).norm();
  }

  return error;
}

std::tuple<float, RotQuat> RotationOptimizer::Optimize(size_t N)
{
  Eigen::Matrix3d W = 0.5 * Eigen::Matrix3d::Identity();
  Eigen::Matrix3d V = 2 * Eigen::Matrix3d::Identity();
  Eigen::MatrixXd src_mat = StdVecToMat(src_);
  Eigen::MatrixXd dst_mat = StdVecToMat(dst_);
  size_t iter = 0;
  float lambda = 1e-3;
  float preLoss = Error();
  RotQuat rqt = GetQuat();
  Eigen::Matrix3d R_fixed = RToRotMat(GetQuat());

  std::cout << "[InitialGuess] : loss = " << preLoss << ", lambda = " << lambda
            << std::endl;
  while (iter < N)
  {
    Eigen::Vector3d g = Eigen::Vector3d::Zero();
    Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
    Eigen::Matrix3d R = R_fixed;

    for (size_t j = 0; j < src_mat.cols(); j++)
    {
      g +=
        (R * src_mat.col(j)).cross(W * (dst_mat.col(j) - R * src_mat.col(j))) -
        (W * (dst_mat.col(j) - R * src_mat.col(j)))
          .cross(R * V * R.transpose() * W *
                 (dst_mat.col(j) - R * src_mat.col(j)));
      H += toCross(R * src_mat.col(j)) * W * toCross(R * src_mat.col(j));
    }
    g *= -1;

    Eigen::Vector3d omega =
      -1.0 * (H + lambda * Eigen::Matrix3d::Identity()).inverse() * g;
    Eigen::Matrix3d dR = expMap(omega);
    R = dR * R;
    R_ = MatToQuat(R);
    float loss = Error();
    std::cout << "[Iter: " << iter << "] : loss = " << loss
              << ", lambda = " << lambda << std::endl;
    if (loss <= preLoss)
    {
      preLoss = loss;
      R_fixed = R;
      rqt = MatToQuat(R);
      lambda *= 0.1;
      rqt = GetQuat();
      iter++;
      std::cout << "[Quat] : " << rqt[3] << ", " << rqt[0] << ", " << rqt[1]
                << ", " << rqt[2] << std::endl;
    }
    else
    {
      lambda *= 10;
      R_ = rqt;
    }
  }

  return {preLoss, GetQuat()};
}

} // namespace rot
