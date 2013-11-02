#ifndef CGH_HASHSET_H
#define CGH_HASHSET_H

#include "benchmark.h"

#include <unordered_set>

class HashSet {
public:
  typedef unsigned long ElemType;
  HashSet();
  HashSet(const HashSet& hs);
  HashSet(const SetDataSuite::SetData& data);
  virtual ~HashSet() { }

  const HashSet& operator=(const HashSet& ps);
  
  virtual void Insert(ElemType e);
  virtual void Remove(ElemType e);
  virtual bool Contains(ElemType e) const;
  
  virtual bool Includes(const HashSet& ps) const;
  virtual bool Equals(const HashSet& ps) const;

  virtual void Union(const HashSet& rhs, HashSet* r) const;
  virtual void Intersect(const HashSet& rhs, HashSet* r) const;
  virtual void Differentiate(const HashSet& rhs, HashSet* r) const;
  virtual void DiffSym(const HashSet& rhs, HashSet* r) const;
  
protected:
  std::unordered_set<ElemType> set_;
};

#endif
