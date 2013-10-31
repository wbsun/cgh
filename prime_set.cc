#include "prime_set.h"

PrimeSet::PrimeSet() {
  mpz_init_set_ui(product_, 1UL);
  size_ = 0;
}

PrimeSet::PrimeSet(const mpz_t p, int size) {
  mpz_init_set(product_, p);
  size_ = size;
}

PrimeSet::PrimeSet(const PrimeSet& ps) {
  mpz_init_set(product_, ps.product_);
  size_ = ps.size_;
}

PrimeSet::~PrimeSet() {
  mpz_clear(product_);
}

const PrimeSet& PrimeSet::operator=(const PrimeSet& ps) {
  mpz_set(product_, ps.product_);
  size_ = ps.size_;
  return *this;
}

void PrimeSet::Insert(PrimeSet::ElemType e) {
  mpz_mul_ui(product_, product_, e);
  ++size_;
}

void PrimeSet::Remove(PrimeSet::ElemType e) {
  mpz_divexact_ui(product_, product_, e);
  --size_;
}

bool PrimeSet::Contains(PrimeSet::ElemType e) const {
  return mpz_divisible_ui_p(product_, e) != 0;
}

bool PrimeSet::Includes(const PrimeSet& ps) const {
  if (size_ < ps.size_) {
    return false;
  }
  // Comment out for benchmarking
  // else if (size_ == ps.size_) {
    // return mpz_cmp(product_, ps.product_) == 0;
  // } else {
  return mpz_divisible_p(product_, ps.product_) != 0;
  // }
}

bool PrimeSet::Equals(const PrimeSet& ps) const {
  if (size_ != ps.size_) {
    return false;
  } else {
    return mpz_cmp(product_, ps.product_) == 0;
  }
}

void PrimeSet::Union(const PrimeSet& rhs, PrimeSet* r) const {
  mpz_lcm(r->product_, product_, rhs.product_);
}

void PrimeSet::Intersect(const PrimeSet& rhs, PrimeSet* r) const {
  mpz_gcd(r->product_, product_, rhs.product_);
}

void PrimeSet::Differentiate(const PrimeSet& rhs, PrimeSet* r) const {
}

void PrimeSet::Minus(const PrimeSet& rhs, PrimeSet* r) const {
}

size_t PrimeSet::num_bits() const {
  return mpz_sizeinbase(product_, 2);
}

