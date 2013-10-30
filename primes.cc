#include "primes.h"

#include <cmath>
#include <fstream>

Primes::Primes(int upper_bound, std::string filename) {
  upper_bound_ = upper_bound;
  int probable_size = upper_bound / std::log(upper_bound);
  primes_.reserve(probable_size);

  int prime;
  std::ifstream ifs(filename);
  if (ifs.good()) {
    ifs >> prime;
    while (ifs.good()) {
      primes_.push_back(prime);
      ifs >> prime;
    }
  }  
}
