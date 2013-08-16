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
#include "../Engine/SoundBuffer.hpp"

class Logic : public GameLogic
{
public:

  Logic() : m_tex("data/tileset.png") 
  {
    m_sprite.setTexture(*m_tex, true);
  }
  
  void draw()
  {
    GameLogic::draw();
    getRendow()->draw( m_sprite );
  }

private:

  sf::Sprite m_sprite;
  e::Texture m_tex;
};

class Editor : public wxApp
{
  DECLARE_EVENT_TABLE()

public:

  Editor() : wxApp(), m_sb("data/sound.oog") {}

private:

  bool OnInit()
  {
    m_frame = new wxFrame(NULL, wxID_ANY, wxT("Color Project Editor"));
    m_frame->Show();
   
    e::SoundBuffer("data/sound.wav");
    m_sound.setBuffer(*m_sb);    
    m_sound.play();
   
    wxSFMLCanvas *canvas = new wxSFMLCanvas(m_frame, wxID_ANY, wxDefaultPosition, wxSize(800,600));
    GameLogic *logic = new Logic;
    canvas->setLogic( logic );
    
    return true;
  }
  
  sf::Sound m_sound;
  e::SoundBuffer m_sb;
  wxFrame* m_frame;
};
BEGIN_EVENT_TABLE(Editor, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)

//*/
