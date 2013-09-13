//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "datamodel.h"
#include <iostream>

edDATAMODEL::edDATAMODEL() {}

const std::shared_ptr<TILEMAP>& edDATAMODEL::Tilemap() const
{
  return mTilemap;
}

bool edDATAMODEL::LoadLevel(const std::string& levelName)
{
  std::cout << "Niveau '" << levelName << "' chargé!" << std::endl;
  return false;
}

void edDATAMODEL::NewLevel()
{
  std::cout << "Nouveau niveau!" << std::endl;
}

bool edDATAMODEL::SaveLevel(const std::string& levelName)
{
  std::cout << "Niveau '" << levelName << "' sauvegardé!" << std::endl;
  return false;
}

