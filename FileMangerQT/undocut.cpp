#include "undocut.h"
UndoCut::UndoCut(boost::filesystem::path &source_path, boost::filesystem::path &dest_path)
{
    std::string old_path= source_path.string();
    std::size_t pos = old_path.find_last_of("/");
    if (pos != std::string::npos) {
        old_path.erase(pos);
    }
    fs::path mypath(old_path);
    this->source_path=mypath;
    this->dest_path=dest_path;
}

void UndoCut::undo()
{
    Undo::pasteToUndoCut(dest_path,source_path);
}
