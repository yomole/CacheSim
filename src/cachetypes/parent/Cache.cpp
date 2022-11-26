#include "Cache.h"

Cache::Cache(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache,
             unsigned int memBits): numLines(cacheSize / blockSize), numSets(numLines / associativity) {

    //Initialize member variables.
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->associativity = associativity;
    this->memBits = memBits;
    this->offsetBits = (unsigned int) log2(blockSize);
    this->tagBits = this->memBits - this->offsetBits;
    this->lruCache = lruCache;
    this->counter = 0;
    this->replacements = 0;
    this->hits = 0;

    //Initialize the cache container.
    for (unsigned int s = 0; s < numSets; s++) {
        //Emplace an empty set containing the set number and an empty CacheLine vector.
        pair<unsigned int, list<CacheLine>> emptySet = {s, list<CacheLine>()};
        cacheLines.emplace(emptySet);

        for (unsigned int l = 0; l < associativity; l++) {
            //Push back an empty cache line per set line.
            try {
                cacheLines.at(s).emplace_back(CacheLine());
            }

            catch (out_of_range &out_of_range) {
                cerr << "Could not create LRU Cache!" << endl;
                cerr << out_of_range.what();
                exit(1);
            }
        }
    }
}

unsigned int Cache::getCacheSize() const{
    return cacheSize;
}

unsigned int Cache::getBlockSize() const{
    return blockSize;
}

unsigned int Cache::getAssociativity() const{
    return associativity;
}

unsigned int Cache::getNumLines() const{
    return numLines;
}

unsigned int Cache::getNumSets() const{
    return numSets;
}

unsigned int Cache::getOffsetBits() const{
    return offsetBits;
}

unsigned int Cache::getTagBits() const{
    return tagBits;
}

unsigned int Cache::getMemBits() const{
    return memBits;
}

unsigned int Cache::getHits() const{
    return hits;
}

unsigned int Cache::getReplacements() const{
    return replacements;
}

unsigned int Cache::getCounter() const{
    return counter;
}

unsigned int Cache::getTag(unsigned int set, unsigned int line) const{
    try {
        auto iter = cacheLines.at(set).begin();
        unsigned int i = 0;

        while (iter != cacheLines.at(set).end() && i != line) {
            iter++;
            i++;
        }

        return iter->tag;
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not get the tag of item in set " << set << ", line " << line << endl;
        cerr << out_of_range.what();
        return 0;
    }
}

unsigned int Cache::getLRUCount(unsigned int set, unsigned int line) const{
    try {
        auto iter = cacheLines.at(set).begin();
        unsigned int i = 0;

        while (iter != cacheLines.at(set).end() && i != line) {
            iter++;
            i++;
        }

        return iter->lru;
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not get the LRU counter of item in set " << set << ", line " << line << endl;
        cerr << out_of_range.what();
        return 0;
    }
}

bool Cache::isOccupied(unsigned int set, unsigned int line) const{
    try {
        auto iter = cacheLines.at(set).begin();
        unsigned int i = 0;

        while (iter != cacheLines.at(set).end() && i != line) {
            iter++;
            i++;
        }

        return iter->occupied;
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not get the occupation of item in set " << set << ", line " << line << endl;
        cerr << out_of_range.what();
        return true;
    }
}

void Cache::addLine(unsigned int set, unsigned int tag, bool debug) {
    try {
        bool foundSpot = false;
        unsigned int i = 0;

        //Put the tag in the first available spot.
        for (auto &iter: cacheLines.at(set)) {
            if (!iter.occupied) {
                if (debug) cout << "\tPlacing tag in index " << i << endl;

                iter.tag = tag;
                iter.occupied = true;
                iter.lru = (++counter);

                foundSpot = true;
                break;
            }
            i++;
        }

        if (!foundSpot) {
            if (debug) cout << "\tAll spots occupied! Replacing..." << endl;
            replacements++;

            if (lruCache) {
                replaceLeastLRU(set, tag, debug);
            } else {
                replaceFIFO(set, tag, debug);
            }
        }
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not add line to cache in set " << set << " with tag " << tag << endl;
        cerr << out_of_range.what();
    }
}

