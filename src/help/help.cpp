#include "help.h"

void printHelp(Commands command){
    if (command != NONE_CLI && command != NONE_LBL) {
        printHelpHeader(command);
    }

    switch(command){
        case HELP:{
            cout << "\tDisplays information about a command or a list of commands." << endl;
            cout << "\t\t\tStructures: -h=[command] ; -h" << endl;
            break;
        }
        case SETFILE:{
            cout << "\tSets the trace file to use for the simulation. The trace file must have been loaded by TraceHandler." << endl;
            cout << "\t\t\tIf a file is not loaded at the start, place it in the traces file and restart the program." << endl;
            cout << "\t\t\tStructures: -sf=\"[file name]\"" << endl;

            break;
        }

        case LBL:{
            cout << "\t\tRuns the simulation in line by line mode." << endl;
            cout << "\t\t\tLine by line mode has a similar interface to gdb. Enter \'h\' during the simulation for commands." << endl;
            break;
        }

        case SILENT:{
            cout << "\tRuns the simulation with no CLI output." << endl;
            cout << "\t\t\tThis flag overrides line by line mode." << endl;
            break;
        }

        case ASSOCIATIVITY: {
            cout << "\t\tSets the associativity for the simulation." << endl;
            cout << "\t\t\tStructures: -as=4 ; -as=1,2,4,8" << endl;
            break;
        }

        case BLOCKSIZE:{
            cout << "\tSets the block size for the simulation (in bytes)." << endl;
            cout << "\t\t\tStructures: -bs=512 ; -bs=4,8,16,32,64,128" << endl;
            break;
        }

        case CACHESIZE:{
            cout << "\tSets the cache size for the simulation (in bytes)." << endl;
            cout << "\t\t\tStructures: -cs=512 ; -cs=4,8,16,32,64,128" << endl;
            break;
        }

        case REPLACEMENT:{
            cout << "\tSets the replacement strategy used for the simulation." << endl;
            cout << "\t\t\tStructures: -rp=fifo ; -rp=fifo,lru" << endl;
            break;
        }

        case MEMORYBITS:{
            cout << "\tSets the memory bits for the simulation." << endl;
            cout << "\t\t\tThis is an OPTIONAL argument. The simulation runs with a default 32 bit memory." << endl;
            cout << "\t\t\tStructures: -mb=32" << endl;
            break;
        }

        case EXPORT:{
            cout << "\tSets the name for the data csv to export." << endl;
            cout << "\t\t\tIf it has the same name as another file, the data will be appended to that file." << endl;
            cout << "\t\t\tStructures: -e=\"[file_name_no_spaces.csv]\"" << endl;
            break;
        }

        case NONE_CLI:{
            printAll();
            break;
        }

        case LIST:{
            cout << "\tDisplays all of the line by line commands." << endl;
            break;
        }

        case NEXT:{
            cout << "\tProceeds to the next memory request." << endl;
            break;
        }

        case TABLE:{
            cout << "\tPrints the cache in a table format." << endl;
            break;
        }

        case SUMMARY:{
            cout << "\tPrints the number of hits, misses, replacements, and requests." << endl;
            break;
        }

        case NEXTSIM:{
            cout << "\tSkips until the next valid simulation." << endl;
            break;
        }

        case END:{
            cout << "\tSkips until the end of all simulations." << endl;
            break;
        }

        case NONE_LBL:{
            printAllLBL();
            break;
        }
    }

    cout << endl;
}

void printHelpHeader(Commands command){
    vector<string> commandStrings = findCommandString(command);

    cout << "\t";

    for (unsigned int i = 0; i < commandStrings.size(); i++){
        cout << (command <= NONE_CLI ? "-" : "") <<
        (i + 1 < commandStrings.size() ? commandStrings.at(i) + " , " : commandStrings.at(i));
    }
}

void printAll(){
    cout << "CacheSim Application V. " << VERSION << endl << endl;
    cout << "Options:" << endl;
    for (int i = HELP; i != NONE_CLI; i++){
        printHelp(static_cast<Commands>(i));
    }
}

void printAllLBL(){
    cout << "Line by Line Options:" << endl;
    for (int i = LIST; i != NONE_LBL; i++){
        printHelp(static_cast<Commands>(i));
    }
}

vector<string> findCommandString(Commands command){
    vector<string> strings;

    for (const auto& i : commandDictionary){
        if (i.second == command){
            strings.push_back(i.first);
        }
    }

    return strings;
}