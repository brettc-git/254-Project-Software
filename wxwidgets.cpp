#include <wx/wx.h>

class MyApp : public passwordApp
{
public:
  bool OnInit() override;
};
wxIMPLEMENT_APP(MyApp);
