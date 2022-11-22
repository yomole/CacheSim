/*
 * File Name: FullyAssociative.h
 * Author: Yovany Molina
 * Date: 19/11/22
 *
 * Description: A class for the fully associative cache organization method in CacheSim.
 */

//----------
// INCLUDES
//----------

#include <cmath>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>

#include "parent/Cache.h"

//-----------------
// USING STATEMENTS
//-----------------

using std::pow;
using std::string;
using std::istringstream;
using std::cout;
using std::endl;
using std::cerr;

#ifndef CACHESIM_FULLYASSOCIATIVE_H
#define CACHESIM_FULLYASSOCIATIVE_H

class FullyAssociative : public Cache{
public:

    FullyAssociative(unsigned int cacheSize, unsigned int blockSize, bool lruCache = true,
                     unsigned int memBits = 32);

    //Class Functions:
    void processRequest(const string& memAddress, bool debug = false) override;

    //Finds a specific tag in the cache. Returns the index (-1 if not found).
    int findTag(unsigned int& tag);

};

#endif //CACHESIM_FULLYASSOCIATIVE_H
