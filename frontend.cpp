#include "password.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/numdlg.h>
#include <wx/splitter.h>
#include <wx/checkbox.h>
#include <fstream>


class App : public wxApp {
public:
	virtual bool OnInit();
};

class Frame : public wxFrame {
public:
	Frame(const wxString& title);
private:
	wxTextCtrl* textbox;
	int passwordLength = 12;

	// For settings
	bool includeSingleSpecial = true;
	bool includeSingleNumbers = true;
	bool includeSingleUppercase = true;
	bool includeBatchSpecial = true;
	bool includeBatchNumbers = true;
	bool includeBatchUppercase = true;

	// Event functions
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);
	void OnGeneratePassword(wxCommandEvent& event);
	void OnBatchPassword(wxCommandEvent& event);
};

bool App::OnInit()
{
	Frame* window = new Frame("Random Password Generator and Strength Tester");
	window->Show(true);
	return true;
}

enum {
	wxID_BATCHPASSWORD = wxID_HIGHEST + 1,
	wxID_SETTINGS = wxID_HIGHEST + 2,
};

Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

	// Split program panel into both windows; we would usually use wxPanel but a splitter is added for the textctrl, and the password prereqs
	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY);
	wxPanel* leftPanel = new wxPanel(splitter, wxID_ANY);
	wxPanel* rightPanel = new wxPanel(splitter, wxID_ANY);
	splitter->SplitVertically(leftPanel, rightPanel);
	splitter->SetSashGravity(0.6);

	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	leftPanel->SetSizer(leftSizer);
	rightPanel->SetSizer(rightSizer);

	// Add flags on the right
	wxStaticText* hasNumberFlag = new wxStaticText(rightPanel, wxID_ANY, "Has at least one numeric character: X");
	wxStaticText* hasUppercaseCharacterFlag = new wxStaticText(rightPanel, wxID_ANY, "Has at least one uppercase Letter: X");
	wxStaticText* hasSpecialCharacterFlag = new wxStaticText(rightPanel, wxID_ANY, "Has at least one special character : X");

	rightSizer->Add(hasNumberFlag, 0, wxALL, 10);
	rightSizer->Add(hasUppercaseCharacterFlag, 0, wxALL, 10);
	rightSizer->Add(hasSpecialCharacterFlag, 0, wxALL, 10);


	// Title
	wxStaticText* top_text = new wxStaticText(leftPanel, wxID_ANY, "Password Strength Tester and Generator", wxDefaultPosition, wxDefaultSize);

	// Configure the text 
	wxFont font = top_text->GetFont();
	font.SetPointSize(32);
	top_text->SetFont(font);

	leftSizer->Add(top_text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);


	leftSizer->AddStretchSpacer(1);

	// Textbox for password 
	textbox = new wxTextCtrl(leftPanel, wxID_ANY, "", wxDefaultPosition, wxSize(450, -1), wxTE_CENTRE); // Increase size
	textbox->SetHint("Enter password..."); // Placeholder text
	leftSizer->Add(textbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

	// Bind textbox's text to the flags for each condition fulfilled, O if fulfilled, X if not
	textbox->Bind(wxEVT_TEXT, [=](wxCommandEvent& event) {
		std::string password = textbox->GetValue().ToStdString();

		hasNumberFlag->SetLabelText("Has at least one numeric character: " + std::string(containsNumber(password) ? "O" : "X"));
		hasUppercaseCharacterFlag->SetLabelText("Has at least one uppercase Letter: " + std::string(containsUpper(password) ? "O" : "X"));
		hasSpecialCharacterFlag->SetLabelText("Has at least one special character: " + std::string(containsSpecial(password) ? "O" : "X"));
		});

	// Button below to generate a random password on text bar
	wxButton* GeneratePasswordButton = new wxButton(leftPanel, wxID_ANY, "Generate Random Password");
	leftSizer->Add(GeneratePasswordButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	GeneratePasswordButton->Bind(wxEVT_BUTTON, &Frame::OnGeneratePassword, this);

	// Button below the first that displays a dialog to generate batch of passwords on a txt file.

	wxButton* BatchPasswordButton = new wxButton(leftPanel, wxID_ANY, "Batch Password Generator");
	leftSizer->Add(BatchPasswordButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	BatchPasswordButton->Bind(wxEVT_BUTTON, &Frame::OnBatchPassword, this);

	leftSizer->AddStretchSpacer(1);

	leftSizer->Fit(this);
	rightSizer->Fit(this);

	// Create menu bar on top
	wxMenuBar* menuBar = new wxMenuBar;

	wxMenu* menuFile = new wxMenu;
	wxMenu* menuEdit = new wxMenu;
	wxMenu* menuHelp = new wxMenu;


	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");
	menuFile->AppendSeparator(); // Equivalent to horizontal line
	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &Frame::OnExit, this, wxID_EXIT);

	// Set up Edit portion of Menu Bar 
	menuEdit->Append(wxID_SETTINGS, "&Settings");
	Bind(wxEVT_MENU, &Frame::OnSettings, this, wxID_SETTINGS);

	// Menu bar help  implementation 
	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);

	SetMenuBar(menuBar);


}
// About/Credits function 
void Frame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Team Members: Cristian Victorio, Rene Acosta, Brett Chiu");
}

// Exit function 
void Frame::OnExit(wxCommandEvent& event) {
	Close(true);
}

