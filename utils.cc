#include "utils.h"

#include <algorithm>

using namespace std;

namespace utils {

void RandomIndecies(int begin, int end, std::vector<int>* indecies) {
  if (indecies->size() == 0) {
    for (int i = begin; i < end; ++i) {
      indecies->push_back(i);
    }
  }
  random_shuffle(indecies->begin(), indecies->end());
}

void Timing::Start() {
  gettimeofday(&begin_, nullptr);
}

void Timing::Stop() {
  gettimeofday(&end_, nullptr);
}

long Timing::ElapsedTime() const {
  return 1000000*(end_.tv_sec - begin_.tv_sec) +
      ((long)(end_.tv_usec) - (long)(begin_.tv_usec));
}

}  // namespace utils
