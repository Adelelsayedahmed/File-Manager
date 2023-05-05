    #include "contentfilessearch.h"
    #include <iostream>
    #include <map>
    #include <thread>
    #include <mutex>
    #include <vector>



    std::map<int, std::string> contentFilesSearch:: searchInMultiplefiles(const std::vector<std::string> &filePaths,
                                                                         const std::string &searchStr)
    {
        const unsigned int availableThreadsCount = std::thread::hardware_concurrency();
        const unsigned int numberOfFiles = filePaths.size();
        std::vector<std::thread> threads;
        std::map<int, std::string> totalResults;

        if (numberOfFiles <= availableThreadsCount)
        {
 //           for (int i = 0 ; i < numberOfFiles ; i++)
//            {
//                try{
//                threads.emplace_back(&contentFilesSearch::searchContentWorkFunction, this,std::cref(filePaths), searchStr, 1, i,
//                                         std::ref(totalResults));
//                }catch (const std::exception& e) {
//                std::cout<<e.what()<<std::endl;
//                }

  //          }

for (const auto& filePath : filePaths) {
    try {
        auto results = searchInOneFile(filePath, searchStr);
        totalResults.insert(results.begin(), results.end());
    } catch (const std::exception& e) {
        // Log exception
    }
}
        }else {
            // Distribute work among threads
            unsigned int workCount = numberOfFiles / (availableThreadsCount - 1);
            unsigned int residualWorkCount = numberOfFiles % (availableThreadsCount - 1);
            unsigned int startIndex = 0;

            for (unsigned int i = 0; i < availableThreadsCount - 1; ++i) {
                threads.emplace_back(&contentFilesSearch::searchContentWorkFunction, this,
                                     std::cref(filePaths), searchStr, workCount, startIndex,
                                     std::ref(totalResults));
                startIndex += workCount;
            }
            threads.emplace_back(&contentFilesSearch::searchContentWorkFunction, this,
                                 std::cref(filePaths), searchStr, residualWorkCount, startIndex,
                                 std::ref(totalResults));
        }

        // Join threads and handle exceptions
        for (auto& thread : threads) {
            try {
                thread.join();
            } catch (const std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }

        return totalResults;
    }

    void contentFilesSearch::searchContentWorkFunction(const std::vector<std::string>& filePaths,
                                                       const std::string& searchStr,
                                                       unsigned int workCount, unsigned int startIdx,
                                                       std::map<int, std::string>& totalResults)
    {
        std::map<int, std::string> threadResults;

        for (unsigned int i = 0; i < workCount; ++i) {
            try {
                auto results = searchInOneFile(filePaths[startIdx + i], searchStr);
                threadResults.insert(results.begin(), results.end());
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }

        std::lock_guard<std::mutex> lock(m_mutex);
        for (const auto& result : threadResults) {
            totalResults.insert(result);
        }
    }


    std::map<int, std::string> contentFilesSearch::searchInOneFile(const std::string &filePath,
                                                                   const std::string &searchStr)
    {
        std::map<int, std::string> results;
        std::ifstream file(filePath);
        if (file) {
            std::string line;
            int lineNum = 1;
            while (getline(file, line)) {
                if (line.find(searchStr) != std::string::npos) {
                    results[lineNum] = filePath;
                    std::cout << "line found at " << lineNum << std::endl;
                }
                ++lineNum;
            }
        }
        return results;
    }
