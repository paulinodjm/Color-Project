//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>
#include "settings.h"
#include "frame.h"
#include "id.h"

class edEDITOR : public wxApp, public edFRAMELISTENER
{  
public:

  edEDITOR();
  
  edFRAME* MainFrame() const;
  
protected:

  void OnFrameResized(edFRAME* frame, const wxSize& size);

private:

  bool OnInit();
  int OnExit();
  
  edFRAME*    mMainFrame;
  edSETTINGS  mSettings;
};

DECLARE_APP(edEDITOR)

