//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <wx/wx.h>
#include "wxSFMLCanvas.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Engine/BaseTypes.hpp"
#include "../Engine/BaseGame.hpp"

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
  }

protected:

  void update()
  {
    clear();
  }
};

class Editor : public wxApp
{
  bool OnInit()
  {
    wxFrame* frame = new wxFrame(NULL, wxID_ANY, _T("Color Project Editor"));
    wxPanel* panel = new wxPanel(frame);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    sizer->Add( new wxStaticText(panel, wxID_ANY, _T("Coming soon!")), 0, wxALIGN_CENTER );
    wxSFMLCanvas* canvas = new GameView(panel, wxID_ANY);
    
    
    
    sizer->Add( canvas, 1, wxEXPAND );
    frame->Show();
    return true;
  }
};
IMPLEMENT_APP(Editor)