string Cache::hexToBinString(const char& hex){
    switch (hex) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a':
        case 'A': return "1010";
        case 'b':
        case 'B': return "1011";
        case 'c':
        case 'C': return "1100";
        case 'd':
        case 'D': return "1101";
        case 'e':
        case 'E': return "1110";
        case 'f':
        case 'F': return "1111";
        default:{
            cerr << "Invalid hex string " << hex << "!" << endl;
            return "0000";
        }
    }
}

unsigned int Cache::binStringToInt(const string& bin){
    unsigned int value = 0;
    for (unsigned int i = 0; i < bin.size(); i++){
            char bit = bin[bin.size() - 1 - i];
            value += atoi(&bit) * (unsigned int) pow(2, i);
    }
    return value;
}

void Cache::replaceLeastLRU(unsigned int set, unsigned int tag, bool debug){
    unsigned int line = 0, i = 0, leastLRU = UINT32_MAX;

    CacheLine* least;

    try {
        for (auto &iter: cacheLines.at(set)) {
            if (iter.lru < leastLRU) {
                leastLRU = iter.lru;
                line = i;
                least = &iter;
            }
            i++;
        }

        if (debug) {
            cout << "Smallest LRU in set " << set << " is " << leastLRU << " in line " << line << endl;
            cout << "Replacing..." << endl;
        }

        least->tag = tag;
        least->lru = ++counter;
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not replace the item in LRU cache set " << set << " with tag " << tag << endl;
        cerr << out_of_range.what();
    }
}

void Cache::replaceFIFO(unsigned int set, unsigned int tag, bool debug){
    try {
        //Get the list we need to replace in.
        list<CacheLine> &targetList = cacheLines.at(set);

        if (debug) cout << "Replaced line with tag " << targetList.front().tag << " (should be the oldest)." << endl;

        //Remove the front node (oldest).
        targetList.pop_front();

        //Add a new node in the front with the information we need.
        targetList.emplace_back(CacheLine(tag, ++counter, true));
    }

    catch (out_of_range& out_of_range){
        cerr << "Could not replace the item in FIFO cache set " << set << endl;
        cerr << out_of_range.what();
    }
}

void Cache::serialize(const std::string& csvFileName, bool overwrite){
    directory_entry dataFile((path(csvFileName)));

    //Check for a csv extension.
    if (dataFile.path().extension() != ".csv"){
        cerr << "Improper file extension! The file name needs to have a .csv extension!";
        exit(1);
    }

    fstream file;

    //check if the file exists. If not, make it.
    if (!dataFile.exists()){
        file.open(dataFile.path(), fstream::out);
        file.close();
    }

    //Open the file as an input stream to check the headings.
    if (overwrite){
        //Remove all content from the files.
        file.open(dataFile.path(), fstream::out | fstream::trunc);
        file.close();
    }

    //Basic open arguments.
    file.open(dataFile.path(), fstream::in);

    string line;
    if (file.is_open()){
        //Check to see if there are headings.
        getline(file, line);

        //Reopen the file as output appending to add the data and/or headings.
        file.close();
        file.open(dataFile.path(), fstream::out | fstream::app);

        if (line.empty()){
            //Make the headings.
            file << "cache_size,block_size,associativity,lru_fifo,num_lines,hits,misses,replacements,num_requests" << endl;
        }

        //Output the data for the current cache.
        file << cacheSize << "," << blockSize << "," << associativity << "," << (lruCache ? "lru" : "fifo") << "," <<
        numLines << "," << hits << "," << (counter - hits) << "," << replacements << "," << counter << endl;
    }

    else{
        cerr << "Could not open file " << dataFile.path().string() << "!" << endl;
    }
}