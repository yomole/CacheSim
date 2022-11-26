#include "cachePrint.h"

void debugReport(const Cache &cache){
    cout << endl << "==CACHE REPORT==" << endl;
    cout << "Hits: " << cache.getHits() << endl;
    cout << "Misses: " << cache.getCounter() - cache.getHits() << endl;
    cout << "Replacements: " << cache.getReplacements() << endl;
    cout << "Total Requests: " << cache.getCounter() << endl;
    cout << endl;
}

void printCacheTable(const Cache& cache){
    printBorder();
    vector<string> headings = {"Set", "Tag", "LRU", "Occ"};
    printMid(headings);
    printBorder();

    for (unsigned int s = 0; s < cache.getNumSets(); s++){
        for (unsigned int l = 0; l < cache.getAssociativity(); l++){
            vector<string> data={
                    to_string(s),
                    to_string(cache.getTag(s, l)),
                    to_string(cache.getLRUCount(s, l)),
                    (cache.getLRUCount(s, l) != 0 ? "Y" : "N")
            };

            printMid(data);
            printBorder();
        }
    }
}

void printBorder(){
    cout << "+";

    for (unsigned int i = 0; i < 3; i++){
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