#pragma once

#include <cmath>
#include <numeric>
#include <vector>

class PerlinNoise {
  public:
    PerlinNoise(unsigned int seed);

    double noise(double x, double y, double z) const;

  private:
    std::vector<int> p;  // Permutation vector

    double fade(double t) const;
    double lerp(double t, double a, double b) const;
    double grad(int hash, double x, double y, double z) const;
};
