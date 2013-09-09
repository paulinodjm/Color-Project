//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "zipstream.h"
#include <iostream>

ZIPSTREAM::ZIPSTREAM() : mFile(nullptr) 
{}

ZIPSTREAM::~ZIPSTREAM()
{
  if (mFile)
    PHYSFS_close(mFile);
}

bool ZIPSTREAM::Open(const std::string& filename)
{
  if (mFile)
    PHYSFS_close(mFile);
  mFile = PHYSFS_openRead(filename.c_str());
  if (mFile)
  {
    return true;
  }
  else
  {
    std::cout << "Unable to open stream '" << filename << "' : " << std::string(PHYSFS_getLastError()) << "." << std::endl;
    return false;
  }
}

sf::Int64 ZIPSTREAM::read(void* data, sf::Int64 size)
{
  if (mFile)
    return PHYSFS_read(mFile, data, 1, size);
  else
    return -1;
}

sf::Int64 ZIPSTREAM::seek(sf::Int64 position)
{
  if (mFile)
  {
    PHYSFS_seek(mFile, position);
    return tell();
  }
  else
    return -1;
}

sf::Int64 ZIPSTREAM::tell()
{
  if (mFile)
    return PHYSFS_tell(mFile);
  else
    return -1;
}

sf::Int64 ZIPSTREAM::getSize()
{
  if (mFile)
    return PHYSFS_fileLength(mFile);
  else
    return -1;
}

