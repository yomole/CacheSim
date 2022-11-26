/*
 * File Name: cachePrint.h
 * Author: Yovany Molina
 * Date: 21/11/22
 *
 * Description: Functions for making cache prettytables and exporting cache results.
 */

//----------
// INCLUDES
//----------

#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include "parent/Cache.h"

//-----------------
// USING STATEMENTS
//-----------------

using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::right;
using std::string;
using std::to_string;
using std::vector;

//----------
// CONSTANTS
//----------

//Maximum width of an unsigned integer as a string.
const int widthUInt = 10;

//Maximum width of a bool as a string.
const int widthBool = 3;

#ifndef CACHESIM_CACHEPRINT_H
#define CACHESIM_CACHEPRINT_H

//----------------------
// FUNCTION DECLARATIONS
//----------------------

//Reports the hits/misses and calculates the hit, miss ratio.
void debugReport(const Cache &cache);

//Prints all the lines in the cache in table form.
void printCacheTable(const Cache& cache);

//Prints the line between numbers.
void printBorder();

//Prints the cells.
void printMid(const vector<string> &cellData);

#endif //CACHESIM_CACHEPRINT_H
