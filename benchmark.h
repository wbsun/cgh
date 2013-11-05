#ifndef CGH_BENCHMARK_H
#define CGH_BENCHMARK_H

#include "primes.h"
#include "utils.h"

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <locale>

class SetDataSuite {
 public:
  struct SetData {
    std::vector<utils::Element> data;
    utils::Element for_insert;
    utils::Element for_remove;
    utils::Element for_contains_in;
    utils::Element for_contains_not_in;
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
                 int equals_true_ratio, bool latex = false) {
  if (latex) {
    std::cout.imbue(std::locale(""));
  }
  
  if (!latex)
    std::cout << "Benchmark on " << title << std::endl;
  else
    std::cout << "& " << title << " ";

  long includes_time = 0,
      equals_time = 0,
      union_time = 0,
      diff_time = 0,
      intersect_time = 0,
      contains_time = 0,
      delete_time = 0,
      insert_time = 0;

  std::vector<SetType*> sets;
  for (int i = 0; i < set_data.num_sets(); ++i) {
    sets.push_back(new SetType(set_data.GetSetData(i)));
  }

  std::vector<SetType*> dup_sets_insert, dup_sets_remove, dup_sets;
  for (auto s : sets) {
    dup_sets.push_back(new SetType(*s));
    dup_sets_insert.push_back(new SetType(*s));
    dup_sets_remove.push_back(new SetType(*s));
  }

  int threshold = 0;
  utils::Timing tm;

  threshold = sets.size() * contains_true_ratio / 100;
  if (!latex) {
    std::cout << "Contains: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Contains(set_data.GetSetData(i).for_contains_in);
    else
      sets[i]->Contains(set_data.GetSetData(i).for_contains_not_in);
  }
  tm.Stop();
  contains_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << contains_time << " ns" << std::endl;

  if (!latex) {
    std::cout << "Insert: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    dup_sets_insert[i]->Insert(set_data.GetSetData(i).for_insert);
  }
  tm.Stop();
  insert_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << insert_time << " ns" << std::endl;

  if (!latex) {
    std::cout << "Delete: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    dup_sets_remove[i]->Remove(set_data.GetSetData(i).for_remove);
  }
  tm.Stop();
  delete_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << delete_time << " ns" << std::endl;

  threshold = sets.size() * includes_true_ratio / 100;
  if (!latex) {
    std::cout << "Includes: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Includes(*dup_sets_remove[i]);
    else
      sets[i]->Includes(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  includes_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << includes_time << " ns" << std::endl;

  threshold = sets.size() * equals_true_ratio / 100;
  if (!latex) {
    std::cout << "Equals: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    if (i < threshold)
      sets[i]->Equals(*dup_sets[i]);
    else
      sets[i]->Equals(*sets[sets.size() - i - 1]);
  }
  tm.Stop();
  equals_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << equals_time << " ns" << std::endl;

  SetType res;
  if (!latex) {
    std::cout << "Union: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    sets[i]->Union(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  union_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << union_time << " ns" << std::endl;

  if (!latex) {
    std::cout << "Intersect: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    sets[i]->Intersect(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  intersect_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << intersect_time << " ns" << std::endl;

  if (!latex) {
    std::cout << "Diff: "; std::cout.flush();
  }
  tm.Start();
  for (int i = 0; i < (int)sets.size(); ++i) {
    sets[i]->Differentiate(*sets[sets.size() - i - 1], &res);
  }
  tm.Stop();
  diff_time = (tm.ElapsedTime()*1000) / sets.size();
  if (!latex)
    std::cout << diff_time << " ns" << std::endl;

  for (int i = 0; i < (int)sets.size(); ++i) {
    delete sets[i];
    delete dup_sets[i];
    delete dup_sets_insert[i];
    delete dup_sets_remove[i];
  }

  if (latex) {
    std::cout << " & " << includes_time
              << " & " << equals_time
              << " & " << union_time
              << " & " << diff_time
              << " & " << intersect_time
              << " & " << contains_time
              << " & " << delete_time
              << " & " << insert_time
              << " \\\\ "
              << std::endl;
  }
}

#endif
