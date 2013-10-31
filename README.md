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
Generating sets: .................................................................................................... Done
Run contains ... Contains: 346 ns
Run insert ... Insert: 400 ns
Run remove ... Remove: 743 ns
Run inclusion ... Inclusion: 442 ns
Run equals ... Equals: 9 ns
Run union ... Union: 429274 ns
Run intersect ... Intersect: 393631 ns
```
