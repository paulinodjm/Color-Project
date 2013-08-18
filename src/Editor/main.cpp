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
#include "../Engine/SoundPlayer.hpp"

class Logic : public GameLogic
{
public:

  Logic() : m_tex("data/tileset.png")
  {
    e::Texture tex("data/strip.png");
    tex = m_tex;
    m_sprite.setTexture(*tex, true);
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

  Editor() : wxApp() {}

private:

  bool OnInit()
  {
    wxApp::OnInit();
  
    m_frame = new wxFrame(NULL, wxID_ANY, wxT("Color Project Editor"));
    m_frame->Show();
   
    e::SoundPlayer player1;
    e::SoundPlayer player2(e::SoundBuffer("data/sound.oog"));
    player2 = player1;
    player2.setBuffer(e::SoundBuffer("data/sound.wav"));
    player1.setBuffer(e::SoundBuffer("data/sound.wav"));
    player1 = player2;
    m_sound = player1;
    
    m_sound.play();
   
    /*
    wxSFMLCanvas *canvas = new wxSFMLCanvas(m_frame, wxID_ANY, wxDefaultPosition, wxSize(800,600));
    m_logic = new Logic;
    canvas->setLogic( m_logic );
    */
    
    return true;
  }
  
  int OnExit()
  {
    delete m_logic;
    return wxApp::OnExit();
  }
  
  Logic* m_logic;
  e::SoundPlayer m_sound;
  wxFrame* m_frame;
};
BEGIN_EVENT_TABLE(Editor, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)

//*/
