CC = gcc
CXX = g++
CFLAGS = -O2 -Wall
CXXFLAGS = -O2 -std=c++0x -Wall
CXXFLAGS_NO_OPT = -O0 -std=c++0x -Wall
LDFLAGS = -O2
GMP_LDFLAGS = -lgmpxx -lgmp

OBJS = primes.o prime_set.o utils.o benchmark.o eval_sets.o hashset.o treeset.o array_set.o
LIBS =
TEST-OBJS = primes-test.o
TEST-EXES = primes-test
EXES = eval_sets

default: $(LIBS) $(EXES) $(TEST-EXES)

primes.o: primes.cc primes.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

primes-test.o: primes-test.cc primes.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

primes-test: primes-test.o primes.o
	$(CXX) $(LDFLAGS) $^ -o $@

prime_set.o: prime_set.cc prime_set.h utils.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

utils.o: utils.cc utils.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

benchmark.o: benchmark.cc benchmark.h utils.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

hashset.o: hashset.cc hashset.h utils.h benchmark.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

treeset.o: treeset.cc treeset.h utils.h benchmark.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

array_set.o: array_set.cc array_set.h utils.h benchmark.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

eval_sets.o: eval_sets.cc *.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

eval_sets: primes.o utils.o benchmark.o prime_set.o hashset.o treeset.o array_set.o eval_sets.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(GMP_LDFLAGS)

.PHONY:	clean

clean:
	$(RM) -rf $(OBJS)
	$(RM) -rf $(TEST-OBJS)
	$(RM) -rf $(LIBS)
	$(RM) -rf $(EXES)
	$(RM) -rf $(TEST-EXES)
