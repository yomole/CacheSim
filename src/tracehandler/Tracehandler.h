/*
 * File Name: Tracehandler.h
 * Author: Yovany Molina
 * Date: 20/11/22
 *
 * Description: A class used to manage trace files.
 */

//----------
// INCLUDES
//----------

#include <vector>
#include <experimental/filesystem>
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

//-----------------
// USING STATEMENTS
//-----------------

namespace fs = std::experimental::filesystem;

using std::vector;
using std::string;
using std::string_view;
using std::cout;
using std::endl;
using std::cerr;
using std::unordered_map;
using std::pair;
using std::find;
using std::ifstream;
using std::iterator;
using std::getline;

using fs::directory_entry;
using fs::directory_iterator;
using fs::path;
using fs::current_path;
using fs::filesystem_error;

//----------
// CONSTANTS
//----------
static const string_view DEFAULT_TRACE_DIR = "traces/";
static const string_view DEFAULT_TRACE_EXTENSION = ".trace";

#ifndef CACHESIM_TRACEHANDLER_H
#define CACHESIM_TRACEHANDLER_H

class Tracehandler {
    unordered_map<string, directory_entry> traceFiles; //Holds names and locations of trace files.

    vector<string> memAddresses;

public:

    Tracehandler();

    void readFile(const string& traceName);

    const vector<string>& getAddresses();
};

#endif //CACHESIM_TRACEHANDLER_H
