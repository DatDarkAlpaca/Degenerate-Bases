#include "pch.h"
#include "App.h"
#include "../SRWA/SRWA.h"
#include "../gui/main_frame.h"
#include "../settings/settings.h"

bool dgn::App::OnInit()
{
	using namespace dgn;

	Settings::CreateDefault();
	Settings::ReadSettings();

	DegenerateBaseFrame* frame = new DegenerateBaseFrame(nullptr, wxID_ANY, "Degenerate Bases v5.0");
	SetTopWindow(frame);
	frame->Show(true);

	return true;
}
