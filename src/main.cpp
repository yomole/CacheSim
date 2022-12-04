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
#include <map>
#include <vector>
#include <string>

#include "tracehandler/Tracehandler.h"
#include "cachePrint/cachePrint.h"
#include "cachetypes/SetAssociative.h"
#include "help/help.h"

//-----------------
// USING STATEMENTS
//-----------------

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::out_of_range;
using std::invalid_argument;
using std::exception;
using std::stoi;

//----------
// CONSTANTS
//----------
const string_view DEFAULT_DATA_DIR = "data/";

//----------------------
// FUNCTION DECLARATIONS
//----------------------

//Processes the arguments passed into the program.
map<Commands, vector<string>> processArgs(int argc, char* argv[]);

//Checks the processed arguments to see if valid simulations can be run.
bool validSims(map<Commands, vector<string>>& args);

//----------
// MAIN CODE
//----------

int main(int argc, char* argv[]){

    cout << endl;

    if (argc < 2){
        printHelp(NONE_CLI);
        exit(0);
    }

    else{
        Tracehandler tracehandler;
        map<Commands, vector<string>> processed = processArgs(argc, argv);

        //Test for the help command.
        if (processed.find(HELP) != processed.end()){
            try {
                if (processed.find(HELP)->second.empty()){
                    printHelp(NONE_CLI);
                }

                else {
                    printHelp(commandDictionary.at(processed.find(HELP)->second.at(0)));
                }
            }

            catch(out_of_range& out_of_range){
                cerr << "That command is not a valid command!" << endl;
            }
        }

        //Run the simulations if everything is set to do so.
        else if (validSims(processed)) {
            //Get the total number of simulations.
            unsigned int numSims = 1;

            for (auto& i : processed){
                if (i.second.size() != 0) {
                    numSims *= i.second.size();
                }
            }

            //Check if line by line mode was requested.
            bool lbl = (processed.find(LBL) != processed.end());
            bool lbltemp = lbl;
            bool silent = (processed.find(SILENT) != processed.end());
            string fileName = processed.find(EXPORT)->second.at(0);

            tracehandler.readFile(processed.find(SETFILE)->second.at(0));
            //Loop through all replacement types, cache sizes, block sizes, associativity, etc.
            unsigned int sim = 1, validsim = 0;
            for (const string &mb: processed.find(MEMORYBITS)->second) {
                for (const string &rp: processed.find(REPLACEMENT)->second) {
                    for (const string &cs: processed.find(CACHESIZE)->second) {
                        for (const string &bs: processed.find(BLOCKSIZE)->second) {
                            for(const string& as: processed.find(ASSOCIATIVITY)->second){
                                unsigned int membits;
                                unsigned int cacheSize;
                                unsigned int blockSize;
                                unsigned int associativity;
                                bool lruCache;
                                try {
                                    membits = stoi(mb);
                                    cacheSize = stoi(cs);
                                    blockSize = stoi(bs);
                                    associativity = stoi(as);
                                    lruCache = (rp == "lru");

                                    if (blockSize < 4){
                                        throw invalid_argument("Block size is smaller than 4 bytes!");
                                    }

                                    if (cacheSize < blockSize){
                                        throw invalid_argument("Number of lines would be smaller than 1!");
                                    }

                                    if ((cacheSize / blockSize) < associativity){
                                        throw invalid_argument("Number of sets would be smaller than 1!");
                                    }

                                    if (!silent) {
                                        cout << "(" << sim << "/" << numSims << ") RUNNING CacheSim simulation with:"
                                             << endl;
                                        cout << "\tMemory bits: " << mb << endl;
                                        cout << "\tLRU Cache: " << (lruCache ? "TRUE" : "FALSE") << endl;
                                        cout << "\tCache Size: " << cs << endl;
                                        cout << "\tBlock Size: " << bs << endl;
                                        cout << "\tAssociativity: " << as << endl;
                                        cout << "\tFile: " << processed.find(SETFILE)->second.at(0) << endl;
                                        cout << endl;
                                    }
                                    else{
                                        printf("Running...(%u/%u)\r", sim, numSims);
                                    }
                                }

                                catch (exception& exception){
                                    if (!silent) {
                                        cerr << "(" << sim << "/" << numSims << ") SKIPPING CacheSim simulation with:"
                                             << endl;
                                        cerr << "\tMemory bits: " << mb << endl;
                                        cerr << "\tLRU Cache: " << (lruCache ? "TRUE" : "FALSE") << endl;
                                        cerr << "\tCache Size: " << cs << endl;
                                        cerr << "\tBlock Size: " << bs << endl;
                                        cerr << "\tAssociativity: " << as << endl;
                                        cerr << "\tFile: " << processed.find(SETFILE)->second.at(0) << endl;
                                        cerr << endl;
                                        cerr << "Exception Details:" << endl;
                                        cerr << string(exception.what()) << endl;
                                        cerr << endl;
                                    }
                                    sim++;
                                    continue;
                                }

                                SetAssociative testingCache(cacheSize, blockSize, associativity, lruCache, membits);

                                unsigned int count = 1;
                                string input, prevInput = "nr";
                                bool debug = false;
                                for (const string& i : tracehandler.getAddresses()) {
                                    //Process any line by line commands, if the mode is active.
                                    if (lbltemp && !silent){
                                        do {
                                            debug = true;
                                            getline(cin, input);

                                            //If enter is pressed with no string, use the previous input.
                                            if (input.empty()) {
                                                input = prevInput;
                                            }

                                            if (input == "l") {
                                                printAllLBL();
                                            } else if (input == "t") {
                                                printCacheTable(testingCache);
                                            } else if (input == "su") {
                                                debugReport(testingCache);
                                            } else if (input == "ns") {
                                                lbltemp = false;
                                                debug = false;
                                            } else if (input == "q") {
                                                lbl = false;
                                                lbltemp = false;
                                                debug = false;
                                            }

                                            //Keep a record of the input passed in.
                                            prevInput = input;
                                        }while(input != "nr" && input != "ns" && input != "q");
                                    }

                                    testingCache.processRequest(i, debug);
                                }

                                if (!silent) {
                                    cout << endl;
                                }

                                testingCache.serialize(string(DEFAULT_DATA_DIR) + fileName);
                                sim++;
                                validsim++;

                                lbltemp = lbl;
                            }
                        }
                    }
                }
            }

            cout << "==SIMULATION SUMMARY==" << endl;
            cout << "Simulations Executed: " << validsim << endl;
            cout << "Simulations Rejected: " << numSims - validsim << endl;
        }
    }
    return 0;
}

