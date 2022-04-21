#include "pch.h"
#include "settings.h"

const std::string dgn::Settings::Get(std::string&& section, std::string&& key)
{
	if (s_Structure.has(section))
	{
		auto& collection = s_Structure[section];
		if (collection.has(key))
			return collection[key];
	}

	return std::string();
}

void dgn::Settings::CreateDefault()
{
	if (ExistsSettings())
		return;

	mINI::INIFile iniFile(s_SettingsPath);
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

void dgn::Settings::ReadSettings()
{
	mINI::INIFile file(s_SettingsPath);

	file.read(s_Structure);
}

size_t dgn::Settings::CountFiles()
{
	auto dirIter = std::filesystem::directory_iterator(Settings::Get("results", "directory"));

	auto fileCount = std::count_if(begin(dirIter), end(dirIter),
		[](auto& entry) { return entry.is_regular_file(); }
	);

	return fileCount;
}

bool dgn::Settings::ExistsSettings()
{
	return std::filesystem::exists(s_SettingsPath);
}
