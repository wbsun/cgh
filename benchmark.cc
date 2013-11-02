#include "benchmark.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>

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

template<typename SetType>
void DoBenchmark(std::vector<SetType*> sets, std::string title, const SetDataSuite& set_data,
                 int contains_true_ratio, int includes_true_ratio,
                 int equals_true_ratio) {
  cout << "Benchmark on " << title << endl;

  int threshold = 0;
  utils::Timing tm;

  threshold = sets.size() / 10 * contains_true_ratio;
  cout << "Contains: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Contains(set_data.GetSetData(i).for_contains_in);
    else
      sets[i]->Contains(set_data.GetSetData(i).for_contains_not_in);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  vector<SetType*> dup_sets_insert, dup_sets_remove, dup_sets;
  for (auto s : sets) {
    dup_sets.push_back(new SetType(*s));
    dup_sets_insert.push_back(new SetType(*s));
    dup_sets_remove.push_back(new SetType(*s));
  }

  cout << "Insert: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    dup_sets_insert[i]->Insert(set_data.GetSetData(i).for_insert);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  cout << "Remove: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    dup_sets_remove[i]->Remove(set_data.GetSetData(i).for_remove);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  threshold = sets.size() / 10 * includes_true_ratio;
  cout << "Includes: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Includes(*dup_sets_remove[i]);
    else
      sets[i]->Includes(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  threshold = sets.size() / 10 * equals_true_ratio;
  cout << "Equals: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Equals(*dup_sets[i]);
    else
      sets[i]->Equals(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  SetType res;
  cout << "Union: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Union(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  cout << "Intersect: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Intersect(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  cout << "Diff: "; cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Differentiate(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << endl;

  for (int i = 0; i < sets.size(); ++i) {
    delete dup_sets[i];
    delete dup_sets_insert[i];
    delete dup_sets_remove[i];
  }
}
