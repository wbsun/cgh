#ifndef CGH_BENCHMARK_H
#define CGH_BENCHMARK_H

#include "primes.h"

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
  const Primes& primes_;
  int num_sets_;
  int size_;
  int range_;
};

template<typename SetType>
void DoBenchmark(std::vector<std::pair<SetType*, SetType* > >& sets,
                 std::string title);

#endif
