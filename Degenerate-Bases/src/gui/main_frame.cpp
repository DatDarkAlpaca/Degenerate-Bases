#include "pch.h"
#include "data.h"
#include "main_frame.h"
#include "../input/input.h"
#include "../permutator/permutator.h"
#include "../fasta/chunk.h"

dgn::MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, "Degenerate Bases v5.0", wxDefaultPosition, wxSize(600, 400))
{
	PrepareMenu();

	PrepareInput();
}

void dgn::MainFrame::PrepareMenu()
{
	wxMenu* menuFile = new wxMenu;

	// File Menu:
	menuFile->Append(ID_NEW, "&New...\tCtrl+N");
	menuFile->Append(ID_OPEN, "&Open...\tCtrl+O");
	menuFile->Append(ID_SAVE, "&Save\tCtrl+S");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	// Help Menu:
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	// Menu Bar:
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	// Bindings:
	Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); }, wxID_EXIT);

	SetMenuBar(menuBar);
}

void dgn::MainFrame::PrepareInput()
{
	// Instances:
	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
													  wxSP_BORDER | wxSP_LIVE_UPDATE);
	wxPanel* inputPanel = new wxPanel(splitter);
	wxPanel* resultsPanel = new wxPanel(splitter);
	
	// Panel Color:
	inputPanel->SetBackgroundColour(wxColor(200, 100, 100));
	resultsPanel->SetBackgroundColour(wxColor(100, 200, 100));

	// Sizer:
	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* resultsSizer = new wxBoxSizer(wxVERTICAL);

	// TextControl & Generate Button:
	m_Input = new wxTextCtrl(inputPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	wxButton* generateButton = new wxButton(inputPanel, ID_INPUT_BTN, "Generate");

	// List:
	m_ResultsList = new VirtualList(resultsPanel, wxID_ANY, wxDefaultPosition, wxSize(0, 800));

	// Input Sizer:
	inputSizer->Add(m_Input, 5, 0, wxALIGN_CENTRE_HORIZONTAL);
	inputSizer->Add(generateButton, 1, 0, wxALIGN_CENTRE_HORIZONTAL);
	inputPanel->SetSizer(inputSizer);

	// Results Sizer:
	resultsSizer->Add(m_ResultsList, 0, wxEXPAND, 0);
	resultsPanel->SetSizer(resultsSizer);

	// Binding:
	Bind(wxEVT_BUTTON, &MainFrame::ButtonGenerate, this, ID_INPUT_BTN);

	// Splitting:
	splitter->SetMinimumPaneSize(200);
	splitter->SplitVertically(inputPanel, resultsPanel);
}

void dgn::MainFrame::ButtonGenerate(wxCommandEvent& event)
{
	// Clear the list
	// Todo: history list.
	m_ResultsList->Clear();

	Data::sequence = m_Input->GetValue();

	InputHandler::SanitizeInput();

	Permutator::Execute();

	for (const auto& element : Chunk::data)
		m_ResultsList->AddItem(0, element, true);

	Chunk::Clear();

	Data::Clear();
}

