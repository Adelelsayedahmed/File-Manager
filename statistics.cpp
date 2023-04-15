#include "statistics.h"

statistics::statistics()
{

}

std::unordered_map<std::string,int> statistics::directoryFilesSizes(const path& directortyPath)
{
    std::unordered_map<std::string, int> dataMap;

     for (auto& item : directory_iterator(directortyPath))
    {
        if (is_regular_file(item))
        {
        dataMap.insert({item.path().filename().string(),convertToKB(file_size(item))});
        }
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

     for (auto& item : directory_iterator(directortyPath))
     {
        if (is_regular_file(item))
        {
        std::string extension=item.path().extension().string();
        if(extension.empty()){
            extension="other";
        }
        if(dataMap.count(extension)){

            dataMap.at(extension)+=1;
        }else{
        dataMap.insert({extension,1});
        }

        }
        else if(is_directory(item))
        {
        if(dataMap.count("directory")){
        dataMap.at("directory")+=1;
        }else{

        dataMap.insert({"directory",1});
        }

        }
     }
     return dataMap;

}

path statistics::getCurrentPath()
{
     std::string s="/home/fady/CLionProjects";
//     qDebug() << current_path().string();
//     return current_path();
     qDebug() << s;
     return path(s);
}

uintmax_t statistics::directory_size(const path& directory_path)
{
     uintmax_t size = 0;

     for (auto& item  : recursive_directory_iterator(directory_path))
     {
        if (is_regular_file(item))
        {
        size += file_size(item);
        }
     }

     return size;
}
int statistics::convertToKB(uintmax_t bytes)
{
     int sizeInKB=bytes/1000;
     return sizeInKB;
}
