#include <dataloader.h>

#include <iostream>

int main(int argc, char** argv)
{
  rot::DataLoader srcDataLoader("../data/src.csv");
  const auto vec = srcDataLoader.points();
  for (const auto& v : vec)
  {
    std::cout << v << std::endl;
  }
  return 0;
}
