//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "contentmanager.h"

template<>
LOADER<TEXTURE>& CONTENTMANAGER::GetLoader()
{
  return textureLoader;
}

template<>
CONTENTMANAGER::CACHE<TEXTURE>& CONTENTMANAGER::GetCache()
{
  return textureCache;
}

template<>
LOADER<SOUNDBUFFER>& CONTENTMANAGER::GetLoader()
{
  return soundBufferLoader;
}

template<>
CONTENTMANAGER::CACHE<SOUNDBUFFER>& CONTENTMANAGER::GetCache()
{
  return soundBufferCache;
}

void CONTENTMANAGER::Weep()
{
  GetCache<TEXTURE>().Weep();
  GetCache<SOUNDBUFFER>().Weep();
}
