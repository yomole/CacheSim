#include "FullyAssociative.h"

FullyAssociative::FullyAssociative(unsigned int cacheSize, unsigned int blockSize, bool lruCache, unsigned int memBits)
    : Cache(cacheSize, blockSize, 1, lruCache, memBits){}

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

    //Try to find the tag.
    int index = findTag(tag);

    if (index != -1 && isOccupied(index)){
        if (debug) cout << "\tHIT! Index is " << index << endl;

        //Update the hits counter and update the lru for the entry (and the counter too).
        hits++;
        cacheLinesLru.at(index).lru = (++counter);
    }

    else {
        if (debug) cout << "\tMISS!" << endl;

        //Put the tag in the first available spot.
        bool foundSpot = false;

        for (unsigned int i = 0; i < numLines; i++) {
            if (!cacheLinesLru.at(i).occupied) {
                if (debug) cout << "\tPlacing tag in index " << i << endl;
                this->cacheLinesLru.at(i).tag = tag;
                this->cacheLinesLru.at(i).occupied = true;
                this->cacheLinesLru.at(i).lru = (++counter);
                foundSpot = true;
                break;
            }
        }

        if(!foundSpot){
            if (debug) cout << "\tAll spots occupied! Replacing..." << endl;
            replacements++;

            if(lruCache) {
                unsigned int i = findLeastLRU(debug);

                if (debug) cout << "\tPlacing tag in index " << i << endl;
                this->cacheLinesLru.at(i).tag = tag;
                this->cacheLinesLru.at(i).occupied = true;
                this->cacheLinesLru.at(i).lru = (++counter);
            }
        }
    }
}

int FullyAssociative::findTag(unsigned int& tag){
    int index = -1;
    for (unsigned int i = 0; i < numLines; i++){
        if (cacheLinesLru[i].tag == tag){
            index = (int) i;
            break;
        }
    }

    return index;
}