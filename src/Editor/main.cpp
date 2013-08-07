//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <wx/wx.h>
#include <string>
#include "wxSFMLCanvas.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Engine/BaseTypes.hpp"
#include "../Engine/BaseGame.hpp"
#include <iostream>
#include <wx/colordlg.h>

class GameView : public wxSFMLCanvas
{
public:

  GameView(
    wxWindow* parent, 
    wxWindowID id, 
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = 0,
    const wxValidator& validator = wxDefaultValidator,
    const wxString& name = wxPanelNameStr)
  :
    wxSFMLCanvas(parent, id, pos, size, style, validator, name)
  {
    open(wxT("data/tileset.png"));
    m_size = GetSize();
  }

  void open(const wxString& filename)
  {
    m_texture.loadFromFile( std::string(filename.mb_str()) );
    m_sprite.setTexture(m_texture, true);
  }

  void setBackgroundColor(const wxColor& col)
  {
    m_background.r = col.Red();
    m_background.g = col.Green();
    m_background.b = col.Blue();
  }
  
  wxColor getBackgroundColor() const
  {
    return wxColor( m_background.r, m_background.g, m_background.b );
  }

protected:

  void update()
  {
    if (m_size != GetSize())
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
      
      m_size = GetSize();
    }
    setView( sf::View(sf::FloatRect(0,0, (float)GetSize().GetWidth(), (float)GetSize().GetHeight())));
    clear(m_background);
    draw( m_sprite );
  }
  
private:

  sf::Texture m_texture;
  sf::Sprite m_sprite;
  sf::Color m_background;
  wxSize m_size;
};

class Editor : public wxApp
{
  DECLARE_EVENT_TABLE()

  void onOpen(wxCommandEvent& event)
  {
    wxFileDialog* fileChooser = new wxFileDialog(m_frame, wxT("Ouvrir une image"), wxT(""), wxT(""), 
      wxT("Images|*bmp;*.png;*tga;*.jpg;*.gif;*.psd;*.hdr;*.pic" ) );
    
    if ( fileChooser->ShowModal() == wxID_OK )
    {
      wxString path = fileChooser->GetPath();
      m_gameView->open(path);
    }
  }

  void onChooseBackgroundColor(wxCommandEvent& event)
  {
    wxColour col = wxGetColourFromUser(m_frame, m_gameView->getBackgroundColor(), wxT("Choisissez la couleur de fond"));
    if (col.IsOk())
    {
      m_gameView->setBackgroundColor(col);
    }
  }

  void onExit(wxCommandEvent& event)
  {
    if ( 
      wxMessageBox(
        wxT("Êtes-vous sûr de vouloir quitter?"), 
        wxT("Quitter"),
        wxYES_NO|wxICON_QUESTION,
        m_frame
      ) == wxYES
    ){
      m_frame->Close();
    }
  }

  bool OnInit()
  {
    m_frame = new wxFrame(NULL, wxID_ANY, wxT("Color Project Editor"));
    
    // menu bar
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* menu = new wxMenu();
    menu->Append(wxID_OPEN, wxT("Ouvrir une image"), wxT("Choisir l'image en arrière plan"));
    menu->Append(1, wxT("Couleur de fond"), wxT("Choisir la couleur de fond"));
    menu->AppendSeparator();
    menu->Append(wxID_EXIT, wxT("Quitter"), wxT("Quitter l'éditeur"));
    menuBar->Append( menu, wxT("Fichier") );
    m_frame->SetMenuBar(menuBar);
    
    // content
    wxPanel* panel = new wxPanel(m_frame);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    m_gameView = new GameView(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 600) );
    sizer->Add( m_gameView, 1, wxEXPAND );
    m_frame->Show();
    return true;
  }
  
  wxFrame* m_frame;
  GameView* m_gameView;
};
BEGIN_EVENT_TABLE(Editor, wxApp)
  EVT_MENU(wxID_OPEN, Editor::onOpen)
  EVT_MENU(1, Editor::onChooseBackgroundColor)
  EVT_MENU(wxID_EXIT, Editor::onExit)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)


