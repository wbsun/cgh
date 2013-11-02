#include "hashset.h"

HashSet::HashSet() {
}

HashSet::HashSet(const HashSet& ps) {
  set_ = ps.set_;
}

HashSet::HashSet(const SetDataSuite::SetData& data) {
  for (utils::Element i : data.data) {
    set_.insert(i);
  }
}

const HashSet& HashSet::operator=(const HashSet& ps) {
  set_ = ps.set_;
  return *this;
}

void HashSet::Insert(utils::Element e) {
  set_.insert(e);
}

void HashSet::Remove(utils::Element e) {
  set_.erase(e);
}

bool HashSet::Contains(utils::Element e) const {
  return set_.find(e) != set_.end();
}

bool HashSet::Includes(const HashSet& ps) const {
  for (auto e : ps.set_) {
    if (!Contains(e)) {
      return false;
    }
  }
  return true;
}

bool HashSet::Equals(const HashSet& ps) const {
  if (set_.size() != ps.set_.size()) {
    return false;
  } else {
    return Includes(ps);
  }
}

void HashSet::Union(const HashSet& rhs, HashSet* r) const {
  r->set_ = set_;
  r->set_.insert(rhs.set_.begin(), rhs.set_.end());
}

void HashSet::Intersect(const HashSet& rhs, HashSet* r) const {
  r->set_.clear();
  for (auto e : set_) {
    if (rhs.Contains(e)) {
      r->Insert(e);
    }
  }
}

void HashSet::Differentiate(const HashSet& rhs, HashSet* r) const {
  r->set_.clear();
  for (auto e : set_) {
    if (!rhs.Contains(e)) {
      r->Insert(e);
    }
  }
}

void HashSet::DiffSym(const HashSet& rhs, HashSet* r) const {
  // Not implemented
}
