#include "benchmark.h"
#include "utils.h"
#include <vector>

using namespace std;

SetDataSuite::SetDataSuite(int num_sets, int size, int range, const Primes& primes)
    : num_sets_(num_sets), size_(size), range_(range), primes_(primes) {}

SetDataSuite::~SetDataSuite() { }

void SetDataSuite::CreateAllSetData() {
  vector<int> indecies;
  for (int i = 0; i < num_sets_; ++i) {
    set_data_.push_back(SetData());
    SetData& d = set_data_.back();
    utils::RandomIndecies(0, range_-1, &indecies);
    for (int j = 0; j < size_; ++j) {
      int idx = indecies[j];
      d.data.push_back(primes_.GetPrime(idx));
    }
    d.for_insert = primes_.GetPrime(indecies[size_]);
    d.for_remove = primes_.GetPrime(indecies[0]);
    d.for_contains_in = primes_.GetPrime(indecies[1]);
    d.for_contains_not_in = primes_.GetPrime(indecies[size_+1]);
  }
}
