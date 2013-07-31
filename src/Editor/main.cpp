#include <wx/wx.h>

class Editor : public wxApp
{
  bool OnInit()
  {
    wxFrame* frame = new wxFrame(NULL, wxID_ANY, _T("Color Project Editor"));
    wxPanel* panel = new wxPanel(frame);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);
    sizer->Add( new wxStaticText(panel, wxID_ANY, _T("Coming soon!")), 1, wxALIGN_CENTER );
    frame->Show();
    return true;
  }
};
IMPLEMENT_APP(Editor)

