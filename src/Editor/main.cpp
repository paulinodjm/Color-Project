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
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include "../Engine/Texture.hpp"

class Editor : public wxApp
{
  DECLARE_EVENT_TABLE()

public:

  Editor() : wxApp(),
   
    m_texture("data/tileset.png")
  {}

private:

  bool OnInit()
  {
    m_frame = new wxFrame(NULL, wxID_ANY, wxT("Color Project Editor"));
    m_frame->Show();
    
    e::Texture("dqsfjmk.png");
    e::Texture("data/tileset.png");
    
    return true;
  }
  
  e::Texture m_texture;
  wxFrame* m_frame;
};
BEGIN_EVENT_TABLE(Editor, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)

//*/
