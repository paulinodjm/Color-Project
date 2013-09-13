//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "frame.h"
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/aboutdlg.h>
#include "id.h"
#include "leveldialog.h"

BEGIN_EVENT_TABLE(edFRAME, wxFrame)
  EVT_SIZE(edFRAME::OnResize)
  EVT_MENU(static_cast<int>(edID::New), edFRAME::OnNew)
  EVT_MENU(static_cast<int>(edID::Open), edFRAME::OnOpen)
  EVT_MENU(static_cast<int>(edID::Save), edFRAME::OnSave)
  EVT_MENU(static_cast<int>(edID::SaveAs), edFRAME::OnSaveAs)
  EVT_MENU(static_cast<int>(edID::Exit), edFRAME::OnExit)
  EVT_MENU(static_cast<int>(edID::Help), edFRAME::OnHelp)
  EVT_MENU(static_cast<int>(edID::About), edFRAME::OnAbout)
END_EVENT_TABLE()

edFRAME::edFRAME(
  wxWindow* parent,
  wxWindowID id,
  const wxString& title,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxString& name
)
  : wxFrame(parent, id, title, pos, size, style, name),
  mDataModel(nullptr)
{
  SetupMenuBar();
}

void edFRAME::SetupMenuBar()
{
  wxMenuBar *menuBar = new wxMenuBar;
  wxMenu *menu(nullptr);
  
  // file menu
  menu = new wxMenu;
  menu->Append(static_cast<int>(edID::New), wxT("Nouveau"), wxT("Nouveau niveau") );
  menu->Append(static_cast<int>(edID::Open), wxT("Ouvrir"), wxT("Ouvrir un niveau") );
  menu->Append(static_cast<int>(edID::Save), wxT("Sauvegarder"), wxT("Sauvegarder le niveau") );
  menu->Append(static_cast<int>(edID::SaveAs), wxT("Sauvegarder sous"), wxT("Sauvegarder le niveau sous un autre nom") );
  menu->AppendSeparator();
  menu->Append(static_cast<int>(edID::Exit), wxT("Quitter"), wxT("Quitter l'éditeur") );
  menuBar->Insert(0, menu, wxT("Fichier"));
  // edition menu
  menu = new wxMenu;
  menu->Append(static_cast<int>(edID::Undo), wxT("Annuler"), wxT("Annule la dernière action") );
  menu->Append(static_cast<int>(edID::Redo), wxT("Rétablir"), wxT("Rétabli la dernière action annulée") );
  menuBar->Insert(1, menu, wxT("Édition"));
  // tool menu
  menu = new wxMenu;
  menu->Append(static_cast<int>(edID::EditTilemap), wxT("Mode tilemap"), wxT("Éditer la tilemap") );
  menu->Append(static_cast<int>(edID::EditObjects), wxT("Mode objets"), wxT("Placer des objets") );
  menu->AppendSeparator();
  menu->Append(static_cast<int>(edID::Preview), wxT("Prévisualisation"), wxT("Lancer le niveau dans une autre fenêtre") );
  menuBar->Insert(2, menu, wxT("Outils"));
  // help menu
  menu = new wxMenu;
  menu->Append(static_cast<int>(edID::Help), wxT("Aide"));
  menu->Append(static_cast<int>(edID::About), wxT("À propos"));
  menuBar->Insert(3, menu, wxT("?"));
   
  SetMenuBar(menuBar);
}

bool edFRAME::AddFrameListener(edFRAMELISTENER* listener)
{
  if (!listener) return false;
  
  return mListeners.insert(listener).second;
}

bool edFRAME::DeleteFrameListener(edFRAMELISTENER* listener)
{
  return mListeners.erase(listener) == 1;
}

void edFRAME::ClearFrameListeners()
{
  mListeners.clear();
}

edDATAMODEL *edFRAME::DataModel() const
{
  return mDataModel;
}

void edFRAME::SetDataModel(edDATAMODEL* model)
{
  mDataModel = model;
} 

void edFRAME::OnResize(wxSizeEvent& event)
{
  for (edFRAMELISTENER* listener : mListeners)
  {
    listener->OnFrameResized(this, event.GetSize());
  }
}

void edFRAME::OnNew(wxCommandEvent& event)
{
  if (mDataModel && wxMessageBox(wxT("Êtes vous sûr de vouloir créer un nouveau niveau?\n"
    "Les modifications non sauvegardée du niveau actuel seront perdues."), wxT("Nouveau"), wxYES_NO, this) == wxYES)
  {
    mDataModel->NewLevel();
  }
}

void edFRAME::OnOpen(wxCommandEvent& event)
{
  edLEVELDIALOG *dialog = new edLEVELDIALOG(this, wxID_ANY, wxT("Ouvrir un niveau"));
  dialog->SetLevelName(wxT("Niveau 1"));
  dialog->ShowModal();
  dialog->Destroy();
}

void edFRAME::OnSave(wxCommandEvent& event)
{
}

void edFRAME::OnSaveAs(wxCommandEvent& event)
{
}

void edFRAME::OnExit(wxCommandEvent& event)
{
  if (wxMessageBox(wxT("Quitter l'éditeur?"), wxT("Quitter"), wxYES_NO|wxICON_QUESTION, this) == wxYES)
  {
    Close();
  }
}

void edFRAME::OnHelp(wxCommandEvent& event)
{
  wxMessageBox(wxT("Aucune aide disponible actuellement."), wxT("Aide"), wxOK, this);
}

void edFRAME::OnAbout(wxCommandEvent& event)
{
  wxAboutDialogInfo info;
  info.SetName(wxT("Color Project Editor"));
  info.SetCopyright(wxT("Copyright (C) 2013 Marié Paulino"));
  info.AddDeveloper(wxT("Marié Paulino"));
  wxAboutBox(info);
}

