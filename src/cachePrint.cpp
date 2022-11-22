#include "cachePrint.h"

void debugReport(const Cache &cache){
    cout << "==CACHE REPORT==" << endl;
    cout << "Hits: " << cache.getHits() << endl;
    cout << "Misses: " << cache.getCounter() - cache.getHits() << endl;
    cout << "Replacements: " << cache.getReplacements() << endl;
    cout << "Total Requests: " << cache.getCounter() << endl;
}

void printCache(const Cache& cache){
    for (unsigned int i = 0; i < cache.getNumLines(); i++){
        cout << "Cache Line " << i << endl;
        cout << "\tTag: " << cache.getTag(i) << endl;
        cout << "\tSet: " << cache.getSet(i) << endl;
        cout << "\tLRU: " << cache.getLRUCount(i) << endl;
        cout << "\tOccupied: " << (cache.getLRUCount(i) != 0 ? "Y" : "N") << endl;
        cout << endl;
    }
}

void printCacheTable(const Cache& cache){
    printBorder();
    vector<string> headings = {"Index", "Set", "Tag", "LRU", "Occ"};
    printMid(headings);
    printBorder();

    for (unsigned int i = 0; i < cache.getNumLines(); i++){
        vector<string> data={
                    to_string(i),
                    to_string(cache.getSet(i)),
                    to_string(cache.getTag(i)),
                    to_string(cache.getLRUCount(i)),
                    (cache.getLRUCount(i) != 0 ? "Y" : "N")
        };

        printMid(data);
        printBorder();
    }

}

void printBorder(){
    cout << "+";

    for (unsigned int i = 0; i < 4; i++){
        cout << setw(widthUInt + 1) << setfill('-') << "+";
    }

    cout << setw(widthBool + 1) << setfill('-') << "+" << endl;
}

void printMid(const vector<string> &cellData){
    for (unsigned int i = 0; i < cellData.size() - 1; i++){
        cout << "|" << right << setw(widthUInt) << setfill(' ') << cellData.at(i);
    }

    cout << "|" << right << setw(widthBool) << setfill(' ') << cellData.at(cellData.size() - 1) << "|" << endl;

}