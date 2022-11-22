#include "Cache.h"

Cache::Cache(unsigned int cacheSize, unsigned int blockSize, unsigned int associativity, bool lruCache,
             unsigned int memBits): numLines(cacheSize / blockSize){

    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->associativity = associativity;

    cacheLinesLru.resize(numLines);

    this->memBits = memBits;
    this->offsetBits = (unsigned int) log2(blockSize);
    this->tagBits = this->memBits - this->offsetBits;

    this->lruCache = lruCache;

    //Initialize all lines' sets to 0.
    for (CacheLine i : cacheLinesLru){
        i.set = 0;
        i.tag = 0;
        i.lru = 0;
        i.occupied = false;
    }

    this->counter = 0;
    this->replacements = 0;
    this->hits = 0;
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

unsigned int Cache::getLRUCount(unsigned int index) const{
    return cacheLinesLru.at(index).lru;
}

unsigned int Cache::getTag(unsigned int index) const{
    return cacheLinesLru.at(index).tag;
}

unsigned int Cache::getSet(unsigned int index) const{
    return cacheLinesLru.at(index).set;
}

bool Cache::isOccupied(unsigned int index) const{
    return cacheLinesLru.at(index).occupied;
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

unsigned int Cache::findLeastLRU(bool debug) const{
    unsigned int index = 0;
    unsigned int leastLRU = UINT32_MAX;

    for (unsigned int i = 0; i < numLines; i++){
        if (cacheLinesLru.at(i).lru < leastLRU){
            leastLRU = cacheLinesLru.at(i).lru;
            index = i;
        }
    }

    if (debug) cout << "Smallest LRU is " << leastLRU << " in index " << index << endl;

    return index;
}

void Cache::serialize(const std::string& csvFileName, bool overwrite){
    directory_entry dataFile((path(csvFileName)));

    //Check for a csv extension.
    if (dataFile.path().extension() != ".csv"){
        cerr << "Improper file extension! The file name needs to have a .csv extension!";
        return;
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