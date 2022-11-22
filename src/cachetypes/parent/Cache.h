/*
 * File Name: Cache.h
 * Author: Yovany Molina
 * Date: 18/11/22
 *
 * Description: A parent class for the types of caches used in CacheSim.
 */

//----------
// INCLUDES
//----------

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <filesystem>
#include <fstream>

//-----------------
// USING STATEMENTS
//-----------------
namespace fs = std::filesystem;

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::stoi;
using std::pow;
using std::vector;
using std::queue;
using std::fstream;

using fs::directory_entry;
using fs::directory_iterator;
using fs::path;
using fs::current_path;
using fs::filesystem_error;

#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H

class Cache {

protected:

    unsigned int cacheSize{};
    unsigned int blockSize{};
    unsigned int associativity{};

    const unsigned int numLines = 0;

    unsigned int offsetBits{};
    unsigned int tagBits{};
    unsigned int memBits{};

    unsigned int hits{};
    unsigned int replacements{};
    unsigned int counter{};

    bool lruCache;

    struct CacheLine{
        unsigned int set = 0;
        unsigned int tag = 0;
        unsigned int lru = 0;
        bool occupied = false;
    };

    vector<CacheLine> cacheLinesLru;
    queue<CacheLine> cacheLinesFifo;

public:

    explicit Cache(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache = true,
                   unsigned int memBits = 32);

    //Getters:
    unsigned int getCacheSize() const;
    unsigned int getBlockSize() const;
    unsigned int getAssociativity() const;
    unsigned int getNumLines() const;
    unsigned int getOffsetBits() const;
    unsigned int getTagBits() const;
    unsigned int getMemBits() const;
    unsigned int getHits() const;
    unsigned int getReplacements() const;
    unsigned int getCounter() const;
    unsigned int getTag(unsigned int index) const;
    unsigned int getSet(unsigned int index) const;
    unsigned int getLRUCount(unsigned int index) const;
    bool isOccupied(unsigned int index) const;

    //Class Functions:

    //Processes a memory request.
    virtual void processRequest(const string& memAddress, bool debug = false) = 0;

    //Converts a hex string to a binary string.
    static string hexToBinString(const char& hex);

    //Converts a binary string into an integer.
    static unsigned int binStringToInt(const string& bin);

    //Returns the index of the smallest LRU cache line.
    unsigned int findLeastLRU(bool debug = false) const;

    //Exports the cache data to a csv file.
    void serialize(const string& csvFileName, bool overwrite = false);
};

#endif //CACHESIM_CACHE_H