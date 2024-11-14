#include <wx/wx.h>

class App : public wxApp {
public:
	virtual bool OnInit();
};

class Frame : public wxFrame {
public:
	Frame(const wxString& title);
private:
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
};

bool App::OnInit()
{
	wxFrame* window = new wxFrame(NULL, wxID_ANY, "Password Strength Checker", wxDefaultPosition, wxDefaultSize);
	window->Show();
	return true;
}

Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	// wxCheckBox* showPasswordCheckbox = new wxCheckBox(, wxID_ANY, "Show Password")
	wxMenu* menu = new wxMenu;
	
	// Menu bar implementation 
	wxMenu* menuFile = new wxMenu;
	wxMenu* menuEdit = new wxMenu;
	wxMenu* menuHelp = new wxMenu;
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

}

void Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Team Members: Brett Chiu, Rene Acosta, Cristian Victorio")
}
// Exit function 
void Frame::OnExit(wxCommandEvent& event) {
	Close(true);
}
wxIMPLEMENT_APP(App);


