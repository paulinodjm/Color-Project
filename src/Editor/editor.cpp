//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "editor.h"
#include "../Engine/filesystem.h"
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <jsoncpp/json/json.h>

IMPLEMENT_APP(edEDITOR)

edEDITOR::edEDITOR() : wxApp(), mMainFrame(nullptr)
{}

bool edEDITOR::OnInit()
{
  if (!wxApp::OnInit())
  {
    return false;
  }
  
  if (  !FS::Init(wxString(argv[0]).mb_str())
    ||  !FS::Mount("data", "data")
    ||  !FS::Mount("editordata", "editordata")
  ){
    return false;
  }

  mSettings.Load("editordata/settings.json");

  mMainFrame = new edFRAME(nullptr, wxID_ANY, wxT("Color Project Editor"), wxDefaultPosition, mSettings.WindowSize());
  mMainFrame->AddFrameListener(this);
  mMainFrame->SetDataModel(&mDataModel);
  mMainFrame->Center();
  mMainFrame->Show();
  return true;
}

int edEDITOR::OnExit()
{
  wxFFileOutputStream out(wxT("editordata"));
  wxZipOutputStream zip(out);
  wxTextOutputStream txt(zip);
  
  zip.PutNextEntry(wxT("settings.json"));
  
  Json::FastWriter writer;
  Json::Value settings;
  settings["window-width"] = mSettings.WindowSize().GetWidth();
  settings["window-height"] = mSettings.WindowSize().GetHeight();
  txt << wxString( writer.write(settings).c_str(), wxConvUTF8 );
  
  return wxApp::OnExit();
}

void edEDITOR::OnFrameResized(edFRAME* frame, const wxSize& size)
{
  mSettings.SetWindowSize(size);
}

edFRAME* edEDITOR::MainFrame() const
{
  return mMainFrame;
}

