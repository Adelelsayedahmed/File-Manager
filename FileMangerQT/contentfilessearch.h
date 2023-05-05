#ifndef CONTENTFILESSEARCH_H
#define CONTENTFILESSEARCH_H

#include <vector>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>


class contentFilesSearch
{
public:
    contentFilesSearch();
    std::map<int, std::string> searchInMultiplefiles(const std::vector<std::string>& filePaths, const std::string& searchStr);
private:
    void searchContentWorkFunction(const std::vector<std::string>& filePaths ,const std::string& searchStr,
                                   const unsigned int workCount ,const unsigned int startIdx,std::map<int, std::string> &finalResults);

    std::map<int, std::string> searchInOneFile(const std::string &filePath , const std::string& searchStr);
    std::mutex m_mutex;

};

#endif // CONTENTFILESSEARCH_H
