//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Engine/level.h"

#ifdef __WXGTK__
    #include <gdk/gdkx.h>
    #include <gtk/gtk.h>
    #include <wx-2.8/wx/gtk/win_gtk.h>
#endif

class edCANVAS : public sf::RenderWindow, public wxControl
{
public:

  edCANVAS(
    wxWindow* parent, 
    wxWindowID id, 
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = 0,
    const wxValidator& validator = wxDefaultValidator,
    const wxString& name = wxPanelNameStr);
    
  virtual ~edCANVAS() {}
  
  void Create();
  
private:

  DECLARE_EVENT_TABLE()

  void OnResize(wxSizeEvent& event);
};
