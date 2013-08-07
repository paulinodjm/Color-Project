//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <map>
#include <string>

namespace e
{
  template <typename T>
  class Loader
  {
  public:

    virtual T* load(const std::string& name) = 0;

    T* get(const std::string& name)
    {
      auto it = m_resources.find(name);
      if (it == m_resources.end())
      {
        T* newItem = load(name);
        if (newItem)
        {
          m_resources[name] = newItem;
          return newItem;
        }
        else
        {
          return nullptr;
        }
      }
      else
      {
        return it->second;
      }
    }

    virtual ~Loader()
    {
      for (auto it = m_resources.begin(); it != m_resources.end(); it++)
      {
        delete it->second;
      }
    }

  private:

    std::map<std::string, T*> m_resources;
  };
}

