#ifndef CGH_HASHSET_H
#define CGH_HASHSET_H

#include "benchmark.h"
#include "utils.h"

#include <unordered_set>

class HashSet {
 public:
  HashSet();
  HashSet(const HashSet& hs);
  HashSet(const SetDataSuite::SetData& data);
  virtual ~HashSet() { }

  const HashSet& operator=(const HashSet& ps);
  
  virtual void Insert(utils::Element e);
  virtual void Remove(utils::Element e);
  virtual bool Contains(utils::Element e) const;
  
  virtual bool Includes(const HashSet& ps) const;
  virtual bool Equals(const HashSet& ps) const;

  virtual void Union(const HashSet& rhs, HashSet* r) const;
  virtual void Intersect(const HashSet& rhs, HashSet* r) const;
  virtual void Differentiate(const HashSet& rhs, HashSet* r) const;
  virtual void DiffSym(const HashSet& rhs, HashSet* r) const;
  
 protected:
  std::unordered_set<utils::Element> set_;
};

#endif
