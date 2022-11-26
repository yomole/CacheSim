#include "FullyAssociative.h"

FullyAssociative::FullyAssociative(unsigned int cacheSize, unsigned int blockSize, bool lruCache, unsigned int memBits)
    : Cache(cacheSize, blockSize, cacheSize/blockSize, lruCache, memBits){}

void FullyAssociative::processRequest(const string& memAddress, bool debug){
    //Turn the memory address into a binary string.

    if (debug) cout << "Memory Request: 0x" << memAddress << endl;

    string binAddress;
    for (const char& i : memAddress){
        binAddress += hexToBinString(i);
    }
    if (debug) cout << "\tBinary Address: " << binAddress << endl;

    //Grab the characters for the bits needed and convert the substring into a number.
    unsigned int tag = binStringToInt(binAddress.substr(0, tagBits));

    if (debug) cout << "\tTag Value: " << tag << endl;

    //Check if the tag exists.
    auto iter = tagExists(DEFAULT_SET, tag);
    if (iter != cacheLines.at(DEFAULT_SET).end()){
        if (debug) cout << "\tHIT! Tag is " << iter->tag << endl;

        //Update the hits counter and update the lru for the entry (and the counter too).
        hits++;
        iter->lru = (++counter);
    }

    else {
        if (debug) cout << "\tMISS!" << endl;

        addLine(DEFAULT_SET, tag, debug);
    }
}