//---------------------
// FUNCTION DEFINITIONS
//---------------------
map<Commands, vector<string>> processArgs(int argc, char* argv[]){
    map<Commands, vector<string>> processed;
    unsigned int notProcessed = 0;

    for(unsigned int i = 1; i < argc; i++){
        string arg = string(argv[i]);

        if (arg.find('-') == string::npos){
            //Ignore any arguments that do not start with '-'.
            notProcessed++;
            continue;
        }

        //Get the command associated with the input.
        Commands first;
        try {
            first = commandDictionary.at(((arg.find('=') != string::npos) ?
                                          arg.substr(arg.find('-') + 1, arg.find('=') - arg.find('-') - 1) :
                                          arg.substr(arg.find('-') + 1)));
        }

        catch(out_of_range& out_of_range){
            notProcessed++;
            continue;
        }

        //Remove all but the remaining values for the argument/commands (if any).
        if (arg.find('=') != string::npos) {
            arg = arg.substr(arg.find('=') + 1);

            vector<string> values;
            while(arg.find(',') != string::npos){
                //Isolate each comma separated value for variables.
                values.push_back(arg.substr(0, arg.find(',')));
                arg = arg.substr(arg.find(',') + 1);
            }

            //Place the last value without a terminating comma in the values vector.
            values.push_back(arg);

            //Put the command with the generated vector in the processed map.
            processed.emplace(pair<Commands, vector<string>>(first, values));
        }

        else{
            //Put the command with an empty vector in the processed map.
            processed.emplace(pair<Commands, vector<string>>(first, vector<string>()));
        }
    }

    if (notProcessed > 0) {
        cerr << notProcessed << " command" << (notProcessed > 1 ? "s" : "") <<
        " had improper formatting and " << (notProcessed > 1 ? "were" : "was") << " ignored." << endl;
    }

    return processed;
}

bool validSims(map<Commands, vector<string>>& args){
    //Check if at least one replacement mode has been specified.
    if (args.find(REPLACEMENT) == args.end()){
        cerr << "There is/are no replacement type(s) specified!" << endl;
        return false;
    }

    //Check if at least one cache size has been specified.
    if (args.find(CACHESIZE) == args.end()){
        cerr << "There is/are no cache size(s) specified!" << endl;
        return false;
    }

    //Check if at least one block size has been specified.
    if (args.find(BLOCKSIZE) == args.end()){
        cerr << "There is/are no block size(s) specified!" << endl;
        return false;
    }

    //Check if at least one associativity has been specified.
    if (args.find(ASSOCIATIVITY) == args.end()){
        cerr << "There is/are no associativity(s) specified!" << endl;
        return false;
    }

    if (args.find(SETFILE) == args.end()){
        cerr << "There is/are no file(s) specified!" << endl;
        return false;
    }

    if (args.find(EXPORT) == args.end()){
        cerr << "There is no output file name specified!" << endl;
        return false;
    }

    if (args.find(MEMORYBITS) == args.end()){
        cerr << "There is/are no memory bit(s) specified!" << endl;
        cout << "Running the simulation(s) with " << MEMBITS << " memory bits." << endl;
        //Add the default memory bits.
        vector<string> value = {to_string(MEMBITS)};
        args.emplace(MEMORYBITS, value);
    }

    return true;
}
