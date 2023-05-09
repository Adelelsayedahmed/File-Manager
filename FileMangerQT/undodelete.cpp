#include "undodelete.h"
undoDelete::undoDelete(boost::filesystem::path &source_path,fs::path& new_path)
{
    std::string old_path= source_path.string();
    std::size_t pos = old_path.find_last_of("/");
    if (pos != std::string::npos) {
        old_path.erase(pos);
    }
    fs::path mypath(old_path);
    this->old_path=old_path;
    this->new_path=new_path;
}
void undoDelete::undo()
{
    utilities::pasteToUndoCut(new_path,old_path);
}
