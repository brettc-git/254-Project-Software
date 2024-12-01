// Implement Somewhere else Later

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
	Frame* window = new Frame("Password Strength Checker");
	window->Show(true);
	return true;
}

// Password Generator Length
// auto dialog = wxNumberEntryDialog {this, "", "Password Length", "Generate Passwords"


Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	// 
	wxTextCtrl* textbox = new wxTextCtrl(panel, wxID_ANY, "Enter password...");
	// Checkbox to show password 
	wxCheckBox* showPasswordCheckbox = new wxCheckBox(panel, wxID_ANY, "Show Password");

	sizer->Add(textbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
	panel->SetSizer(sizer);
	sizer->Fit(this);

	wxMenuBar* menuBar = new wxMenuBar;

	wxMenu* menu = new wxMenu;

	menuBar->Append(menu, "&File");


	menu->AppendSeparator();
	menu->Append(wxID_EXIT);
	// Menu bar implementation 


	wxMenu* menuEdit = new wxMenu;

	wxMenu* menuHelp = new wxMenu;

	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);
	Bind(wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT);
}

void Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Team Members: Brett Chiu, Rene Acosta, Cristian Victorio");
}

// Exit function 
void Frame::OnExit(wxCommandEvent& event) {
	Close(true);
}

// void function that happens when file is done loading passwords
// wxMessageBox("Passwords successfully generated.", wxOK | wxICON_INFORMATION)l;
wxIMPLEMENT_APP(App);


