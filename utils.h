#ifndef CGH_UTILS_H
#define CGH_UTILS_H

#include <vector>
#include <sys/time.h>

namespace utils {

void RandomIndecies(int begin, int end, std::vector<int>* indecies);

class Timing {
 public:
  Timing() { }
  ~Timing() { }

  void Start();
  void Stop();
  long ElapsedTime() const;

 private:
  struct timeval begin_, end_;
};


}  // namespace utils

#endif
