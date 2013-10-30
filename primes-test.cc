#include "primes.h"

#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " upper-bound primes-filename"
              << std::endl;
    return 0;
  }
  int upper = atoi(argv[1]);
  std::string filename = argv[2];
  
  Primes p(upper, filename);

  std::cout << "Totally " << p.num_primes() << " primes:\n";
  for (int i = 0; i < p.num_primes(); ++i) {
    std::cout << p.GetPrime(i) << "\n";
  }
  
  return 0;
}
