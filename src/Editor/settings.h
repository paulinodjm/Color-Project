//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <wx/gdicmn.h>

class edSETTINGS
{
public:

  edSETTINGS();

  bool Load(const std::string& filename);
  bool Save(const std::string& filename);
  void MakeDefault();

  const wxSize& WindowSize() const;
  void SetWindowSize(const wxSize& size);

private:

  wxSize mWindowSize;
};
