#include "SetAssociative.h"

SetAssociative::SetAssociative(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache,
                               unsigned int memBits): Cache(cacheSize, blockSize, associativity, lruCache, memBits){};

void SetAssociative::processRequest(const std::string &memAddress, bool debug){
    //Turn the memory address into a binary string.

    if (debug) cout << "Memory Request: 0x" << memAddress << endl;

    string binAddress;
    for (const char& i : memAddress){
        binAddress += hexToBinString(i);
    }
    if (debug) cout << "\tBinary Address: " << binAddress << endl;

    //Grab the characters for the bits needed and convert the substring into a number.
    unsigned int tag = binStringToInt(binAddress.substr(0, tagBits));
    unsigned int set = binStringToInt(binAddress.substr(tagBits, setBits));

    if (debug) cout << "\tTag Value: " << tag << " (" << tagBits << " bits)" << endl;
    if (debug) cout << "\tSet Value: " << set << " (" << setBits << " bits)" << endl;

    //Check if the tag exists.
    try{
    auto iter = tagExists(set, tag);
        if (iter != cacheLines.at(set).end()) {
            if (debug) cout << "\tHIT! Tag is " << iter->tag << endl;

            //Update the hits counter and update the lru for the entry (and the counter too).
            hits++;
            iter->lru = (++counter);
        } else {
            if (debug) cout << "\tMISS!" << endl;

            addLine(set, tag, debug);
        }
    }

    catch (out_of_range& out_of_range){
        cerr << "Set " << set << " does not exist in the cache!" << endl;
        cerr << out_of_range.what() << endl;
    }
}