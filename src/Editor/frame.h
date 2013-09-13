//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>
#include <set>
#include "datamodel.h"

class edFRAME;

class edFRAMELISTENER
{
public:

  virtual void OnFrameResized(edFRAME *frame, const wxSize& size) = 0;
  
  /*
  virtual void OnNewLevel() {}
  virtual void OnOpenLevel(const wxString& name) {}
  virtual void OnSaveLevel(const wxString& name) {}
  virtual void OnUndo() {}
  virtual void OnRedo() {}
  virtual void OnEditTilemap() {}
  virtual void OnEditObjects() {}
  virtual void OnStartPreview() {} //*/
};

class edFRAME : public wxFrame
{
  DECLARE_EVENT_TABLE()

public:
  
  edFRAME(
    wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxDEFAULT_FRAME_STYLE,
    const wxString& name = wxT("mainFrame"));
    
  bool AddFrameListener(edFRAMELISTENER* listener);
  bool DeleteFrameListener(edFRAMELISTENER* listener);
  void ClearFrameListeners();
  
  edDATAMODEL *DataModel() const;
  void SetDataModel(edDATAMODEL* model);
  
protected:

  void OnResize(wxSizeEvent& event);
  void OnNew(wxCommandEvent& event);
  void OnOpen(wxCommandEvent& event);
  void OnSave(wxCommandEvent& event);
  void OnSaveAs(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnHelp(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  
  void SetupMenuBar();
  
private:

  std::set<edFRAMELISTENER*> mListeners;
  edDATAMODEL *mDataModel;
  wxString    mLevelName;
};

