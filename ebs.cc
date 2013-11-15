#include "prime_set.h"
#include "hashset.h"
#include "treeset.h"
#include "array_set.h"
#include "bitset.h"
#include "utils.h"
#include "benchmark.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {  
  if (argc != 8 && argc != 9 && argc != 10) {
    cout << "Usage: " << argv[0] << " primes-file "
         << "num-sets set-size primes-range contains-true-ratio "
         << "includes-true-ratio equals-true-ratio [latex-output]"
         << " [test-size] "
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
  bool latex_output = true;
  if (argc == 9)
    latex_output = (atoi(argv[8]) != 0);

  if (latex_output && !do_size)
    cout << "\\multirow{4}{*}{" << double(set_size)/(double)primes_range
         << "}  ";

  Primes primes(10000000, filename);
  SetDataSuite data_suite(num_sets, set_size, primes_range, primes);
  if (!latex_output && !do_size) {
    cout << "\nGenerating all set data ... "; cout.flush();
  }
  data_suite.CreateAllSetData();
  
  if (!latex_output)
    cout << "Done\n" << endl;

  DoBenchmark<PrimeSet>("godel hash", data_suite, contains_true_ratio,
                        includes_true_ratio, equals_true_ratio,
                        latex_output);

  if (!latex_output)
    cout << endl;

  switch (primes_range) {
    case 100:
      DoBenchmark<BitSet<542> >("bitset",
                                data_suite, contains_true_ratio,
                                includes_true_ratio, equals_true_ratio,
                                latex_output);
      break;
    case 1000:
      DoBenchmark<BitSet<7920> >("bitset",
                                 data_suite, contains_true_ratio,
                                 includes_true_ratio, equals_true_ratio,
                                 latex_output);
      break;
    case 10000:
      DoBenchmark<BitSet<104730> >("bitset",
                                   data_suite, contains_true_ratio,
                                   includes_true_ratio, equals_true_ratio,
                                   latex_output);
      break;
    case 100000:
      DoBenchmark<BitSet<1299710> >("bitset",
                                    data_suite, contains_true_ratio,
                                    includes_true_ratio, equals_true_ratio,
                                    latex_output);
      break;
    default:
      cout << "Invalide range!" << endl;
      break;
  }

  if (latex_output)
    cout << "\\hline" << endl;

  return 0;
}
