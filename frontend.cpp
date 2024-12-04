#include "password.h"
#include <wx/wx.h>
#include <wx/numdlg.h>
#include <fstream>


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
	void OnSettings(wxCommandEvent& event);
	void OnCheckbox(wxCommandEvent& event);
	void OnGeneratePassword(wxCommandEvent& event);
	void OnBatchPassword(wxCommandEvent& event);
};

bool App::OnInit()
{
	Frame* window = new Frame("Password Strength Checker");
	window->Show(true);
	return true;
}

// Password Generator Length
// auto dialog = wxNumberEntryDialog {this, "", "Password Length", "Generate Passwords"

enum {
	wxID_BATCHPASSWORD = wxID_HIGHEST + 1,
	wxID_SETTINGS = wxID_HIGHEST + 2, 
};

Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* top_text = new wxStaticText(panel, wxID_ANY, "Password Strength Checker and Generator", wxDefaultPosition, wxDefaultSize);
	
	// Configure the text 
	wxFont font = top_text->GetFont();
	font.SetPointSize(32);
	top_text->SetFont(font);

	sizer->Add(top_text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);


	sizer->AddStretchSpacer(1);

	// Textbox for password 
	wxTextCtrl* textbox = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(450,-1), wxTE_CENTRE); // Increase size
	textbox->SetHint("Enter password..."); // Placeholder text
	sizer->Add(textbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

	// Checkbox to show password 
	wxCheckBox* hidePasswordCheckbox = new wxCheckBox(panel, wxID_ANY, "Show Password");
	sizer->Add(hidePasswordCheckbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

	// Button below to generate a random password on text bar
	wxButton* GeneratePasswordButton = new wxButton(panel, wxID_ANY, "Generate Random Password");
	sizer->Add(GeneratePasswordButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	GeneratePasswordButton->Bind(wxEVT_BUTTON, &Frame::OnGeneratePassword, this);

	// Button below the first that displays a dialog to generate batch of passwords on a txt file.

	wxButton* BatchPasswordButton = new wxButton(panel, wxID_ANY, "Batch Password Generator");
	sizer->Add(BatchPasswordButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	BatchPasswordButton->Bind(wxEVT_BUTTON, &Frame::OnBatchPassword, this);

	sizer->AddStretchSpacer(1);

	panel->SetSizer(sizer);
	sizer->Fit(this);

	wxMenuBar* menuBar = new wxMenuBar;

	wxMenu* menuFile = new wxMenu;
	wxMenu* menuEdit = new wxMenu;
	wxMenu* menuHelp = new wxMenu;


	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT);

	// Set up Edit portion of Menu Bar 
	// menuEdit->Append(wxID_SETTINGS, "Settings");
	// Bind(wxEVT_MENU, &Frame::OnSettings, this);

	// Menu bar help  implementation 
	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);
	
	
	 
	
	
	SetMenuBar(menuBar);

	
}
// About/Credits function 
void Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Team Members: ------------------");
}

// Exit function 
void Frame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void Frame::OnSettings(wxCommandEvent& event) {
	//
}
// On checkbox, hide text on textctrl
void Frame::OnCheckbox(wxCommandEvent& event)
{
	
}

// Press button to generate a random password
void Frame::OnGeneratePassword(wxCommandEvent& event) {
	/*wxString::FromUTF8(passwordGenerator(18))*/
}

void Frame::OnBatchPassword(wxCommandEvent& event) {
	// The password length dialog

	wxNumberEntryDialog dialog1(nullptr, "Enter the following: ", "Password Length: ", "Batch Password Generator", 12, 1, 100);

	if (dialog1.ShowModal() == wxID_OK) {
		int passwordLength = dialog1.GetValue();

		// The number of passwords dialog														
		wxNumberEntryDialog dialog2(nullptr, "", "Number of Passwords", "Batch Password Generator", 5, 1, 100);
																								// default, minimum, maximum
		if (dialog2.ShowModal() == wxID_OK) {
			int passwordCount = dialog2.GetValue();
			wxString passwords;

			// Have myfile name be dynamic
			std::ofstream Myfile("passwords.txt");
			if (!Myfile.is_open()) {
				std::cerr << "File not found. Error.";
			}


			for (int i = 0; i < passwordCount; i++) {
				
				passwords += wxString::FromUTF8(passwordGenerator(passwordLength)) + "\n";
				// Append each password on a line
				Myfile << passwordGenerator(passwordLength) << std::endl;
			}

			// Close file
			Myfile.close();

			wxMessageBox("Passwords will show up on passwords.txt", "Generated Passwords successfully.", wxOK | wxICON_INFORMATION);
		}
	}
	
	
 }


wxIMPLEMENT_APP(App);

