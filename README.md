cgh
===

C version GodelHash

Compile and Run:
  - Install libgmp-dev on Linux.
  - make
  - ./prime_set-test 10000000 ./primes-db/primes10000000.txt 1000 500000

The program tests 1000 times of operations (currently only "Contains" and "Inclusion"). 
The command run above creates 1000 (hard-coded number) prime sets, each of them contains 1000 (specified 
by the last '1000') random primes read from the given prime number file. '500000' specifies the number of
the primes among which we choose the 1000 random primes to create a prime set.

Current result:
```
wbsun@fe:/mnt/cgh$ ./prime_set-test 10000000 ./primes-db/primes10000000.txt 1000 500000
Contains: 347 us
Inclusion: 10 us
```

Note that the time shown above is 1000 times of operations, so a single operation takes only 1/1000 of the
shown numbers.
