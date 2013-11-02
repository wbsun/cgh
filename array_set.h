#ifndef CGH_ARRAY_SET_H
#define CGH_ARRAY_SET_H

#include "benchmark.h"
#include "utils.h"

#include <vector>

class ArraySet {
public:
  ArraySet();
  ArraySet(const ArraySet& hs);
  ArraySet(const SetDataSuite::SetData& data);
  virtual ~ArraySet() { }

  const ArraySet& operator=(const ArraySet& ps);
  
  virtual void Insert(utils::Element e);
  virtual void Remove(utils::Element e);
  virtual bool Contains(utils::Element e) const;
  
  virtual bool Includes(const ArraySet& ps) const;
  virtual bool Equals(const ArraySet& ps) const;

  virtual void Union(const ArraySet& rhs, ArraySet* r) const;
  virtual void Intersect(const ArraySet& rhs, ArraySet* r) const;
  virtual void Differentiate(const ArraySet& rhs, ArraySet* r) const;
  virtual void DiffSym(const ArraySet& rhs, ArraySet* r) const;
  
protected:
  std::vector<utils::Element> set_;
};

#endif
