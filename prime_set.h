#ifndef CGH_PRIME_SET_H
#define CGH_PRIME_SET_H

#include "benchmark.h"
#include "utils.h"

#include <gmpxx.h>

class PrimeSet {
 public:
  PrimeSet();
  PrimeSet(const mpz_t p, int size);
  PrimeSet(const PrimeSet& ps);
  PrimeSet(const SetDataSuite::SetData& data);
  virtual ~PrimeSet();

  const PrimeSet& operator=(const PrimeSet& ps);

  // REQUIRES: e not in this
  virtual void Insert(utils::Element e);
  // REQUIRES: e in this
  virtual void Remove(utils::Element e);
  virtual bool Contains(utils::Element e) const;

  virtual bool Includes(const PrimeSet& ps) const;
  virtual bool Equals(const PrimeSet& ps) const;

  virtual void Union(const PrimeSet& rhs, PrimeSet* r) const;
  virtual void Intersect(const PrimeSet& rhs, PrimeSet* r) const;
  virtual void Differentiate(const PrimeSet& rhs, PrimeSet* r) const;
  virtual void DiffSym(const PrimeSet& rhs, PrimeSet* r) const;

  size_t num_bits() const;
  
 protected:
  mpz_t product_;
  int size_;
};

#endif
