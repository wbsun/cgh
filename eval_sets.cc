#include "prime_set.h"
#include "hashset.h"
#include "treeset.h"
#include "array_set.h"
#include "utils.h"
#include "benchmark.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void DoSize(std::string title, const SetDataSuite& set_data) {
  cout << title;
  cout.flush();
  vector<PrimeSet*> sets;
  for (int i = 0; i < set_data.num_sets(); ++i) {
    sets.push_back(new PrimeSet(set_data.GetSetData(i)));
  }

  size_t avg_size = 0;
  for (auto s : sets) {
    avg_size += s->num_bits();
  }
  cout << " " << avg_size / sets.size() << endl;
}

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

  bool do_size = false;
  if (argc == 10)
    do_size = true;

  if (latex_output && !do_size)
    cout << "\\multirow{4}{*}{" << double(set_size)/(double)primes_range << "}  ";

  Primes primes(10000000, filename);
  SetDataSuite data_suite(num_sets, set_size, primes_range, primes);
  if (!latex_output && !do_size) {
    cout << "Generating all set data ... "; cout.flush();
  }
  data_suite.CreateAllSetData();

  if (do_size) {
    cout << primes_range << " " << double(set_size)/(double)primes_range;
    cout.flush();
    DoSize("  ", data_suite);
    return 0;
  }
  
  if (!latex_output)
    cout << "Done\n" << endl;

  DoBenchmark<PrimeSet>("godel hash", data_suite, contains_true_ratio,
                        includes_true_ratio, equals_true_ratio,
                        latex_output);

  if (!latex_output)
    cout << endl;

  DoBenchmark<TreeSet>("sorted treeset", data_suite, contains_true_ratio,
                       includes_true_ratio, equals_true_ratio,
                       latex_output);

  if (!latex_output)
    cout << endl;

  DoBenchmark<ArraySet>("sorted arrayset", data_suite, contains_true_ratio,
                       includes_true_ratio, equals_true_ratio,
                       latex_output);

  if (!latex_output)
    cout << endl;

  DoBenchmark<HashSet>("hashset", data_suite, contains_true_ratio,
                        includes_true_ratio, equals_true_ratio,
                        latex_output);

  if (latex_output)
    cout << "\\hline" << endl;

  return 0;
}
