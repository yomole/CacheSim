/*
 * File Name: main.cpp
 * Author: Yovany Molina
 * Date: 18/11/22
 *
 * Description: The main file for the CacheSim project.
 */

//----------
// INCLUDES
//----------

#include <iostream>
#include "cachetypes/FullyAssociative.h"
#include "tracehandler/Tracehandler.h"
#include "cachePrint.h"

//-----------------
// USING STATEMENTS
//-----------------

using std::cout;
using std::cin;
using std::endl;
using std::getline;

//----------
// CONSTANTS
//----------
const string_view DEFAULT_DATA_DIR = "../data/";

//----------------------
// FUNCTION DECLARATIONS
//----------------------

//----------
// MAIN CODE
//----------

int main(){
    Tracehandler tracehandler;
    tracehandler.readFile("swim");

    for (unsigned int i = 2; i < 9; i++){
        FullyAssociative test(512, (unsigned int) pow(2,i));
        for (const string& i : tracehandler.getAddresses()){
            test.processRequest(i);

            //printCacheTable(test);
            //getline(cin, input);
        }

        test.serialize(string(DEFAULT_DATA_DIR) + "test.csv");
    }

    //debugReport(test);
    //printCache(test);

    //printCacheTable(test);
    //debugReport(test);

    return 0;
}

//---------------------
// FUNCTION DEFINITIONS
//---------------------

