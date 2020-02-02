#include <dataloader.h>
#include <optimizer.h>
#include <utility.h>

#include <iostream>

int main(int argc, char** argv)
{
  rot::DataLoader srcDataLoader("../data/src.csv");
  rot::DataLoader dstDataLoader("../data/dst.csv");

  rot::RotationOptimizer rotOpt(srcDataLoader.points(), dstDataLoader.points());
  rot::print(srcDataLoader.points());

  const auto rotQuat = rotOpt.InitialGuess();
  rotOpt.Error();

  return 0;
}
