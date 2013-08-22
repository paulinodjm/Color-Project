//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "loader.h"
#include "resources.h"
#include <iostream>

template <>
class LOADER<TEXTURE>
{
public:

  bool Load(std::shared_ptr<TEXTURE>& res, const std::string& name);
};
