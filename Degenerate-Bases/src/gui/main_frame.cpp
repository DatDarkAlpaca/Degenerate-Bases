#include "pch.h"
#include "main_frame.h"

dgn::DegenerateBaseFrame::DegenerateBaseFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainFrame(parent, id, title, pos, size, style)
{
	SetLabel(title);

	PrepareMenu();

	CreateVirtualList();
	ModifyGenerateButton();

	Layout();
}

void dgn::DegenerateBaseFrame::PrepareMenu()
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

void dgn::DegenerateBaseFrame::CreateVirtualList()
{
	wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);
	listPanel->SetSizer(listSizer);

	m_ResultListCtrl = new VirtualList(listPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
									   wxBORDER_DEFAULT | wxLC_HRULES | wxLC_REPORT | 
									   wxLC_VIRTUAL | wxLC_VRULES);
	
	listSizer->Add(m_ResultListCtrl, 1, wxALL | wxEXPAND, 1);
}

void dgn::DegenerateBaseFrame::DisplayInformation()
{
	generationResultsTable->ClearAll();
	generationResultsTable->InsertColumn(0, _("Property"));
	generationResultsTable->InsertColumn(1, _("Value"));

	AddInformation("Writing time", std::to_string(Data::writeFastaTime) + "ms");

	AddInformation("Permutation time", std::to_string(Data::permutationTime) + "ms");

	AddInformation("Iterations:", std::to_string(Data::iterations));

	AddInformation("Outcomes:", std::to_string(Data::outcomes));

	AddInformation("Sequence's length:", std::to_string(Data::sequence.size()));

	// Todo: unmatched bases error.
}

void dgn::DegenerateBaseFrame::ModifyGenerateButton()
{
	generateButton->SetId(ID_INPUT_BTN);
	Bind(wxEVT_BUTTON, &DegenerateBaseFrame::ButtonGenerate, this, ID_INPUT_BTN);
}

void dgn::DegenerateBaseFrame::AddInformation(std::string&& name, std::string&& value, bool isWarning, bool isError)
{
	long index = generationResultsTable->InsertItem(0, name);
	generationResultsTable->SetItem(index, 1, value);

	// Todo: change these colors.
	if (isWarning)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 51, 51));

	if(isError)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 210, 51));
}

void dgn::DegenerateBaseFrame::SetInformation(std::string&& name, std::string&& value, bool isWarning, bool isError)
{
	generationResultsTable->ClearAll();
	generationResultsTable->InsertColumn(0, _("Property"));
	generationResultsTable->InsertColumn(1, _("Value"));

	long index = generationResultsTable->InsertItem(0, name);
	generationResultsTable->SetItem(index, 1, value);

	// Todo: change these colors.
	if (isWarning)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 51, 51));

	if (isError)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 210, 51));
}

void dgn::DegenerateBaseFrame::ButtonGenerate(wxCommandEvent& event)
{
	Data::Clear();
	m_ResultListCtrl->Clear();

	SRWA::CreateDefault();

	// Sequence:
	Data::sequence = inputCtrl->GetValue();
	InputHandler::SanitizeInput();

	if (Data::invalidSequence)
	{
		SetInformation("Invalid Sequence", "The input sequence is invalid.", true, false);
		return;
	}

	// SBI:
	if (!Data::anyDegenerate)
		return Permutator::SimpleBaseInsertion();

	// Fasta:
	auto dir = Settings::Get("results", "directory")
		+ Settings::Get("results", "prefix")
		+ std::to_string(Settings::CountFiles()) + "."
		+ Settings::Get("results", "format");

	SRWA::Open(dir);

	Permutator::Preparation();

	high_resolution_clock::time_point begin = high_resolution_clock::now();
	Permutator::LazyPermutation();
	high_resolution_clock::time_point end = high_resolution_clock::now();

	SRWA::Close();

	// Displaying:
	auto results = SRWA::Read(dir);
	m_ResultListCtrl->SetItems(results);

	Data::permutationTime = duration_cast<nanoseconds>(end - begin).count() / 1000000;

	DisplayInformation();
}
