/*
 * File Name: test.cpp
 * Author: Yovany Molina
 * Date: 20/11/22
 *
 * Description: File containing test cases for the CacheSim project.
 */

#define CATCH_CONFIG_MAIN

//----------
// INCLUDES
//----------
#include <cmath>

#include "catch.h"
#include "../cachetypes/FullyAssociative.h"

//-----------------
// USING STATEMENTS
//-----------------
using std::log;

TEST_CASE("Create Fully Associative I", "[setup]"){
    unsigned int membits = log2(64);
    unsigned int blockbits = log2(4);
    unsigned int cachebits = log2(16);

    FullyAssociative test(membits, blockbits, cachebits);

    REQUIRE(test.getTagBits() == 4);
    REQUIRE(test.getOffsetBits() == 2);
}

TEST_CASE("Create Fully Associative II", "[setup]"){
    unsigned int membits = 28;
    unsigned int blockbits = 5;
    unsigned int cachebits = 8;

    FullyAssociative test(membits, blockbits, cachebits);

    REQUIRE(test.getTagBits() == 23);
    REQUIRE(test.getOffsetBits() == 5);
}

TEST_CASE("Create/Copy Fully Associative I", "[setup]"){
    unsigned int membits = 28;
    unsigned int blockbits = 5;
    unsigned int cachebits = 8;

    FullyAssociative test(membits, blockbits, cachebits);

    FullyAssociative test2(test);

    REQUIRE(test2.getTagBits() == 23);
    REQUIRE(test2.getOffsetBits() == 5);
}

TEST_CASE("Create/Copy Fully Associative II", "[setup]"){
    unsigned int membits = 28;
    unsigned int blockbits = 5;
    unsigned int cachebits = 8;

    FullyAssociative test(membits, blockbits, cachebits);

    FullyAssociative test2 = test;

    REQUIRE(test2.getTagBits() == 23);
    REQUIRE(test2.getOffsetBits() == 5);
}