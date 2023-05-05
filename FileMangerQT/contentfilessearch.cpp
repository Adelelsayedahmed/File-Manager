#include "contentfilessearch.h"
#include <thread>
#include <algorithm>
std::mutex finalResultsMutex;


std::multimap<int, std::string> contentFilesSearch::searchInMultiplefiles(const std::vector<std::string>& filePaths, const std::string& searchStr) {
    std::multimap<int, std::string> finalResults;
    const unsigned int numThreads = std::min(static_cast<unsigned int>(std::thread::hardware_concurrency()), static_cast<unsigned int>(filePaths.size()));
    const unsigned int filesPerThread = (filePaths.size() + numThreads - 1) / numThreads;

    std::vector<std::thread> threads;
    if (filePaths.size() > numThreads) {
        // Open a thread for each group of files
        for (unsigned int i = 0; i < numThreads; ++i) {
            const unsigned int startIdx = i * filesPerThread;
            const unsigned int endIdx = std::min(startIdx + filesPerThread, static_cast<unsigned int>(filePaths.size()));
            threads.emplace_back(&contentFilesSearch::searchContentWorkFunction, this, filePaths, searchStr, endIdx - startIdx, startIdx, std::ref(finalResults));
        }
    } else {
        // Open a thread for each file
        for (unsigned int i = 0; i < filePaths.size(); ++i) {
            threads.emplace_back(&contentFilesSearch::searchContentWorkFunction, this, filePaths, searchStr, 1, i, std::ref(finalResults));
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return finalResults;
}


void contentFilesSearch::searchContentWorkFunction(const std::vector<std::string>& filePaths, const std::string& searchStr, const unsigned int workCount, const unsigned int startIdx, std::multimap<int, std::string>& finalResults) {
    std::multimap<int, std::string>results;
    //static std::mutex finalResultsMutex; // Define the mutex as a static variable

    for (unsigned int i = startIdx; i < startIdx + workCount; i++) {
        const std::multimap<int, std::string> fileResults = searchInOneFile(filePaths[i], searchStr);
        results.insert(fileResults.begin(), fileResults.end());
    }
    {
        std::lock_guard<std::mutex> lock(finalResultsMutex);
        finalResults.insert(results.begin(), results.end());
    }
}
std::multimap<int, std::string> contentFilesSearch::searchInOneFile(const std::string& filePath, const std::string& searchStr) {
    std::multimap<int, std::string> results;
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        int lineNumber = 1;
        while (std::getline(file, line)) {
            if (line.find(searchStr) != std::string::npos) {
                results.insert(std::make_pair(lineNumber, filePath));
            }
            lineNumber++;
        }
        file.close();
    }
    return results;
}
