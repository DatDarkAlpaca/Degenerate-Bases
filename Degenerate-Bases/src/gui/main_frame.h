#pragma once
#include "pch.h"

#include "compiled/main_frame/degenerate_ui.h"
#include "virtual_list.h"

#include "../permutator/permutator.h"
#include "../input/input.h"
#include "../SRWA/SRWA.h"
#include "../data.h"

namespace dgn
{
	namespace
	{
		enum { ID_NEW = 1, ID_OPEN, ID_SAVE };

		enum { ID_INPUT_BTN = wxID_HIGHEST + 1 };
	}

	class DegenerateBaseFrame : public MainFrame
	{
	public:
		DegenerateBaseFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);

	private:
		void PrepareMenu();

		void CreateVirtualList();

		void ModifyGenerateButton();

		void FillResults(const std::string& dir);

		void FixListCtrl(wxSizeEvent& event);

		void FixListCtrlSash(wxSplitterEvent& event);

	private:
		void AddInformation(std::string&& name, std::string&& value, bool isWarning = false, bool isError = false);

		void SetInformation(std::string&& name, std::string&& value, bool isWarning = false, bool isError = false);

		void DisplayInformation();

	private:
		void ButtonGenerate(wxCommandEvent& event);

	private:
		VirtualList* m_ResultListCtrl;
	};
}