// Settings Dialog
void Frame::OnSettings(wxCommandEvent& event) {        // May change wxDefaultSize to something else
	wxDialog settings(this, wxID_ANY, "Settings", wxDefaultPosition, wxSize(400, 500));

	wxBoxSizer* settingsSizer = new wxBoxSizer(wxVERTICAL);

	// Random Password Generator Settings

	wxStaticText* randomGeneratorText = new wxStaticText(&settings, wxID_ANY, "Random Password Generator Settings:");
	wxFont Font1 = randomGeneratorText->GetFont();
	Font1.SetPointSize(14);
	randomGeneratorText->SetFont(Font1);

	settingsSizer->Add(randomGeneratorText, 0, wxALIGN_LEFT | wxALL, 10);

	// Checkboxes for including characters in the random password generator
	wxCheckBox* includeSingleSpecial = new wxCheckBox(&settings, wxID_ANY, "Include Special Characters");
	wxCheckBox* includeSingleNumbers = new wxCheckBox(&settings, wxID_ANY, "Include Numbers");
	wxCheckBox* includeSingleUppercase = new wxCheckBox(&settings, wxID_ANY, "Include Uppercase Characters");

	// Set all of these to true by default
	includeSingleSpecial->SetValue(this->includeSingleSpecial);
	includeSingleNumbers->SetValue(this->includeSingleNumbers);
	includeSingleUppercase->SetValue(this->includeSingleUppercase);

	// Add to sizer
	settingsSizer->Add(includeSingleSpecial, 0, wxALIGN_LEFT | wxALL, 5);
	settingsSizer->Add(includeSingleNumbers, 0, wxALIGN_LEFT | wxALL, 5);
	settingsSizer->Add(includeSingleUppercase, 0, wxALIGN_LEFT | wxALL, 5);

	// Add the number entry box for random password generator
	// We use a different type of spacer for the dialog window

	wxStaticText* passwordLengthText = new wxStaticText(&settings, wxID_ANY, "Random Password Length (single): ");
	settingsSizer->Add(passwordLengthText, 0, wxALIGN_LEFT | wxALL, 10);

	wxSpinCtrl* setPasswordLength = new wxSpinCtrl(&settings, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	setPasswordLength->SetRange(1, 100);
	setPasswordLength->SetValue(passwordLength);
	settingsSizer->Add(setPasswordLength, 0, wxALIGN_LEFT | wxALL, 10);



	settingsSizer->AddSpacer(20);

	// Batch Password Generator Settings

	wxStaticText* batchGeneratorText = new wxStaticText(&settings, wxID_ANY, "Batch Password Generator Settings:");
	wxFont Font2 = batchGeneratorText->GetFont();
	Font2.SetPointSize(14);
	batchGeneratorText->SetFont(Font2);

	settingsSizer->Add(batchGeneratorText, 0, wxALIGN_LEFT | wxALL, 10);

	// Checkboxes for including characters in the batch passwords.


	wxCheckBox* includeBatchSpecial = new wxCheckBox(&settings, wxID_ANY, "Include Special Characters");
	wxCheckBox* includeBatchNumbers = new wxCheckBox(&settings, wxID_ANY, "Include Numbers");
	wxCheckBox* includeBatchUppercase = new wxCheckBox(&settings, wxID_ANY, "Include Uppercase Characters");

	settingsSizer->Add(includeBatchSpecial, 0, wxALIGN_LEFT | wxALL, 5);
	settingsSizer->Add(includeBatchNumbers, 0, wxALIGN_LEFT | wxALL, 5);
	settingsSizer->Add(includeBatchUppercase, 0, wxALIGN_LEFT | wxALL, 5);

	// Set all of these 
	includeBatchSpecial->SetValue(this->includeBatchSpecial);
	includeBatchNumbers->SetValue(this->includeBatchNumbers);
	includeBatchUppercase->SetValue(this->includeBatchUppercase);


	settingsSizer->AddSpacer(20);

	// OK and Cancel button
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* OK = new wxButton(&settings, wxID_OK, "OK");
	wxButton* Cancel = new wxButton(&settings, wxID_CANCEL, "Cancel");
	buttonSizer->Add(OK, 0, wxALL, 5);
	buttonSizer->Add(Cancel, 0, wxALL, 5);

	settingsSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL);

	settings.SetSizer(settingsSizer);
	settings.Centre();


	if (settings.ShowModal() == wxID_OK) {
		this->includeSingleSpecial = includeSingleSpecial->IsChecked();
		this->includeSingleNumbers = includeSingleNumbers->IsChecked();
		this->includeSingleUppercase = includeSingleUppercase->IsChecked();
		this->includeBatchSpecial = includeBatchSpecial->IsChecked();
		this->includeBatchNumbers = includeBatchNumbers->IsChecked();
		this->includeBatchUppercase = includeBatchUppercase->IsChecked();
		// Get password length
		passwordLength = setPasswordLength->GetValue();
	}
}


// Press button to generate a random password
void Frame::OnGeneratePassword(wxCommandEvent& event) {
	std::string password = passwordGenerator(passwordLength, includeSingleUppercase, includeSingleNumbers, includeSingleSpecial);
	textbox->SetValue(wxString::FromUTF8(password)); // Set textbox with generated password
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

			std::ofstream Myfile("passwords.txt");
			if (!Myfile.is_open()) {
				std::cerr << "File not found. Error.";
			}


			for (int i = 0; i < passwordCount; i++) {

				passwords += wxString::FromUTF8(passwordGenerator(passwordLength, includeBatchUppercase, includeBatchNumbers, includeBatchSpecial)) + "\n";
				// Append each password on a line
				Myfile << passwordGenerator(passwordLength, includeBatchUppercase, includeBatchNumbers, includeBatchSpecial) << std::endl;
			}

			// Close file
			Myfile.close();

			wxMessageBox("Passwords will show up on passwords.txt", "Generated Passwords successfully.", wxOK | wxICON_INFORMATION);
		}
	}


}


wxIMPLEMENT_APP(App);
