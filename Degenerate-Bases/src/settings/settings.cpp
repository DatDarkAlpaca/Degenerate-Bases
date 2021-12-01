#include "pch.h"
#include "settings.h"

const std::string& dgn::SettingsHandler::Get(std::string&& section, std::string&& key)
{
	if (SettingsHandler::s_Structure.has(section))
	{
		auto& collection = SettingsHandler::s_Structure[section];
		if (collection.has(key))
			return collection[key];
	}

	return std::string();
}

void dgn::SettingsHandler::CreateDefault()
{
	if (SettingsHandler::ExistsSettings())
		return;

	mINI::INIFile iniFile(SettingsHandler::s_SettingsPath);
	mINI::INIStructure iniStruct;

	iniStruct["fasta"].set({
		{ "header_character ", ">" },
		{ "header_template", "seq" }
	});

	iniStruct["results"].set({
		{ "prefix ", "Result_" },
		{ "format", "fas" },
		{ "directory", "./results/" }
	});

	iniStruct["Logging"].set({
		{ "enable ", "true" },
		{ "prefix", "Log_" },
		{ "directory", "./logs/" }
	});

	iniStruct["chunks"].set({
		{ "chunk_size ", "1024" }
	});

	iniStruct["debug"].set({
		{ "enable", "false" },
		{ "write_debug", "false" },
	});

	iniFile.generate(iniStruct, true);
}

void dgn::SettingsHandler::ReadSettings()
{
	mINI::INIFile file(SettingsHandler::s_SettingsPath);

	file.read(SettingsHandler::s_Structure);
}

bool dgn::SettingsHandler::ExistsSettings()
{
	return std::filesystem::exists(s_SettingsPath);
}

// Static properties:
const std::string dgn::SettingsHandler::s_SettingsPath = "settings.ini";

mINI::INIStructure dgn::SettingsHandler::s_Structure = mINI::INIStructure();