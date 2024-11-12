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

}

bool MyApp::OnInit()
{
  return true;
}
