# Problem Statement

We have an input file PageTableFile, which shows page-table entries in two
columns. In our program, there will never be a case when an access to page-table is
a miss.

We have another file TLBAccessesFile which shows the accesses made to the TLB
(except the first line, see below).
The first line of PageTableFile shows the number of bits in VPN.
The second line of PageTableFile shows the number of bits in PFN.

After this, the PageTableFile shows VPN and PFN. However, the TLBAccessesFile
shows virtual-addresses being accessed. The first line of TLBAccessesFile will show
the page-size in bits. For example, if page size is 256B, then the first line will have
value 8. So, for every virtual address shown in TLBAccessesFile, you have to first
find the VPN based on the page-size information.

Our TLB is a fully-associative TLB. We have only one-level TLB. Initially, TLB is
empty. If a TLB access is a hit, fine. If it is a miss, access the page table and fetch
the translation-entry into the TLB. For making replacement decisions, you have to
implement only one replacement policy, namely LRU.

TLB associativity is specified as the command-line argument, e.g., if you program is
RollNumber.cpp/RollNumber.java and its binary is tlbsim, then, for a 16-entry TLB,
we will run
$ g++ Rollnumber.cpp –o tlbsim
$./tlbsim PageTableFile TLBAccessesFile LRU 16
For such a command, your output file should have the name:
RollNumber_PageTableFile_TLBAccessesFile_LRU_16

Both VPN/PFN and virtual addresses will be specified as decimal numbers. We will
not test your program with any incorrect input or extra spaces or extra empty lines.
We will test your algorithm using our inputs files. Several sample TLBAccessesFile
are provided in a google folder to test your submission (see below). In this file, after
the first line, each entry shows the address which is accessed. The corresponding
output files (assuming roll number of 1111) are also attached.
Limits: We will not check your code for TLB associativity value greater than 4096.
In PageTableFile, there will be at most 10,000 lines (including the first line showing
"VPN PFN").

In TLBAccessesFile, there will be at most 10,000 lines.
Page-size will be at most 1KB.
So, if you are using fixed-size arrays, you can write the code accordingly.
Submission: The name of your submitted file MUST be
Rollnumber.cpp/RollNumber.java, e.g., 1111.cpp.

You need to upload your code as a single C++/C/Java source file, which can be
compiled and run with g++ (or equivalent) without using any flags. It is OK to use
c++11 features. Use of STL (e.g., vector, find, etc.) is acceptable.

Output: Your program should print everything in output file (anything printed on
command-prompt will be ignored). In such a file, the first three lines should be
TOTAL_ACCESSES = 869
TOTAL_MISSES = 800
TOTAL_HITS = 69

Of course, your numbers may be different than 800/69 etc.
After these lines, on each line, print corresponding physical address and HIT or
MISS, depending on whether the access hit or missed in the TLB. Multiple sample
output files are available.
You can use them to check your code.
