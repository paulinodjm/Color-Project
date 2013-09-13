//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "settings.h"
#include "../Engine/zipstream.h"
#include "../Engine/zipstring.h"
#include <jsoncpp/json/json.h>
#include <physfs.h>

edSETTINGS::edSETTINGS()
{
  MakeDefault();
}

bool edSETTINGS::Load(const std::string& filename)
{
  ZIPSTREAM zipstream;
  ZIPSTRING zipstring;
  Json::Reader reader;
  Json::Value root;
  
  if (!zipstream.Open(filename))
  {
    std::cout << "Failed to load settings from '" << filename << "'." << std::endl;
    MakeDefault();
    return false;
  }
  if (!zipstring.Read(zipstream))
  {
    std::cout << "Failed to load settings from '" << filename << "' : stream error." << std::endl;
    MakeDefault();
    return false;
  }
  if (!reader.parse(zipstring.Str(), root))
  {
    std::cout << "Failed to load settings from '" << filename << "' : " << reader.getFormatedErrorMessages();
    MakeDefault();
    return false;
  }
  
  SetWindowSize(
    wxSize(
      root.get("window-width", 800).asInt(),
      root.get("window-height", 600).asInt()
    )
  );

  std::cout << "Settings successfully loaded from '" << filename << "'." << std::endl;
  return true;
}

bool edSETTINGS::Save(const std::string& filename)
{
  return false;
}

void edSETTINGS::MakeDefault()
{
  SetWindowSize(wxSize(800, 600));
}

const wxSize& edSETTINGS::WindowSize() const
{
  return mWindowSize;
}

void edSETTINGS::SetWindowSize(const wxSize& size)
{
  if (size.GetWidth() > 0 || size.GetHeight() > 0)
  {
    mWindowSize = size;
  }
}
