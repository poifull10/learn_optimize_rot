#include <gtest/gtest.h>

#include <dataloader.h>
#include <optimizer.h>
#include <utility.h>

TEST(RotationOptimizer, test_initial_guess)
{
  rot::DataLoader srcDataLoader("../data/src.csv");
  rot::DataLoader dstDataLoader("../data/dst.csv");
  rot::DataLoader ansDataLoader("../data/answer.csv");

  rot::RotationOptimizer rotOpt(srcDataLoader.points(), dstDataLoader.points());

  const auto rotQuat = rotOpt.InitialGuess();

  for (size_t i = 0; i < 4; i++)
  {
    EXPECT_NEAR(ansDataLoader.points()[i], rotQuat[i], 1e-6);
  }
}