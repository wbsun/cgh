#ifndef CGH_TREESET_H
#define CGH_TREESET_H

#include "benchmark.h"
#include "utils.h"

#include <set>

class TreeSet {
 public:
  TreeSet();
  TreeSet(const TreeSet& hs);
  TreeSet(const SetDataSuite::SetData& data);
  virtual ~TreeSet() { }

  const TreeSet& operator=(const TreeSet& ps);
  
  virtual void Insert(utils::Element e);
  virtual void Remove(utils::Element e);
  virtual bool Contains(utils::Element e) const;
  
  virtual bool Includes(const TreeSet& ps) const;
  virtual bool Equals(const TreeSet& ps) const;

  virtual void Union(const TreeSet& rhs, TreeSet* r) const;
  virtual void Intersect(const TreeSet& rhs, TreeSet* r) const;
  virtual void Differentiate(const TreeSet& rhs, TreeSet* r) const;
  virtual void DiffSym(const TreeSet& rhs, TreeSet* r) const;
  
 protected:
  std::set<utils::Element> set_;
};

#endif
