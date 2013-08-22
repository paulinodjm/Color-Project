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

void CONTENTMANAGER::Weep()
{
  GetCache<TEXTURE>().Weep();
}
