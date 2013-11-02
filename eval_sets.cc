#include "prime_set.h"
#include "hashset.h"
#include "utils.h"
#include "benchmark.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 8) {
    cout << "Usage: " << argv[0] << " primes-file "
         << "num-sets set-size primes-range contains-true-ratio "
         << "includes-true-ratio equals-true-ratio"
         << endl;
    return 0;
  }

  string filename = argv[1];
  int num_sets = atoi(argv[2]);
  int set_size = atoi(argv[3]);
  int primes_range = atoi(argv[4]);
  int contains_true_ratio = atoi(argv[5]);
  int includes_true_ratio = atoi(argv[6]);
  int equals_true_ratio = atoi(argv[7]);

  Primes primes(10000000, filename);
  SetDataSuite data_suite(num_sets, set_size, primes_range, primes);
  cout << "Generating all set data ... "; cout.flush();
  data_suite.CreateAllSetData();
  cout << "Done" << endl;

  DoBenchmark<PrimeSet>("PrimeSet", data_suite, contains_true_ratio,
                        includes_true_ratio, equals_true_ratio);

  DoBenchmark<HashSet>("HashSet", data_suite, contains_true_ratio,
                        includes_true_ratio, equals_true_ratio);
  
  return 0;
}
