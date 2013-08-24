//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "loader.h"
#include "animation.h"
#include <memory>
#include <jsoncpp/json/json.h>

template <>
class LOADER<ANIMATIONS>
{
public:

  bool Load(std::shared_ptr<ANIMATIONS>& res, const std::string& name, CONTENTMANAGER& contentManager);
  
};

