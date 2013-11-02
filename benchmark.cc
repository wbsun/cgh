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
      d.data.push_back(utils::Element(primes_.GetPrime(idx), j));
    }
    d.for_insert = utils::Element(primes_.GetPrime(indecies[size_+1]), size_+1);
    d.for_remove = utils::Element(primes_.GetPrime(indecies[size_/5]), size_/m4);
    d.for_contains_in = utils::Element(primes_.GetPrime(indecies[size_/4]), size_/3);
    d.for_contains_not_in = utils::Element(primes_.GetPrime(indecies[size_+2]), size_+2);
  }
}
