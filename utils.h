#ifndef CGH_UTILS_H
#define CGH_UTILS_H

#include <vector>
#include <sys/time.h>
#include <functional>

namespace utils {

struct Element {
  unsigned long val;
  int id;
  Element() { }
  Element(int v, int i) : val((unsigned long)v), id(i) {}
  Element(unsigned long v, int i) : val(v), id(i) {}
  Element(const Element& e) :val(e.val), id(e.id) {}
  const Element& operator=(const Element& e) {
    val = e.val;
    id = e.id;
    return *this;
  }
  bool operator==(const utils::Element& b) const {
    return val == b.val;
  }

  bool operator<(const utils::Element& b) const {
    return val < b.val;
  }
};

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

// bool operator==(const utils::Element& a, const utils::Element& b) {
  // return a.val == b.val;
// }

namespace std {
template<> struct less<utils::Element> {
  bool operator()(const utils::Element& a, const utils::Element& b) const {
    return a.val < b.val;
  }
};
  
template<> struct hash<utils::Element> {
  size_t operator()(const utils::Element& e) const {
    return (e.val+e.id) % 2;
  }
};
}

#endif
