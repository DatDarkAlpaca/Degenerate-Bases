#include "pch.h"
#include "App.h"
#include "main_frame.h"
#include "../fasta/chunk.h"
#include "../fasta/fasta.h"
#include "../settings/settings.h"

bool dgn::App::OnInit()
{
	SettingsHandler::CreateDefault();
	SettingsHandler::ReadSettings();

	Fasta::Configure(SettingsHandler::Get("fasta", "header_character").c_str()[0], 
		             SettingsHandler::Get("fasta", "header_template"));

	MainFrame* frame = new MainFrame;
	frame->Show(true);
	return true;
}
