#ifndef CGH_BENCHMARK_H
#define CGH_BENCHMARK_H

#include "primes.h"
#include "utils.h"

#include <vector>
#include <string>
#include <utility>
#include <iostream>

class SetDataSuite {
 public:
  struct SetData {
    std::vector<int> data;
    int for_insert;
    int for_remove;
    int for_contains_in;
    int for_contains_not_in;
  };
  
  SetDataSuite(int num_sets, int size, int range, const Primes& primes);
  ~SetDataSuite();

  void CreateAllSetData();
  const SetData& GetSetData(int which) const { return set_data_[which]; }

  int num_sets() const { return num_sets_; }
  
 private:
  std::vector<SetData> set_data_;
  int num_sets_;
  int size_;
  int range_;
  const Primes& primes_;
};

template<typename SetType>
void DoBenchmark(std::string title, const SetDataSuite& set_data,
                 int contains_true_ratio, int includes_true_ratio,
                 int equals_true_ratio) {
  std::cout << "Benchmark on " << title << std::endl;

  std::vector<SetType*> sets;
  for (int i = 0; i < set_data.num_sets(); ++i) {
    sets.push_back(new SetType(set_data.GetSetData(i)));
  }

  int threshold = 0;
  utils::Timing tm;

  threshold = sets.size() / 10 * contains_true_ratio;
  std::cout << "Contains: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Contains(set_data.GetSetData(i).for_contains_in);
    else
      sets[i]->Contains(set_data.GetSetData(i).for_contains_not_in);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  std::vector<SetType*> dup_sets_insert, dup_sets_remove, dup_sets;
  for (auto s : sets) {
    dup_sets.push_back(new SetType(*s));
    dup_sets_insert.push_back(new SetType(*s));
    dup_sets_remove.push_back(new SetType(*s));
  }

  std::cout << "Insert: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    dup_sets_insert[i]->Insert(set_data.GetSetData(i).for_insert);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  std::cout << "Remove: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    dup_sets_remove[i]->Remove(set_data.GetSetData(i).for_remove);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  threshold = sets.size() / 10 * includes_true_ratio;
  std::cout << "Includes: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Includes(*dup_sets_remove[i]);
    else
      sets[i]->Includes(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  threshold = sets.size() / 10 * equals_true_ratio;
  std::cout << "Equals: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Equals(*dup_sets[i]);
    else
      sets[i]->Equals(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  SetType res;
  std::cout << "Union: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Union(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  std::cout << "Intersect: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Intersect(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  std::cout << "Diff: "; std::cout.flush();
  tm.Start();
  for (int i = 0; i < sets.size(); ++i) {
    sets[i]->Differentiate(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  std::cout << (tm.ElapsedTime()*1000) / sets.size() << " ns" << std::endl;

  for (int i = 0; i < sets.size(); ++i) {
    delete sets[i];
    delete dup_sets[i];
    delete dup_sets_insert[i];
    delete dup_sets_remove[i];
  }
}

#endif
