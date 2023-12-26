#!/bin/bash

g++ tlbsim.cpp -o tlbsim
./tlbsim SampleRuns/PageTableFile3 SampleRuns/TLBAccessesFile3 LRU 512
echo done
