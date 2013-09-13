//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "leveldialog.h"

edLEVELDIALOG::edLEVELDIALOG(
  wxWindow* parent, 
  wxWindowID id, 
  const wxString& title, 
  const wxPoint& pos,
  const wxSize& size,
  long style, 
  const wxString& name
) :
  wxDialog(parent, id, title, pos, size, style, name),
  mMustExist(false),
  mAlertIfExist(false)
{
  //wxPanel *rootPanel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *rootSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(rootSizer);
  rootSizer->Add( new wxListBox(this, wxID_ANY), 1, wxEXPAND|wxALL, 5);
  
  wxPanel *filenamePanel = new wxPanel(this, wxID_ANY);
  rootSizer->Add(filenamePanel, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 5);
  wxBoxSizer *filenameSizer = new wxBoxSizer(wxHORIZONTAL);
  filenamePanel->SetSizer(filenameSizer);
  filenameSizer->Add( new wxStaticText(filenamePanel, wxID_ANY, wxT("Nom du niveau : ")), 0, wxCENTER );
  filenameSizer->AddSpacer(5);
  mLevelName = new wxTextCtrl(filenamePanel, wxID_ANY);
  filenameSizer->Add(mLevelName, 1, wxEXPAND );
  
  wxPanel *buttonPanel = new wxPanel(this, wxID_ANY);
  rootSizer->Add(buttonPanel, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxBOTTOM, 5);
  //wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
  wxStdDialogButtonSizer *buttonSizer = CreateStdDialogButtonSizer(0);
  buttonSizer->AddButton( new wxButton(buttonPanel, wxID_CANCEL, wxT("Annuler")) );
  buttonSizer->AddButton(new wxButton(buttonPanel, wxID_OK, wxT("Valider")));
  buttonSizer->Realize();
  buttonPanel->SetSizer(buttonSizer);
  //buttonPanel->SetSizer(buttonSizer);
  //buttonSizer->Add( new wxButton(buttonPanel, wxID_CANCEL, wxT("Annuler")), 0);
  //buttonSizer->AddSpacer(5);
  //buttonSizer->Add( new wxButton(buttonPanel, wxID_OK, wxT("Valider")), 0);
}
  
wxString edLEVELDIALOG::LevelName() const
{
  return mLevelName->GetValue();
}

void edLEVELDIALOG::SetLevelName(const wxString& levelName)
{
  mLevelName->SetValue(levelName);
}

bool edLEVELDIALOG::MustExist() const
{
  return mMustExist;
}

void edLEVELDIALOG::SetMustExist(bool value)
{
  mMustExist = value;
}

bool edLEVELDIALOG::AlertIfExist() const
{
  return mAlertIfExist;
}

void edLEVELDIALOG::SetAlertIfExist(bool value)
{
  mAlertIfExist = value;
}
  
