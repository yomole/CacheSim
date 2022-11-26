/*
 * File Name: FullyAssociative.h
 * Author: Yovany Molina
 * Date: 22/11/22
 *
 * Description: A class for the set associative cache organization method in CacheSim.
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
using std::out_of_range;

#ifndef CACHESIM_SETASSOCIATIVE_H
#define CACHESIM_SETASSOCIATIVE_H

class SetAssociative : public Cache{
public:

    SetAssociative(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache = true,
                     unsigned int memBits = 32);

    //Class Functions:
    void processRequest(const string& memAddress, bool debug) override;
};

#endif //CACHESIM_SETASSOCIATIVE_H
