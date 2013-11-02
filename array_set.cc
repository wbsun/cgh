#include "array_set.h"

#include <algorithm>
#include <vector>

using namespace std;

ArraySet::ArraySet() {
}

ArraySet::ArraySet(const ArraySet& ps) {
  set_ = ps.set_;
}

ArraySet::ArraySet(const SetDataSuite::SetData& data) {
  for (utils::Element i : data.data) {
    set_.push_back(i);
  }
  std::sort(set_.begin(), set_.end());
}

const ArraySet& ArraySet::operator=(const ArraySet& ps) {
  set_ = ps.set_;
  return *this;
}

void ArraySet::Insert(utils::Element e) {
  auto pos = std::upper_bound(set_.begin(), set_.end(), e);
  set_.insert(pos, e);
}

void ArraySet::Remove(utils::Element e) {
  auto pos = std::lower_bound(set_.begin(), set_.end(), e);
  if (pos != set_.end() && pos->val == e.val)
    set_.erase(pos);
}

bool ArraySet::Contains(utils::Element e) const {
  return std::binary_search(set_.begin(), set_.end(), e);
}

bool ArraySet::Includes(const ArraySet& ps) const {
  // return std::includes(set_.begin(), set_.end(),
                       // ps.set_.begin(), ps.set_.end());
  for (auto e : ps.set_) {
    if (!Contains(e))
      return false;
  }
  return true;
}

bool ArraySet::Equals(const ArraySet& ps) const {
  if (set_.size() != ps.set_.size()) {
    return false;
  } else {
    return Includes(ps);
  }
}

void ArraySet::Union(const ArraySet& rhs, ArraySet* r) const {
  vector<utils::Element> tmp(set_.size() + rhs.set_.size());
  auto it = std::set_union(set_.begin(), set_.end(),
                           rhs.set_.begin(), rhs.set_.end(),
                           tmp.begin());
  tmp.resize(it - tmp.begin());
  r->set_.clear();
  for (auto e : tmp) {
    r->set_.push_back(e);
  }
}

void ArraySet::Intersect(const ArraySet& rhs, ArraySet* r) const {
  vector<utils::Element> tmp(set_.size() + rhs.set_.size());
  auto it = std::set_intersection(set_.begin(), set_.end(),
                                  rhs.set_.begin(), rhs.set_.end(),
                                  tmp.begin());
  tmp.resize(it - tmp.begin());
  r->set_ = tmp;
  r->set_.clear();
  for (auto e : tmp) {
    r->set_.push_back(e);
  }
}

void ArraySet::Differentiate(const ArraySet& rhs, ArraySet* r) const {
  vector<utils::Element> tmp(set_.size() + rhs.set_.size());
  auto it = std::set_difference(set_.begin(), set_.end(),
                                rhs.set_.begin(), rhs.set_.end(),
                                tmp.begin());
  tmp.resize(it - tmp.begin());
  r->set_ = tmp;
  r->set_.clear();
  for (auto e : tmp) {
    r->set_.push_back(e);
  }
}

void ArraySet::DiffSym(const ArraySet& rhs, ArraySet* r) const {
  // Not implemented
}
