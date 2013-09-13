//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>

enum class edID
{
  Open    = wxID_OPEN,
  New     = wxID_NEW,
  Save    = wxID_SAVE,
  SaveAs  = wxID_SAVEAS,
  Exit    = wxID_EXIT,
  
  Undo    = wxID_UNDO,
  Redo    = wxID_REDO,
  
  Help    = wxID_HELP,
  About   = wxID_ABOUT,
  
  EditTilemap = wxID_HIGHEST+1,
  EditObjects,
  Preview
};

