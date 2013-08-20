#include "wxSFMLCanvas.hpp"

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
  EVT_IDLE(wxSFMLCanvas::onIdle)
  EVT_PAINT(wxSFMLCanvas::onPaint)
END_EVENT_TABLE()

wxSFMLCanvas::wxSFMLCanvas(
    wxWindow* parent, 
    wxWindowID id, 
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxValidator& validator,
    const wxString& name) 
:
  wxControl(parent, id, pos, size, style, validator, name),
  e::BaseGame(static_cast<sf::RenderWindow&>(*this))
{
  #ifdef __WXGTK__
    gtk_widget_realize(m_wxwindow);
    gtk_widget_set_double_buffered(m_wxwindow, false);
    GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
    XFlush(GDK_WINDOW_XDISPLAY(Win));
    sf::RenderWindow::create(GDK_WINDOW_XWINDOW(Win));

  #else
    sf::RenderWindow::create( static_cast<sf::WindowHandle>(GetHandle()) );
  #endif
}

void wxSFMLCanvas::onIdle(wxIdleEvent&)
{
  Refresh(false);
}

void wxSFMLCanvas::onPaint(wxPaintEvent&)
{
  wxPaintDC Dc(this);
  clear();
  display();
}
