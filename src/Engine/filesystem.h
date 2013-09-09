//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <string>

namespace FS
{
  bool Init(const char* argv0);
  bool IsInit();
  bool Deinit();
  
  bool Mount(const std::string& dir, const std::string& mountPoint="/");
}
