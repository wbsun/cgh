#ifndef CGH_BITSET_H
#define CGH_BITSET_H

#include "benchmark.h"
#include "utils.h"

#include <bitset>

template<size_t N>
class BitSet {
 public:
  BitSet() { }
  BitSet(const BitSet<N>& bs) {
    bs_ |= bs.bs_;
  }
  BitSet(const SetDataSuite::SetData& data) {
    for (utils::Element i : data.data) {
      bs_.set(i.val);
    }
  }
  virtual ~BitSet() { }

  const BitSet& operator=(const BitSet<N>& ps) {
    bs_.reset();
    bs_ |= ps.bs_;
    return *this;
  }
  
  virtual void Insert(utils::Element e) {
    bs_.set(e.val);
  }
  virtual void Remove(utils::Element e) {
    bs_.reset(e.val);
  }
  virtual bool Contains(utils::Element e) const {
    return bs_.test(e.val);
  }
  
  virtual bool Includes(const BitSet<N>& ps) const {
    std::bitset<N> bs = bs_ & ps.bs_;
    return bs == ps.bs_;
  }
  virtual bool Equals(const BitSet<N>& ps) const {
    std::bitset<N> bs = bs_ ^ ps.bs_;
    return bs.none();
  }

  virtual void Union(const BitSet<N>& rhs, BitSet<N>* r) const {
    r->bs_ = rhs.bs_ | bs_;
  }
  virtual void Intersect(const BitSet<N>& rhs, BitSet<N>* r) const {
    r->bs_ = rhs.bs_ & bs_;
  }
  virtual void Differentiate(const BitSet<N>& rhs, BitSet<N>* r) const {
    r->bs_ = rhs.bs_ ^ bs_; // this is sym-diff
  }
  virtual void DiffSym(const BitSet<N>& rhs, BitSet<N>* r) const {
    r->bs_ = rhs.bs_ ^ bs_;
  }

 protected:
  std::bitset<N> bs_;
};


#endif
