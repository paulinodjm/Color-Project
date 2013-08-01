//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <wx/wx.h>
#include <SFML/Graphics/RenderWindow.hpp>

#ifdef __WXGTK__
    #include <gdk/gdkx.h>
    #include <gtk/gtk.h>
    #include <wx-2.8/wx/gtk/win_gtk.h>
#endif

class wxSFMLCanvas : public sf::RenderWindow, public wxControl
{
public:

  wxSFMLCanvas(
    wxWindow* parent, 
    wxWindowID id, 
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = 0,
    const wxValidator& validator = wxDefaultValidator,
    const wxString& name = wxPanelNameStr);
    
  virtual ~wxSFMLCanvas() {}
  
protected:

  virtual void update() {}
  
private:

  DECLARE_EVENT_TABLE()

  void onIdle(wxIdleEvent& event);

  void onPaint(wxPaintEvent& event);
};