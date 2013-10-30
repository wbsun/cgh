#ifndef CGH_PRIMES_H
#define CGH_PRIMES_H

#include <string>
#include <vector>

class Primes {
 public:
  Primes(int upper_bound, std::string filename);
  ~Primes() { }

  int GetPrime(int which) const { return primes_[which]; }
  int num_primes() const { return primes_.size(); }
  int upper_bound() const { return upper_bound_; }
  
 private:
  int upper_bound_;
  std::vector<int> primes_;
};

#endif
