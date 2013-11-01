CC = gcc
CXX = g++
CFLAGS = -O3 -Wall
CXXFLAGS = -O3 -std=c++0x -Wall
CXXFLAGS_NO_OPT = -O0 -std=c++0x -Wall
LDFLAGS = 
GMP_LDFLAGS = -lgmpxx -lgmp

OBJS = primes.o prime_set.o utils.o
LIBS =
TEST-OBJS = primes-test.o prime_set-test.o
TEST-EXES = primes-test prime_set-test
EXES = 

default: $(LIBS) $(EXES) $(TEST-EXES)

primes.o: primes.cc primes.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

primes-test.o: primes-test.cc primes.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

primes-test: primes-test.o primes.o
	$(CXX) $(LDFLAGS) $^ -o $@

prime_set.o: prime_set.cc prime_set.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

prime_set-test.o: prime_set-test.cc prime_set.h primes.h utils.h
	$(CXX) -c $(CXXFLAGS_NO_OPT) $< -o $@

prime_set-test: prime_set-test.o prime_set.o primes.o utils.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(GMP_LDFLAGS)

utils.o: utils.cc utils.h
	$(CXX) -c $(CXXFLAGS) $< -o $@


.PHONY:	clean

clean:
	$(RM) -rf $(OBJS)
	$(RM) -rf $(TEST-OBJS)
	$(RM) -rf $(LIBS)
	$(RM) -rf $(EXES)
	$(RM) -rf $(TEST-EXES)
