#include "pch.h"
#include "main_frame.h"

dgn::DegenerateBaseFrame::DegenerateBaseFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: MainFrame(parent, id, title, pos, size, style)
{
	SetLabel(title);

	// PrepareMenu();

	CreateVirtualList();
	ModifyGenerateButton();

	Layout();

	Bind(wxEVT_SIZE, &DegenerateBaseFrame::FixListCtrl, this, wxID_ANY);
	Bind(wxEVT_SPLITTER_SASH_POS_CHANGED, &DegenerateBaseFrame::FixListCtrlSash, this, wxID_ANY);
}

void dgn::DegenerateBaseFrame::PrepareMenu()
{
	// Todo: create functions.

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

	wxSizeEvent e;
	FixListCtrl(e);

	AddInformation("Writing time", std::to_string(Data::writeFastaTime) + "ms");

	AddInformation("Permutation time", std::to_string(Data::permutationTime) + "ms");

	AddInformation("Iterations:", std::to_string(Data::iterations));

	AddInformation("Outcomes:", std::to_string(Data::outcomes));

	AddInformation("Sequence's length:", std::to_string(Data::sequence.size()));

	if (Data::cartesianSize != Data::outcomes)
		AddInformation("Unmatched Bases Error!", "The results from this permutation may be imprecise.", false, true);
}

void dgn::DegenerateBaseFrame::ModifyGenerateButton()
{
	generateButton->SetId(ID_INPUT_BTN);
	Bind(wxEVT_BUTTON, &DegenerateBaseFrame::ButtonGenerate, this, ID_INPUT_BTN);
}

void dgn::DegenerateBaseFrame::FillResults(const std::string& dir)
{
	SRWA::Open(dir, std::ios_base::in);

	bool firstLine = true;
	char headerCharacter;
	for (std::string line; std::getline(SRWA::file, line); )
	{
		if (firstLine)
		{
			headerCharacter = line[0];
			firstLine = false;
		}

		if (line[0] != headerCharacter)
			m_ResultListCtrl->AddItem(line);
	}

	SRWA::Close();
}

void dgn::DegenerateBaseFrame::FixListCtrl(wxSizeEvent& event)
{
	if (!m_ResultListCtrl || m_ResultListCtrl->GetColumnCount() == 0)
		return;

	if (!generationResultsTable || generationResultsTable->GetColumnCount() == 0)
		return;
	
	m_ResultListCtrl->SetColumnWidth(1, listPanel->GetSize().GetWidth() - m_ResultListCtrl->GetColumnWidth(0));
	generationResultsTable->SetColumnWidth(1, resultsPanel->GetSize().GetWidth() - generationResultsTable->GetColumnWidth(0));

	event.Skip();
}

void dgn::DegenerateBaseFrame::FixListCtrlSash(wxSplitterEvent& event)
{
	if (!m_ResultListCtrl || m_ResultListCtrl->GetColumnCount() == 0)
		return;

	if (!generationResultsTable || generationResultsTable->GetColumnCount() == 0)
		return;

	m_ResultListCtrl->SetColumnWidth(1, listPanel->GetSize().GetWidth() - m_ResultListCtrl->GetColumnWidth(0));
	generationResultsTable->SetColumnWidth(1, resultsPanel->GetSize().GetWidth() - generationResultsTable->GetColumnWidth(0));

	event.Skip();
}

void dgn::DegenerateBaseFrame::AddInformation(std::string&& name, std::string&& value, bool isWarning, bool isError)
{
	long index = generationResultsTable->InsertItem(0, name);
	generationResultsTable->SetItem(index, 1, value);

	// Todo: change these colors.
	if (isError)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 51, 51));

	if(isWarning)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 210, 51));
}

void dgn::DegenerateBaseFrame::SetInformation(std::string&& name, std::string&& value, bool isWarning, bool isError)
{
	generationResultsTable->ClearAll();
	generationResultsTable->InsertColumn(0, _("Property"));
	generationResultsTable->InsertColumn(1, _("Value"));

	wxSizeEvent e;
	FixListCtrl(e);

	long index = generationResultsTable->InsertItem(0, name);
	generationResultsTable->SetItem(index, 1, value);

	// Todo: change these colors.
	if (isError)
		generationResultsTable->SetItemBackgroundColour(index, wxColour(210, 51, 51));

	if (isWarning)
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

	if (Data::cartesianSize > Data::warningCartesianSize)
		SetInformation("Large Output", "It may take a long time to compute this sequence.", true, false);

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
	FillResults(dir);

	Data::permutationTime = duration_cast<nanoseconds>(end - begin).count() / 1000000;

	DisplayInformation();
}
