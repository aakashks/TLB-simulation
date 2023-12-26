#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "lrucache.h"

using namespace std;

pair<int, bool> va_to_pa_translation(int va, unordered_map<int, int> pageTable, int page_size_bits, LRUCache &tlb)
{
    int page_size = pow(2, page_size_bits);
    int vpn = va / page_size;
    int page_offset = va % page_size;
    int pfn = tlb.get(vpn);

    if (pfn == -1) 
    {
        // TLB Miss
        pfn = pageTable[vpn];
        tlb.put(vpn, pfn);
        return pair<int, bool>(pfn * page_size + page_offset, false);
    }
	return pair<int, bool>(pfn * page_size + page_offset, true);
}

int main(int argc, char *argv[])
{
    string pageTableFileName = argv[1];
    string TLBAccessesFileName = argv[2];
    string policy = argv[3];
    string cache_size = argv[4];

    ifstream pageTableFile(pageTableFileName);
    ifstream TLBAccessesFile(TLBAccessesFileName);

    // output file
    ofstream outFile("./22125001_" + pageTableFileName + "_" + TLBAccessesFileName + "_" + policy + "_" + cache_size);

    // // READING INPUT FILES
    // inputting first few lines
    int VPNbits, PFNbits;
    pageTableFile >> VPNbits >> PFNbits;
    
    // newline VPN PFN title lines
    string _;
    getline(pageTableFile, _);
    getline(pageTableFile, _);

    vector<int> VPN, PFN;
    
    int vpn, pfn;
    while (pageTableFile >> vpn >> pfn)
    {
        VPN.push_back(vpn);
        PFN.push_back(pfn);
    }

    // reading TLB Accesses
    int page_size_bits;
    TLBAccessesFile >> page_size_bits;

    vector<int> TLBAccesses;
    int access;
    while (TLBAccessesFile >> access)
    {
        TLBAccesses.push_back(access);
    }

    // // MAP VPN to PFN
    unordered_map<int, int> pageTable;
    for (int i=0; i<VPN.size(); i++)
    {
        pageTable[VPN[i]] = PFN[i];
    }

    // // translating all virtual addresses
    LRUCache tlb(stoi(cache_size));

    vector<pair<int, bool>> pa_hit_list;
    int num_hits = 0;
    int num_misses = 0; 
    for (auto va: TLBAccesses)
    {   
        pair<int, bool> pa_hit = va_to_pa_translation(va, pageTable, page_size_bits, tlb);
        if (pa_hit.second)
            num_hits += 1;
        else
            num_misses += 1;

        pa_hit_list.push_back(pa_hit);
    }
    int num_accesses = num_hits + num_misses;

    // // writing into the ouput file
    outFile << "TOTAL_ACCESSES = " << num_accesses << endl;
    outFile << "TOTAL_MISSES = " << num_misses << endl;
    outFile << "TOTAL_HITS = " << num_hits << endl;

    for (auto pa_hit: pa_hit_list)
    {
        outFile << pa_hit.first << " " << (pa_hit.second ? "HIT" : "MISS") << endl;
    }

    pageTableFile.close();
    TLBAccessesFile.close();
    outFile.close();
    return 0;
}
