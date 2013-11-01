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
    ps->Insert(primes.GetPrime(idx));
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
  int p = primes.GetPrime(range/2);
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Contains(p);
  }
  tm.Stop();
  cout << " Contains: " << tm.ElapsedTime() << " ns" << endl;

  cout << "Run insert ...";
  cout.flush();
  tm.Start();
  p = primes.GetPrime(range/3);
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Insert(p);
  }
  tm.Stop();
  cout << " Insert: " << tm.ElapsedTime() << " ns" << endl;

  cout << "Run remove ...";
  cout.flush();
  tm.Start();
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Remove(p);
  }
  tm.Stop();
  cout << " Remove: " << tm.ElapsedTime() << " ns" << endl;

  cout << "Run inclusion ...";
  cout.flush();
  tm.Start();
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Includes(pss[NUM_TESTS-i-1]);
  }
  tm.Stop();
  cout << " Inclusion: " << tm.ElapsedTime() << " ns" << endl;

  cout << "Run equals ...";
  cout.flush();
  tm.Start();
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Equals(pss[NUM_TESTS-i-1]);
  }
  tm.Stop();
  cout << " Equals: " << tm.ElapsedTime() << " ns" << endl;

  PrimeSet res;
  cout << "Run union ...";
  cout.flush();
  tm.Start();
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Union(pss[NUM_TESTS-i-1], &res);
  }
  tm.Stop();
  cout << " Union: " << tm.ElapsedTime() << " ns" << endl;

  cout << "Run intersect ...";
  cout.flush();
  tm.Start();
  for (int i = 0; i < NUM_TESTS; ++i) {
    pss[i].Intersect(pss[NUM_TESTS-i-1], &res);
  }
  tm.Stop();
  cout << " Intersect: " << tm.ElapsedTime() << " ns" << endl;

  return 0;
}
