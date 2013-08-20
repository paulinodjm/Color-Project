//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <wx/wx.h>
#include "wxSFMLCanvas.hpp"

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
   
    wxSFMLCanvas *canvas = new wxSFMLCanvas(m_frame, wxID_ANY, wxDefaultPosition, wxSize(800,600));
    
    return true;
  }
  
  int OnExit()
  {
    return wxApp::OnExit();
  }
  
  wxFrame* m_frame;
};
BEGIN_EVENT_TABLE(Editor, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)

//*/
