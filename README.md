CQueue
======
High-performance fixed-length integer queue implementation in C

By: Roneil Rumburg

## Overview:
CQueue is a high-performance implementation of the traditional queue data
structure in C. It works by using an array of integers to represent the queue
and preallocates the queue to the size given by the client.

## Compilation:
Compile CQueue using the provided makefile (run "make" in the same directory as
the CQueue code). The makefile currently uses gcc but other C compilers should
work fine with little modification of the makefile.

## Usage Details:
To use this CQueue implementation, simply include the 'cqueue.h' header file in
your code and link your program to the cqueue.o binary file. The header file
contains documentation of the various functions available for interacting with
a CQueue.
To run a set of tests to make sure that CQueue compiled correctly, use the
included cqueue-test program. To run basic tests run cqueue-test with no
arguments, and to run a performance test run with the argument 'performance'.

## Implementation Details:
The queue works by storing an array of integers (where all the data is held), a
count of the number of integers currently in the queue, the capacity of the
queue, and the current position in the queue (starts at 0). As items are added
to the queue, they fill it from index 0 to capacity, and as items are retrieved
from the queue the current position is incremented up (instead of actually
removing the item from the queue). The queue implementation is circular,
so as items are added and removed only counters are manipulated and the queue's
internal storage never needs to be reorganized to make room for new elements.
By using this structure, all queue operations (create, dispose, count, put,
get, and peek) run in O(1) time.

## Performance:
Because the implementation manipulates memory directly and avoids moving memory
around it runs blazingly fast.  When compiled with no optimizations (O0) and
debug information enabled, the performance test finishes in about 8 seconds on
my 2.2 GHz Core i7 Macbook Pro, and that test fully utilizes a 100 million
element queue (using around 400 megabytes of memory), filling and emptying it
multiple times. With heavy optimization (O2), the test finishes in just over
1.6 seconds on my machine, with performance gains likely coming from inlining
the addressing helper function. To test it for yourself, compile the project
and run "time ./cqueue-test performance" to see how it runs on your machine.

## License
[WTFPL](http://www.wtfpl.net/about/)
