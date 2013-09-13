//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <string>
#include "../Engine/tilemap.h"

class edDATAMODEL
{
public:

  edDATAMODEL();

  const std::shared_ptr<TILEMAP>& Tilemap() const;
  
  bool LoadLevel(const std::string& levelName);
  void NewLevel();
  bool SaveLevel(const std::string& levelName);

private:

  std::shared_ptr<TILEMAP>  mTilemap;
};

