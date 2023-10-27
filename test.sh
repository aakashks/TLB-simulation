#!/bin/bash

g++ tlbsim.cpp -o tlbsim
./tlbsim PageTableFile3 TLBAccessesFile3 LRU 512
echo done
