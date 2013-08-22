//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <string>
#include <memory>

template <typename T>
class LOADER
{
public:

  bool Load(std::shared_ptr<T>& res, const std::string& name);
};
