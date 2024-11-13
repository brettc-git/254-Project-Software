#include <wx/wx.h>

class MyApp : public passwordApp
{
public:
  bool OnInit() override;
};
wxIMPLEMENT_APP(MyApp);

class MyFrame : public appFrame {
public:
  MyFrame();
private:
  void OnExit(wxCommandEvent& event);
};

bool MyApp::OnInit()
{
  return true;
}

// HELP MENU
// wxMenu *helpMenu = new wxMenu;

// 
