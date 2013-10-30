#ifndef CGH_PRIME_SET_H
#define CGH_PRIME_SET_H

#include <gmpxx.h>
#include <unordered_set>

class PrimeSet {
 public:
  typedef unsigned long ElemType;
  PrimeSet();
  PrimeSet(const mpz_t p, int size);
  PrimeSet(const PrimeSet& ps);
  virtual ~PrimeSet();

  const PrimeSet& operator=(const PrimeSet& ps);

  // REQUIRES: e not in this
  void Insert(ElemType e);
  // REQUIRES: e in this
  void Remove(ElemType e);
  bool Contains(ElemType e) const;

  bool Includes(const PrimeSet& ps) const;
  bool Equals(const PrimeSet& ps) const;

  void Union(const PrimeSet& rhs, PrimeSet* r) const;
  void Intersect(const PrimeSet& rhs, PrimeSet* r) const;
  void Differentiate(const PrimeSet& rhs, PrimeSet* r) const;
  void Minus(const PrimeSet& rhs, PrimeSet* r) const;

  size_t num_bits() const;
  
 private:
  mpz_t product_;
  int size_;
};

#endif
