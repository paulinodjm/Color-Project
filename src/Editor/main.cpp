//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <wx/wx.h>
#include "wxSFMLCanvas.hpp"
#include "../Game/gametypes.h"
#include "../Engine/level.h"
#include "../Engine/objectfactory.h"
#include "../Engine/contentmanager.h"
#include "../Engine/filesystem.h"
#include <map>
#include <string>
#include <limits>
#include <wx/spinctrl.h>
#include <SFML/Graphics/Rect.hpp>

using namespace std;

void InitGameTypes(map<string, OBJECTFACTORY*>& gameTypes)
{
  #define GAMETYPE(type) gameTypes.insert( pair<string, OBJECTFACTORY*>( #type, new TOBJECTFACTORY<type> ) )
  GAMETYPE(PLAYER);
  GAMETYPE(STATICOBJECT);
  #undef GAMETYPE
}

class Editor : public wxApp
{
  DECLARE_EVENT_TABLE()

public:

  Editor() : wxApp() {}

private:

  bool OnInit()
  {
    if (!FS::Init( wxString(argv[0]).mb_str() ) || !FS::Mount("data", "data"))
    {
      return false;
    }
  
    InitGameTypes(mGameTypes);
  
    mFrame = new wxFrame(NULL, wxID_ANY, wxT("Color Project Editor"),
      wxDefaultPosition, wxSize(950,600));
   
    wxBoxSizer *hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    mFrame->SetSizer(hBoxSizer);
    
    mCanvas = new wxSFMLCanvas(mFrame, wxID_ANY);
    hBoxSizer->Add(mCanvas, 1, wxEXPAND);
    
    mCanvas->SetLevel(new LEVEL);
    if (
      !mCanvas->Level()->Load("data/levels/objects.json", mContentManager, mGameTypes)
      || !mCanvas->Level()->PerformLoading(mContentManager)
    ){
      wxMessageBox(wxT("Le chargement du niveau à échoué"), wxT("Erreur"), wxICON_ERROR);
      return false;
    }
    mCanvas->Level()->Init();
    
    PLAYER* player = dynamic_cast<PLAYER*>( mCanvas->Level()->Object("player") );
    if (!player)
    {
      wxMessageBox(wxT("Pas de 'player' dans le niveau!"), wxT("Erreur"), wxICON_ERROR);
      return false;
    }
    
    wxPanel *panel = new wxPanel(mFrame, wxID_ANY);
    panel->SetMinSize(wxSize(150, 50));
    hBoxSizer->Add(panel, 0, wxEXPAND);
    
    wxBoxSizer *vBoxSizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(vBoxSizer);
    
    mSpinX = new wxSpinCtrl(panel, 1);
    mSpinY = new wxSpinCtrl(panel, 1);
    mSpinX->SetRange(numeric_limits<int>::min(), numeric_limits<int>::max());
    mSpinY->SetRange(numeric_limits<int>::min(), numeric_limits<int>::max());
    mSpinX->SetValue(static_cast<int>(player->Position().x));
    mSpinY->SetValue(static_cast<int>(player->Position().y));
    mResult = new wxStaticText(panel, wxID_ANY, wxT("Résultat..."));
    
    vBoxSizer->Add(mSpinX , 0, wxEXPAND);
    vBoxSizer->Add(mSpinY , 0, wxEXPAND);
    vBoxSizer->Add(mResult, 0, wxEXPAND);
    
    mFrame->Center();
    mFrame->Show();
    return true;
  }
  
  int OnExit()
  {
    return wxApp::OnExit();
  }
  
  void Test(wxSpinEvent& event)
  {
    PLAYER* player = dynamic_cast<PLAYER*>(mCanvas->Level()->Object("player"));
    if (player)
    {
      player->SetPosition( 
        static_cast<float>(mSpinX->GetValue()), 
        static_cast<float>(mSpinY->GetValue())
      );
      mCanvas->Level()->PerformCollisions();
      
      sf::FloatRect bBox = player->Bbox();
      wxString label;
      label << wxT("Bbox : \n  left=") << static_cast<int>(bBox.left)
      << wxT("\n  top=") << static_cast<int>(bBox.top)
      << wxT("\n  left=") << static_cast<int>(bBox.left+bBox.width)
      << wxT("\n  bottom=") << static_cast<int>(bBox.top+bBox.height);
      
      if (!mCanvas->Level()->Tilemap()->PlaceFree(bBox))
      {
        label << wxT("\nCollision!");
      }
      
      mResult->SetLabel(label);
    }
  }
  
  wxFrame* mFrame;
  map<string, OBJECTFACTORY*> mGameTypes;
  CONTENTMANAGER mContentManager;
  wxSpinCtrl *mSpinX, *mSpinY;
  wxStaticText *mResult;
  wxSFMLCanvas *mCanvas;
  
};
BEGIN_EVENT_TABLE(Editor, wxApp)
  EVT_SPINCTRL(1, Editor::Test)
END_EVENT_TABLE()

IMPLEMENT_APP(Editor)

//*/
