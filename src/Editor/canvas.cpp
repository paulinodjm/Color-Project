//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "canvas.h"

BEGIN_EVENT_TABLE(edCANVAS, wxControl)
  EVT_SIZE(edCANVAS::OnResize)
END_EVENT_TABLE()

edCANVAS::edCANVAS(
    wxWindow* parent, 
    wxWindowID id, 
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxValidator& validator,
    const wxString& name) 
:
  wxControl(parent, id, pos, size, style, validator, name)
{
  Create();
}

/*
void wxSFMLCanvas::onIdle(wxIdleEvent&)
{
  Refresh(false);
}

void wxSFMLCanvas::onPaint(wxPaintEvent&)
{
  wxPaintDC Dc(this);
  if (mLevel)
  {
    draw(*mLevel);
  }
  else
  {
    clear(sf::Color::White);
  }
  display();
}//*/

void edCANVAS::OnResize(wxSizeEvent& event)
{
  Create();
}

void edCANVAS::Create()
{
  #ifdef __WXGTK__
    gtk_widget_realize(m_wxwindow);
    GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
    XFlush(GDK_WINDOW_XDISPLAY(Win));
    sf::RenderWindow::create(GDK_WINDOW_XWINDOW(Win));
  #else
    sf::RenderWindow::create( static_cast<sf::WindowHandle>(GetHandle()) );
  #endif
}
