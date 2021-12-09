#include "pch.h"
#include "App.h"
#include "main_frame.h"
#include "../SRWA/SRWA.h"
#include "../settings/settings.h"

bool dgn::App::OnInit()
{
	using namespace dgn;

	SettingsHandler::CreateDefault();
	SettingsHandler::ReadSettings();

	SRWA::Configure(SettingsHandler::Get("fasta", "header_character").c_str()[0], 
		            SettingsHandler::Get("fasta", "header_template"));

	MainFrame* frame = new MainFrame;
	frame->Show(true);
	return true;
}
