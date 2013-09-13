//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "frame.h"

BEGIN_EVENT_TABLE(edFRAME, wxFrame)
  EVT_SIZE(edFRAME::OnResize)
END_EVENT_TABLE()

edFRAME::edFRAME(
  wxWindow* parent,
  wxWindowID id,
  const wxString& title,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxString& name
)
  : wxFrame(parent, id, title, pos, size, style, name)
{}

bool edFRAME::AddFrameListener(edFRAMELISTENER* listener)
{
  if (!listener) return false;
  
  return mListeners.insert(listener).second;
}

bool edFRAME::DeleteFrameListener(edFRAMELISTENER* listener)
{
  return mListeners.erase(listener) == 1;
}

void edFRAME::ClearFrameListeners()
{
  mListeners.clear();
}

void edFRAME::OnResize(wxSizeEvent& event)
{
  for (edFRAMELISTENER* listener : mListeners)
  {
    listener->OnFrameResized(this, event.GetSize());
  }
}

