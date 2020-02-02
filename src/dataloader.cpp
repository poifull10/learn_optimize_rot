#include <dataloader.h>

#include <fstream>
#include <sstream>

namespace rot
{
DataLoader::DataLoader(const std::string& path)
{
  std::ifstream indata;

  indata.open(path);

  std::string line;
  while (getline(indata, line))
  {
    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ' '))
    {
      points_.push_back(std::stof(cell));
    }
  }
}
} // namespace rot
