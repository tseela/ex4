#include "CacheManager.hpp"

using namespace std;
using namespace solver::cache;

solver::cache::CacheManager::CacheManager() {}

/**
 * @brief throws an error if the user added a file named like our cache file.
 * if the cache file does not exist the function creates a new one.
 */
void checkCacheFileExists() {
    //make the dir cache
    if (!std::filesystem::exists(CacheManager::CACHE_DIR) && mkdir(CacheManager::CACHE_DIR, 0777) < 0) {
        throw system_error{errno, system_category()};
    }
    //make the dir for the cache files
    if (!std::filesystem::exists(CacheManager::CACHE_FILES_DIR) && mkdir(CacheManager::CACHE_FILES_DIR, 0777) < 0) {
        throw system_error{errno, system_category()};
    }
    // opening the cache file
    auto cachefd = 0;
    if (!std::filesystem::exists(CacheManager::CACHE_FILE)) {
        cachefd = open(CacheManager::CACHE_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if (cachefd < 0) {
            throw system_error{errno, system_category()};
        }
    }

    // to specify that we are in our cache manager file we make sure that the folowing line in the first one
    // or the file is empty (and we will write the line)
    char cacheID[CacheManager::CACHE_LINE_LENGTH + 1];
    cacheID[CacheManager::CACHE_LINE_LENGTH] = '\0';

    int errorID = read(cachefd, cacheID, CacheManager::CACHE_LINE_LENGTH);
    if (errorID == 0) { // empty file
        int errorWriting = write(cachefd, CacheManager::CACHE_LINE, 
            CacheManager::CACHE_LINE_LENGTH);
        if (errorWriting < 0) {
          close(cachefd);
          throw system_error{errno, system_category()}; 
        }
    } else if (errorID > 0 && (strcmp(cacheID, CacheManager::CACHE_LINE) != 0)) { // the file does not start with our line
        close(cachefd);
        throw runtime_error("A file named 'Cache__DONT_TOUCH_THIS_FILE.txt' which is not a cache manager allready exists. Changed it's name and run the program again.");
    } else if (errorID < 0) { // a system error
        close(cachefd);
        throw system_error{errno, system_category()};
    }
    close(cachefd);
}

/**
 * @brief Creates a Beckup File.
 * for an operation.
 * 
 * @param command the command to make beckup file for.
 * @param index the index of the beckup file.
 */
void createBeckupFile(const Operation& command, unsigned int index) {
    //gets the files name.
    string fileName = "src/bin/cache/files/" + std::to_string(index) + "." + command.getOutputFileType();

    //opening (& creating if needed) the file.
    const auto cachefd = open(fileName.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (cachefd < 0) {
        throw system_error{errno, system_category()};
    }

    //try to write the beckupfile.
    try {
        command.writeToFile(fileName);
    } catch(const exception& e) {
        close(cachefd);
        throw e;
    }

    close(cachefd);
}

/**
 * @brief Get the Cash File Index for the beckup file.
 * 
 * @return uint32_t the index for the beckup file.
 */
uint32_t getCashFileIndex() {
    //opens the catche file
    ifstream cacheFile;
    cacheFile.open(CacheManager::CACHE_FILE);
    if (cacheFile.fail()) {
        throw std::system_error(errno, system_category());
    }

    //helping varible
    string line;

    //if not operation was done yet
    getline(cacheFile, line); //the title
    if (cacheFile.peek() == std::ifstream::traits_type::eof()) {
        cacheFile.close();
        return 0;
    }

    //gets the next index
    getline(cacheFile, line);
    cacheFile.close();
    return std::stoi(line.substr(line.find("|") + 1)) + 1;
}

void solver::cache::CacheManager::saveInCache(const Operation& command, bool isSearched /*= false*/, bool isClear /*= false*/) const {
    //chcking if the catch file exists & creating it if neede.
    checkCacheFileExists();

    //if clear operation
    if (isClear) {
        if (!std::filesystem::remove_all(CACHE_DIR)) {
            throw system_error(errno, system_category());
        }
        return;
    }

    //if search operation
    if (isSearched) {
        string search = this->search(command);
        if (search == "") {
             cout << "result wasn't found in cache" << endl;
        } else {
            cout << "result found in cache – saved on " << search.substr(0, CurrentTime::TIME_STRING_LENGTH) << endl;
        }
        return;
    }

    // searching for the operatin in the cache file. 
    string result = search(command);

    // if we found the command
    if (result.compare("") != 0) {
        // first we will find the cache file that suits the operation
        string replace, fileName;
        unsigned int index = stoi(result.substr(result.find_last_of('|') + 1));

        // changing the time & date
        CurrentTime ct = CurrentTime();
        replace = ct.getTime() + '|' + std::to_string(index);

        // replace the date (the whole line) in the cache file
        string cache = files::readFileContent(CACHE_FILE);
        cache.replace(cache.find(result), result.size(), replace);
        files::writeFileContent(CACHE_FILE, cache);

        return;
    }

    // if the operation not in cache file:

    // writes the operation line into the cache file
    string cacheCopy = "";
    if (!isSearched) {
        cacheCopy += files::readFileContent(CACHE_FILE);
        cacheCopy.erase(0, CACHE_LINE_LENGTH);
        string cache = CACHE_LINE + command.getCacheString();
        //adding the time & date
        cache += ",";
        CurrentTime ct = CurrentTime();
        cache += ct.getTime();

        //adding the beckup file.
        unsigned int index = getCashFileIndex();
        cache += "|" + std::to_string(index);
        cache += "\n";//end of line

        //adding the other cache
        cache += cacheCopy;

        files::writeFileContent(CACHE_FILE, cache);

        createBeckupFile(command, index);
    }
}

string solver::cache::CacheManager::search(const Operation& command) const {   
    //opens the catch file 
    ifstream cacheFile;
    cacheFile.open(CACHE_FILE);
    if (cacheFile.fail()) {
        throw std::system_error(errno, system_category());
    }

    string line, operationLine;
    operationLine = command.getCacheString();

    // checks if every begining of a line is similar to the CacheString of the operation
    // if it finds the similar one it will return something to print
    int lastToCompare = operationLine.find_last_of(',') - 1;
    getline(cacheFile, line); //the title
    while (getline(cacheFile, line)) {
        if (line.substr(0, line.find(',')).compare(operationLine.substr(0, lastToCompare)) == 0) {
            cacheFile.close();
            return line.substr(line.find(',') + 1);
        }
    }

    cacheFile.close();
    return ""; //didn't find
}

string solver::cache::CacheManager::getBackUpFile(const Operation& command) const {
    string result = search(command);
    if (result.compare("") == 0) {
        return "";
    }
    return CACHE_FILES_DIR_ + result.substr(result.find_last_of('|') + 1) + '.' + command.getOutputFileType();
}

bool solver::cache::CacheManager::isSearch(int argc, const char* argv[]) {
    // to few arguments
    if (argc < 3) {
        return false;
    }
    return strcmp(argv[0], "cache") == 0 && strcmp(argv[1], "search") == 0;
}

bool solver::cache::CacheManager::isClear(int argc, const char* argv[]) {
    // only 2 arguments in this cache operation
    if (argc != 2) {
        return false;
    }
    return strcmp(argv[0], "cache") == 0 && strcmp(argv[1], "clear") == 0;
}