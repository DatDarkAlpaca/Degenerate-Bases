#pragma once
#include "pch.h"
#include "virtual_list.h"

namespace dgn
{
	namespace
	{
		enum
		{
			ID_NEW = 1,
			ID_OPEN,
			ID_SAVE
		};

		enum
		{
			ID_INPUT_BTN = wxID_HIGHEST + 1
		};
	}

	class MainFrame : public wxFrame
	{
	public:
		MainFrame();

	private:
		void PrepareMenu();

		void PrepareInput();

	private:
		void ButtonGenerate(wxCommandEvent& event);

	private:
		wxTextCtrl* m_Input;
		VirtualList* m_ResultsList;

	private:
		std::vector<std::thread> m_BasesThreads;
	};
}
