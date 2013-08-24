//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <memory.h>
#include <string>
#include <map>
#include "loader.h"
#include "textureloader.h"
#include "soundbufferloader.h"
#include "animationsloader.h"

class CONTENTMANAGER
{
private:

  template <typename T>
  class CACHE
  {
  public:
  
    bool Get(std::shared_ptr<T>& res, const std::string& name)
    {
      auto it = cache.find(name);
      if (it != cache.end())
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    
    void Add(std::shared_ptr<T>& res, const std::string& name)
    {
      cache[name] = res;
    }
    
    void Weep()
    {
      for (auto it = cache.begin(); it != cache.end(); it++)
      {
        if (it->second.unique())
        {
          cache.erase(it);
        }
      }
    }
  
  private:
  
    std::map<std::string, std::shared_ptr<T>> cache;
  };

private:

  CACHE<TEXTURE>      textureCache;
  LOADER<TEXTURE>     textureLoader;
  CACHE<SOUNDBUFFER>  soundBufferCache;
  LOADER<SOUNDBUFFER> soundBufferLoader;
  CACHE<ANIMATIONS>   animationsCache;
  LOADER<ANIMATIONS>  animationsLoader;

protected:

  template <typename T>
  CACHE<T>& GetCache();
  
  template <typename T>
  LOADER<T>& GetLoader();

public:

  template <typename T>
  bool Load(std::shared_ptr<T>& res, const std::string& name)
  {
    CACHE<T>& cache = GetCache<T>();
    LOADER<T>& loader = GetLoader<T>();
    
    if (cache.Get(res, name))
    {
      return true;
    }
    else if (loader.Load(res, name, *this))
    {
      cache.Add(res, name);
      return true;
    }
    else
    {
      return false;
    }
  }
  
  void Weep();
};
