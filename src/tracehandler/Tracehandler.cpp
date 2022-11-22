//
// Created by molyo on 11/20/2022.
//

#include "Tracehandler.h"

Tracehandler::Tracehandler(){

    cout << "Initializing Trace Handler..." << endl << endl;

    directory_iterator iter;

    try {
        cout << "Current Path: " << current_path().string() << endl << endl;
        iter = directory_iterator((path(string(DEFAULT_TRACE_DIR) )));
    }

    catch(const filesystem_error& error){
        cerr << "Default trace directory " << string(DEFAULT_TRACE_DIR) << " does not exist!" << endl;
        cerr << "Please create the directory, or specify files manually." << endl;
    }

    unsigned int rejectedFiles = 0;
    cout << "Added:" << endl;
    for (const directory_entry& i : iter){

        if (i.path().extension().string() == DEFAULT_TRACE_EXTENSION) {
            string fileName = i.path().filename().string();
            fileName = fileName.substr(0, fileName.find('.'));
            cout << "+ " << i.path().string() << " (" << fileName << ")" << endl;
            traceFiles.emplace(pair<string, directory_entry>(fileName, i));
        }

        else{
            rejectedFiles++;
        }
    }

    cout << endl << "==STARTUP SUMMARY==" << endl;
    cout << "Added: " << traceFiles.size() << " files." << endl;
    cout << "Rejected: " << rejectedFiles << " files." << endl << endl;
}

void Tracehandler::readFile(const string& traceName){
    //Find the directory entry for the file, if it exists.
    auto iter = traceFiles.find(traceName);

    if (iter == traceFiles.end()){
        cerr << traceName << " is not a valid imported file!" << endl;
        return;
    }

    //Pull the path and open an ifstream object with it.
    ifstream file(iter->second.path());

    if (file.is_open()){
        string currLine;
        while(getline(file, currLine)){
            //Remove all but the memory address value in the middle of the line & add it to a vector of memory addresses.
            currLine = currLine.substr(currLine.find('x') + 1);
            currLine = currLine.substr(0, currLine.find(' '));
            memAddresses.push_back(currLine);
        }
    }

    else{
        cerr << "Could not open file " << iter->second.path().string() << "!" << endl;
    }
}

const vector<string>& Tracehandler::getAddresses(){
    return memAddresses;
}