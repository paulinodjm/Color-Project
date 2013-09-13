//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>

class edLEVELDIALOG : public wxDialog
{
public:

  edLEVELDIALOG(
    wxWindow* parent, 
    wxWindowID id, 
    const wxString& title, 
    const wxPoint& pos = wxDefaultPosition, 
    const wxSize& size = wxDefaultSize, 
    long style = wxDEFAULT_DIALOG_STYLE, 
    const wxString& name = wxT("levelDialogBox") );
  
  wxString LevelName() const;
  void SetLevelName(const wxString& levelName);
  
  bool MustExist() const;
  void SetMustExist(bool value);
  
  bool AlertIfExist() const;
  void SetAlertIfExist(bool value);
  
private:

  wxTextCtrl* mLevelName;
  
  bool mMustExist;
  bool mAlertIfExist;
};

