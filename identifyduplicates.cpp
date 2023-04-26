#include "identifyduplicates.h"

IdentifyDuplicates::IdentifyDuplicates()
{

}

std::vector<std::vector<std::string>> IdentifyDuplicates::checkDuplication(const std::vector<path>& paths)
{
    std::unordered_map<int,std::vector<path>> elementsMap;

    // Loop on the paths
    for(auto& path : paths){

        // Loop on files/directories in each path
        for (auto& item : directory_iterator(path)){

            // if item is a file
            if (is_regular_file(item))
            {
               int duplicationHash=fileDuplicationHash(file_size(item),item.path().extension().string());

                // if a suspected duplicate is already found
                if(elementsMap.count(duplicationHash))
                {
                   elementsMap.at(duplicationHash).push_back(item.path());
                }
                else
                {
                   std::vector<boost::filesystem::path> pathsVector;
                   pathsVector.push_back(item.path());
                   elementsMap.insert({duplicationHash,pathsVector});
                }
            }
            // if item is subdirectory
            else if(is_directory(item))
            {
                int duplicationHash=statistics::directory_size(item.path());

                // if a suspected duplicate is already found
                if(elementsMap.count(duplicationHash))
                {
                   elementsMap.at(duplicationHash).push_back(item.path());
                }
                else
                {
                   std::vector<boost::filesystem::path> pathsVector;
                   pathsVector.push_back(item.path());
                   elementsMap.insert({duplicationHash,pathsVector});
                }
            }
        }
    }
    return convertMapToVectorOfVectors(elementsMap);
}


int IdentifyDuplicates::fileDuplicationHash(int size,std::string extension)
{
    int hashValue=size;

    // Loop on the extension so that we can add it's value to our size
    for (char c : extension)
    {
         hashValue+= static_cast<int>(c);
    }
    return hashValue;
}

std::vector<std::vector<std::string>> IdentifyDuplicates::convertMapToVectorOfVectors(std::unordered_map<int, std::vector<path>>& elementsMap)
{
    std::vector<std::vector<std::string>> elementsVector;

    // Loop on the given map
    for (auto& pair : elementsMap)
    {
         // Take each value in the map and put it in a variable
         auto& pathVector = pair.second;

         if(pathVector.size()>1){

         std::vector<std::string> stringVector;

         // For each path in the group of the suspected duplicates put it in vector of strings
         for (auto& path : pathVector)
         {
           stringVector.push_back(path.string());
         }
         elementsVector.push_back(stringVector);
         }
    }
    return elementsVector;
}
bool IdentifyDuplicates::checkPathValidation(const path& path)
{
    return exists(path);
}
path IdentifyDuplicates::convertStringToPath(std::string stringPath)
{
    return path(stringPath);
}
