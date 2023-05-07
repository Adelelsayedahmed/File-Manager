#include "undo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
/*main undo function */
//void Undo::undo()
//{
//    if(actions.empty()==true){
//        return ;
//    }
//    CopyCutAction action=actions.top();
//    actions.pop();
//    fs::path current_path;

//    if(action==CopyCutAction::Cut){
//        if(paths_CUT_COPY.empty()==true){
//            return ;
//        }
//        current_path=paths_CUT_COPY.top();
//        paths_CUT_COPY.pop();
//        fs::path destination_path=paths_CUT_COPY.top();
//        paths_CUT_COPY.pop();
//        cutFile(current_path);
//        paste(current_path,destination_path,CopyCutAction::Cut);

//    }
//    else if(action==CopyCutAction::Copy){
//        if(paths_CUT_COPY.empty()==true){
//            return ;
//        }
//        fs::path current_path=paths_CUT_COPY.top();
//        paths_CUT_COPY.pop();
//        del(current_path);
//    }
//    else if(action==CopyCutAction::BatchRename){
//        undoBatchRename();
//    }
//    else if(action==CopyCutAction::Delete){
//        undoDeleteItems();
//    }
//}
/*delete*/
//void Undo::addDeletedItems(DeletedItem deleted_item)
//{
//    deleted_items.push(deleted_item);
//}
//void Undo::undoDeleteItems()
//{
//    if(  deleted_items.empty()==true){
//        return ;
//    }
//     DeletedItem last_deleted_item=deleted_items.top();
//     deleted_items.pop();
//     std::ofstream file(last_deleted_item.path.string());
//     file <<last_deleted_item.contents;
//}
///*rename*/
//void Undo::addPaths_BatchRename(std::vector<std::string> oldPaths, std::vector<std::string> newNames)
//{
//    paths_Bathc_Rename.push(oldPaths);
//    paths_Bathc_Rename.push(newNames);
//}


//void Undo::undoBatchRename()
//{

//    if( paths_Bathc_Rename.empty()==true)
//        return ;
//    std::vector<std::string> currentNames= paths_Bathc_Rename.top();
//    paths_Bathc_Rename.pop();
//    std::vector<std::string> oldPaths= paths_Bathc_Rename.top();
//    paths_Bathc_Rename.pop();
//   for(int i=0;i<currentNames.size();i++){
//       try
//       {
//           fs::rename(removeNameFromPath(oldPaths[i])+currentNames[i],oldPaths[i]);
//       }
//       catch (const std::exception& ex) {
//       std::cerr << "Error renaming file in Undo: " << ex.what() << std::endl;    }
//   }
//}


//std::string Undo::removeNameFromPath(std::string path) {
//    size_t found = path.find_last_of("/\\");
//    if (found != std::string::npos) {
//        return path.substr(0, found+1);
//    }
//    return path;
//}
///*copy &  cut*/
//void Undo::addActions(CopyCutAction action)
//{
//    actions.push(action);
//}
//void Undo::addPaths_COPY(boost::filesystem::path current_path)
//{
//    paths_CUT_COPY.push(current_path);
//}
//void Undo::addPaths_CUT(boost::filesystem::path oldPath, boost::filesystem::path newPath)
//{

//   std::string old_path= oldPath.string();
//   std::size_t pos = old_path.find_last_of("/");
//   if (pos != std::string::npos) {
//       old_path.erase(pos);
//    }
//     fs::path mypath(old_path);
//     paths_CUT_COPY.push(mypath);
//     paths_CUT_COPY.push(newPath);
//}

///*function zoz*/
//void Undo::paste(fs::path source_path, fs::path destination_path, CopyCutAction action)
//{
//    fs::path temp_path;
//    if (!fs::exists(source_path)) {
//        qInfo() << "Source file does not exist!\n" ;
//        return ;
//    }
//    if(action == CopyCutAction::Copy)
//    {
//        try {
//            temp_path = destination_path / source_path.filename();
//            if (fs::exists(temp_path)) {
//                qInfo() << "Destination already exists!\n";
//                return ;
//            }
//            if (fs::is_directory(source_path))
//            {
//                fs::copy(source_path, temp_path, fs::copy_options::recursive);

//            }
//            else
//            {
//                fs::copy_file(source_path, temp_path);
//            }
//            return ;
//        }
//        catch (const std::exception& ex) {
//            qInfo() << "Error: "  ;
//            std::cout<<temp_path;
//        }
//    }
//    else if(action == CopyCutAction::Cut)
//    {
//        temp_path = destination_path / m_cutPath.filename();
//        pasteFromCut(temp_path);
//    }
//}
//void Undo::pasteFromCut(fs::path destination_path)
//{
//    try {
//        if (fs::exists(destination_path)) {
//            qInfo() << "Destination already exists!\n";
//            return;
//        }

//        if (m_cutPath.empty()) {
//            return; // Nothing to paste
//        }

//        fs::rename(m_cutPath, destination_path);
//        m_cutPath.clear();

//    } catch (const std::exception& ex) {
//        qInfo() << "Error: " << ex.what() << '\n';
//    }
//}


//void Undo::cutFile(const fs::path &path)
//{
//    m_cutPath = path;
//}

