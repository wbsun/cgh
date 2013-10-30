#include "prime_set.h"
#include "utils.h"
#include "primes.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

static int NUM_TESTS = 1000;

void GeneratePrimeSet(const Primes& primes, int size, int range,
                      vector<int>* indecies, PrimeSet* ps) {
  utils::RandomIndecies(0, range-1, indecies);
  for (int i = 0; i < size; ++i) {
    int idx = indecies->at(i);
    ps->Insert( primes.GetPrime(idx));
  }
}

int main(int argc, char* argv[]) {
  int upper_bound = atoi(argv[1]);
  string filename = argv[2];
  int size = atoi(argv[3]);
  int range = atoi(argv[4]);

  Primes primes(upper_bound, filename);
  unique_ptr<PrimeSet[]> pss(new PrimeSet[NUM_TESTS]);
  vector<int> indecies;
  cout << "Generating sets: ";
  cout.flush();
  for (int i = 0; i < NUM_TESTS; ++i) {
    GeneratePrimeSet(primes, size, range, &indecies, &pss[i]);
    if (i % 10 == 0) {
      cout << ".";
      cout.flush();
    }
  }
  
  cout << " Done\nRun contains ...";
  cout.flush();
  utils::Timing tm;
  tm.Start();
  bool r = false;
  int p = primes.GetPrime(range/2);
  for (int i = 0; i < NUM_TESTS; ++i) {
    r = r || pss[i].Contains(p);
  }
  tm.Stop();
  cout << " Contains: " << tm.ElapsedTime() << " us" << endl;

  cout << "Run inclusion ...";
  cout.flush();
  tm.Start();
  r = false;
  for (int i = 0; i < NUM_TESTS; ++i) {
    r = r || pss[i].Includes(pss[NUM_TESTS-i-1]);
  }
  tm.Stop();
  cout << " Inclusion: " << tm.ElapsedTime() << " us" << endl;

  cout << "Run equals ...";
  cout.flush();
  tm.Start();
  r = false;
  for (int i = 0; i < NUM_TESTS; ++i) {
    r = r || pss[i].Equals(pss[NUM_TESTS-i-1]);
  }
  tm.Stop();
  cout << " Equals: " << tm.ElapsedTime() << " us" << endl;

  return 0;
}
