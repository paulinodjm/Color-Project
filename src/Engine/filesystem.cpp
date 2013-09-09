//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "filesystem.h"
#include <physfs.h>
#include <iostream>

bool FS::Init(const char* argv0)
{
  if (!PHYSFS_init(argv0))
  {
    std::cout << "FS error : " << std::string(PHYSFS_getLastError()) << "." << std::endl;
    return false;
  }
  else
  {
    std::cout << "FS initialized." << std::endl;
    return true;
  }
}
  
bool FS::Deinit()
{
  return PHYSFS_deinit();
}

bool FS::IsInit()
{
  return PHYSFS_isInit();
}

bool FS::Mount(const std::string& dir, const std::string& mountPoint)
{
  if (!PHYSFS_mount(dir.c_str(), mountPoint.c_str(), 1))
  {
    std::cout << "Failed to mount '" << dir << "' : " << std::string(PHYSFS_getLastError()) << "." << std::endl;
    return false;
  }
  else
  {
    std::cout << "'" << dir << "' mounted successfully." << std::endl;
    return true;
  }
}
