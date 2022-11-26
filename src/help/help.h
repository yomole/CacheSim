/*
 * File Name: FullyAssociative.h
 * Author: Yovany Molina
 * Date: 22/11/22
 *
 * Description: Functions to help with CLI.
 */

//----------
// INCLUDES
//----------
#include <iostream>
#include <iomanip>
#include <ios>
#include <map>
#include <string>
#include <vector>

//-----------------
// USING STATEMENTS
//-----------------
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::setfill;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::string_view;

//----------
// CONSTANTS
//----------
const string_view VERSION = "1.0.0";

//-------------
// ENUMERATIONS
//-------------
enum Commands{
    HELP,
    SETFILE,
    LBL,
    SILENT,
    ASSOCIATIVITY,
    BLOCKSIZE,
    CACHESIZE,
    REPLACEMENT,
    MEMORYBITS,
    EXPORT,
    NONE_CLI,
    LIST,
    NEXT,
    TABLE,
    SUMMARY,
    NEXTSIM,
    END,
    NONE_LBL,
};

enum LblCommands{

};

static map <string, Commands> commandDictionary = {
    pair<string, Commands>("h", HELP),
    pair<string, Commands>("help", HELP),

    pair<string, Commands>("sf", SETFILE),
    pair<string, Commands>("setfile", SETFILE),

    pair<string, Commands>("lbl", LBL),

    pair<string, Commands>("s", SILENT),
    pair<string, Commands>("silent", SILENT),

    pair<string, Commands>("as", ASSOCIATIVITY),

    pair<string, Commands>("bs", BLOCKSIZE),
    pair<string, Commands>("block", BLOCKSIZE),

    pair<string, Commands>("cs", CACHESIZE),
    pair<string, Commands>("cache", CACHESIZE),

    pair<string, Commands>("rp", REPLACEMENT),
    pair<string, Commands>("method", REPLACEMENT),

    pair<string, Commands>("mb", MEMORYBITS),
    pair<string, Commands>("memory", MEMORYBITS),

    pair<string, Commands>("e", EXPORT),
    pair<string, Commands>("export", EXPORT),

    pair<string, Commands>("l", LIST),
    pair<string, Commands>("nr", NEXT),
    pair<string, Commands>("t", TABLE),
    pair<string, Commands>("su", SUMMARY),
    pair<string, Commands>("ns", NEXTSIM),
    pair<string, Commands>("q", END),

};

//----------------------
// FUNCTION DECLARATIONS
//----------------------

//Prints help info for a specific command or prints all commands.
void printHelp(Commands command);

//Prints info about a CLI command used in line by line mode.
void printHelpLBL(LblCommands command);

//Prints the header of a command (nice CLI formatting).
void printHelpHeader(Commands command);

//Prints all arguments/commands and their info.
void printAll();

//Prints all CLI commands associated with line by line mode.
void printAllLBL();

//Finds the user input string that would yield a command.
vector<string> findCommandString(Commands command);

#ifndef CACHESIM_HELP_H
#define CACHESIM_HELP_H








#endif //CACHESIM_HELP_H
