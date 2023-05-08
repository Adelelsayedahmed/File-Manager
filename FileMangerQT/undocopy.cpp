#include "undocopy.h"
UndoCopy::UndoCopy(std::vector<boost::filesystem::path> &paths)
{
    this->paths=paths;
}
 void UndoCopy::undo()
{
    if(!paths.empty()){
        fs::path p;
        for(int i=0;i<paths.size();i++){
            p=paths.front();
            Undo::del(p);
        }
    }
}
