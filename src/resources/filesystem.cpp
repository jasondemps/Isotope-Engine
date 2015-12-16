#include "Filesystem.h"

namespace System
{
  FileSystem::FileSystem(std::string& path) : base(path), currDir(base)
  {
  }

  FileSystem::~FileSystem()
  {
    //tinydir_close(&dir);
  }

  // Directory Traversal
  int FileSystem::Next()
  {
    // Find a directory.
    /*if (dir.has_next)
    {
      //tinydir_next(&dir);
      currDir = dir.path;

      return 1;
    }*/

    return 0;
  }

  // This takes a bit more work!
  int FileSystem::Prev()
  {
    if (currDir != base)
    {
      // Take off the previous directory from the dir string.
      std::string::size_type pos = currDir.find_last_of("//");
      currDir = currDir.substr(0, currDir.size() - pos);

      //tinydir_open_sorted(&dir, currDir.c_str());

      return 1;
    }
    else
      return 0;
  }

  const std::list<std::pair<const char*, const char*>>& FileSystem::Enumerate(EnumType type)
  {
    // Could get nasty =/
    // TODO: might implement a flag or something to check if we called the same dir enumerate previously.
    dirList.clear();
    /*
    for (int i = 0; i < dir.n_files; ++i)
    {
     // tinydir_file file;
      //tinydir_readfile_n(&dir, &file, i);

      /*
      if (file.is_reg)
      {
        if (type == EnumType::FILES || type == EnumType::ALL)
          dirList.push_back(std::make_pair(file.name, file.path));
      }
      
      if (file.is_dir)
      {
        if (type == EnumType::DIRECTORIES || type == EnumType::ALL)
          dirList.push_back(std::make_pair(file.name, file.path));
      }
      */
    //}

    return dirList;
  }

}