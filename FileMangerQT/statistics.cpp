#include "statistics.h"

statistics::statistics()
{

}

std::unordered_map<std::string,int> statistics::directoryFilesSizes(const path& directortyPath)
{
    std::unordered_map<std::string, int> dataMap;

    // Iterate through directory and its contents and fill the map.
     for (auto& item : directory_iterator(directortyPath))
    {
        // if item is a file
        if (is_regular_file(item))
        {
        dataMap.insert({item.path().filename().string(),convertToKB(file_size(item))});
        }
        // if item is subdirectory
        else if(is_directory(item))
        {
        dataMap.insert({item.path().filename().string()+"/",convertToKB(directory_size(item.path()))});

        }
    }
     return dataMap;

}

std::unordered_map<std::string,int> statistics::directoryFilesTypes(const path& directortyPath)
{

     std::unordered_map<std::string, int> dataMap;

     // Iterate through directory and its contents
     for (auto& item : directory_iterator(directortyPath))
     {
        // if item is a file
        if (is_regular_file(item))
        {
        // Get the extension of the file
        std::string extension=item.path().extension().string();

        // if file extension is empty, set it to "other"
        if(extension.empty())
        {
            extension="other";
        }

        // if file extension already exists in map, increment its value
        if(dataMap.count(extension))
        {
            dataMap.at(extension)+=1;
        }
        // if file extension does not exist in map, insert it with a value of 1
        else
        {
            dataMap.insert({extension,1});
        }
        }
        // if item is subdirectory
        else if(is_directory(item))
        {

        // if "directory" key already exists in map, increment its value
        if(dataMap.count("directory"))
        {
              dataMap.at("directory")+=1;
        }
        // if "directory" key does not exist in map, insert it with a value of 1
        else
        {
            dataMap.insert({"directory",1});
        }

        }
     }
     return dataMap;

}

path statistics::getCurrentPath()
{
     // Return the current directory path.
     return current_path();
}

uintmax_t statistics::directory_size(const path& directory_path)
{
     uintmax_t size = 0;

    // loop over the files and subdirectories recursively(every subdirectory open and loop on files in it)
     for (auto& item  : recursive_directory_iterator(directory_path))
     {
        // check if the current item is a regular file, add the file size to the accumulated size.
        if (is_regular_file(item))
        {
        size += file_size(item);
        }
     }

     return size;
}

int statistics::numberOfItems(path& path)
{
     int numberOfItems=0;

     directory_iterator end_itr;

     // Iterate through directory
     for (directory_iterator itr(path); itr != end_itr; itr++)
     {
        numberOfItems++;
     }
     return numberOfItems;
}

int statistics::convertToKB(uintmax_t bytes)
{     
     return bytes/1000;
}
