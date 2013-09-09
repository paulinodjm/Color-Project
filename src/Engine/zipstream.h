//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/System/InputStream.hpp>
#include <physfs.h>
#include <string>

class ZIPSTREAM : public sf::InputStream
{
public:

  ZIPSTREAM();
  ~ZIPSTREAM();
  
  bool Open(const std::string& filename);
  
  sf::Int64 read(void* data, sf::Int64 size);
  sf::Int64 seek(sf::Int64 position);
  sf::Int64 tell();
  sf::Int64 getSize();
private:

  PHYSFS_file* mFile;
};

