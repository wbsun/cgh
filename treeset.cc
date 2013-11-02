#include "treeset.h"

TreeSet::TreeSet() {
}

TreeSet::TreeSet(const TreeSet& ps) {
  set_ = ps.set_;
}

TreeSet::TreeSet(const SetDataSuite::SetData& data) {
  for (utils::Element i : data.data) {
    set_.insert(i);
  }
}

const TreeSet& TreeSet::operator=(const TreeSet& ps) {
  set_ = ps.set_;
  return *this;
}

void TreeSet::Insert(utils::Element e) {
  set_.insert(e);
}

void TreeSet::Remove(utils::Element e) {
  set_.erase(e);
}

bool TreeSet::Contains(utils::Element e) const {
  return set_.find(e) != set_.end();
}

bool TreeSet::Includes(const TreeSet& ps) const {
  for (auto e : ps.set_) {
    if (!Contains(e)) {
      return false;
    }
  }
  return true;
}

bool TreeSet::Equals(const TreeSet& ps) const {
  if (set_.size() != ps.set_.size()) {
    return false;
  } else {
    return Includes(ps);
  }
}

void TreeSet::Union(const TreeSet& rhs, TreeSet* r) const {
  r->set_ = set_;
  r->set_.insert(rhs.set_.begin(), rhs.set_.end());
}

void TreeSet::Intersect(const TreeSet& rhs, TreeSet* r) const {
  r->set_.clear();
  for (auto e : set_) {
    if (rhs.Contains(e)) {
      r->Insert(e);
    }
  }
}

void TreeSet::Differentiate(const TreeSet& rhs, TreeSet* r) const {
  r->set_.clear();
  for (auto e : set_) {
    if (!rhs.Contains(e)) {
      r->Insert(e);
    }
  }
}

void TreeSet::DiffSym(const TreeSet& rhs, TreeSet* r) const {
  // Not implemented
}
