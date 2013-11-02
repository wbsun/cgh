cgh
===

C version GodelHash

Compile and Run:
  - Install libgmp-dev on Linux.
  - make
  - ./eval_sets ./primes-db/primes10000000.txt 1000 5000 10000 50 50 50

Usage: eval_sets prime-number-file times-of-operations set-size universe-size contains-true-ratio includes-true-ratio equals-true-ratio [latex-output]

This program runs each operations 'times-of-operations' times on sets containing 'set-size' elements randomly fetched from the 'universe-size' prime space.

Evaluated on Emulab machine, hardware spec:
  - Intel Xeon E5-1660 3.3GHz six-core CPU
  - 32GB DDR3-2133 memory,
  - Intel X79 chipset motherboard
  - Smasung 840 Pro 128GB SSD.

Implementation:
  - GodelHash based primeset: using GNU GMP (GNU Multiple Precision Aritchmetic library) for big integer aritchmetic operations.
  - Sorted Arrayset: using std::vector to store data, using std::binary_search, std::set_union/set_difference/includes/set_intersect algorithms for set operations.
  - Sorted Treeset: using std::set, which is a red-black tree based set implementation.
  - Hashset: using std::unordered_set, which is a bucket-based hashset.

Output:
  Times show are in nanoseconds for each single operation.

Explaination:
  GMP is highly optimized on modern CPUs to operate at very long data types with a single instruction.
  Instruction sets such as SSE and AVX can do 256 bits or even 512 bits data arithmetic operations.
  
  