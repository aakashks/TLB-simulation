# Virtual Memory - TLB Simulation

Part of **ECN 207- Computer Architecture and Organization** course

Simulates LRU policy TLB in C++

Detailed problem statement is in [question.md](question.md)

## How to run

run test.sh (assuming gcc compiler is installed)

## What is TLB?

TLB stands for Translation Lookaside Buffer. It is a cache which is needed for virtual memory.

- stores the recent translations of virtual page numbers to physical page numbers
- used to reduce the time taken to access the physical memory
- if the mapping is not found in TLB, then it is searched in the page table
- it is a small cache, so it is faster than page table

## Some abbreviations used in the code

- TLB - Translation Lookaside Buffer
- VPN - Virtual Page Number
- PFN - Physical Frame Number
- LRU - Least Recently Used

## References

- [wikipedia](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)
