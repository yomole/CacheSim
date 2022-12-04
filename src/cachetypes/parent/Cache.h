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
#include <list>
#include <map>
#include <experimental/filesystem>
#include <fstream>

//-----------------
// USING STATEMENTS
//-----------------
namespace fs = std::experimental::filesystem;

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::stoi;
using std::pow;
using std::list;
using std::fstream;
using std::map;
using std::iterator;
using std::pair;
using std::exception;
using std::out_of_range;

using fs::directory_entry;
using fs::directory_iterator;
using fs::path;
using fs::current_path;
using fs::filesystem_error;

#ifndef CACHESIM_CACHE_H
#define CACHESIM_CACHE_H

//----------
// CONSTANTS
//----------
const unsigned int MEMBITS = 32;

class Cache {

protected:

    unsigned int cacheSize{};
    unsigned int blockSize{};
    unsigned int associativity{};

    const unsigned int numLines = 0;
    const unsigned int numSets = 0;

    unsigned int offsetBits{};
    unsigned int setBits{};
    unsigned int tagBits{};
    unsigned int memBits{};

    unsigned int hits{};
    unsigned int replacements{};
    unsigned int counter{};

    bool lruCache;

    struct CacheLine{
        unsigned int tag;
        unsigned int lru;
        bool occupied;

        CacheLine(){
            tag = 0;
            lru = 0;
            occupied = false;
        }

        CacheLine(unsigned int tag, unsigned int lru, bool occupied){
            this->tag = tag;
            this->lru = lru;
            this->occupied = occupied;
        }
    };

    map<unsigned int, list<CacheLine>> cacheLines;

    //Checks to see if a tag exists in a set. Returns a reference to the iterator if successful. otherwise, end iterator.
    list<CacheLine>::iterator tagExists(unsigned int set, unsigned int &tag){
        for (auto iter = cacheLines.at(set).begin(); iter != cacheLines.at(set).end(); iter++){
            if (iter->tag == tag && iter->occupied){
                return iter;
            }
        }
        return cacheLines.at(set).end();
    }

public:

    Cache(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache = true,
          unsigned int memBits = 32);

    //Getters:

    unsigned int getCacheSize() const;
    unsigned int getBlockSize() const;
    unsigned int getAssociativity() const;
    unsigned int getNumLines() const;
    unsigned int getNumSets() const;
    unsigned int getOffsetBits() const;
    unsigned int getSetBits() const;
    unsigned int getTagBits() const;
    unsigned int getMemBits() const;
    unsigned int getHits() const;
    unsigned int getReplacements() const;
    unsigned int getCounter() const;

    unsigned int getTag(unsigned int set, unsigned int line) const;
    unsigned int getLRUCount(unsigned int set, unsigned int line) const;
    bool isOccupied(unsigned int set, unsigned int line) const;

    //Class Functions:

    //Processes a memory request.
    virtual void processRequest(const string& memAddress, bool debug) = 0;

    //Adds a line to the cache.
    void addLine(unsigned int set, unsigned int tag, bool debug = false);

    //Converts a hex string to a binary string.
    static string hexToBinString(const char& hex);

    //Converts a binary string into an integer.
    static unsigned int binStringToInt(const string& bin);

    //Replaces the cache line in a set with the smallest lru.
    void replaceLeastLRU(unsigned int set, unsigned int tag, bool debug = false);

    //Replaces the oldest cache line.
    void replaceFIFO(unsigned int set, unsigned int tag, bool debug = false);

    //Exports the cache data to a csv file.
    void serialize(const string& csvFileName, bool overwrite = false);
};

#endif //CACHESIM_CACHE_H