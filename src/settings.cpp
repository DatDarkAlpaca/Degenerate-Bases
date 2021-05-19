#include "pch.h"
#include "Settings.h"
#include "Data.h"

static vector<pair<string, string>> settingsData = {};

void settings::load()
{
	if (!settings::exists_settings())
		settings::create_default();
	settings::retrieve();
	settings::parse();
}

bool settings::exists_settings()
{
	return std::filesystem::exists("./bin/settings.ini");
}

void settings::create_default()
{
 	std::filesystem::create_directories("bin");
 	
	ofstream settings("./bin/settings.ini");

	settings << "# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #" << '\n';
	settings << "# Degenerates Bases. 2020 -  v4.6f  #" << '\n';
	settings << "# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #" << '\n';

	settings << '\n';

	settings << "# Fasta formatting :" << '\n';
	settings << "initializationCharacter = >" << '\n';
	settings << "sequenceTemplate        = seq" << '\n';

	settings << '\n';

	settings << "# Results Formatting :" << '\n';
	settings << "resultPrefix  = Result_" << '\n';
	settings << "resultFormat  = .fas" << '\n';
	settings << "resultsFolder = ./results/" << '\n';

	settings << '\n';

	settings << "#Logging" << '\n';
	settings << "enableLogging = true" << '\n';
	settings << "logPrefix     = Log_" << '\n';
	settings << "logsFolder    = ./logs/" << '\n';

	settings << '\n';

	settings << "# Chunks:" << '\n';
	settings << "chunkSize = 2048" << '\n';

	settings << '\n';

	settings << "# Debbuging:" << '\n';
	settings << "writeDebug = false" << '\n';
	settings << "debug      = true";

	settings.close();
}

void settings::retrieve()
{
	ifstream settingsFile("./bin/settings.ini");
	
	string line;
	while (getline(settingsFile, line))
	{
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		
		if (line[0] == '#' || line.empty()) 
			continue;
			
		istringstream isStr(line);
		string key;
		if (getline(isStr, key, '='))
		{
			string value;
			if (getline(isStr, value))
				settingsData.push_back(std::make_pair(key, value));
		}
		else 
			continue;
	}

	settingsFile.close();
}

void settings::parse()
{
	auto lower = [](string& s) { for (char& c : s) c = tolower(c); };
	auto removeWhitespace = [](string& s) { s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end()); };

	for (auto& setting : settingsData)
	{
		lower(setting.first);

		removeWhitespace(setting.first);
		removeWhitespace(setting.second);

		if (setting.first == "initializationcharacter")
			program_data::initializationCharacter = setting.second;

		else if (setting.first == "sequencetemplate")
			program_data::sequenceTemplate = setting.second;

		else if (setting.first == "resultprefix")
			program_data::resultPrefix = setting.second;

		else if (setting.first == "resultformat")
			program_data::resultFormat = setting.second;

		else if (setting.first == "resultsfolder")
			program_data::resultsFolder = setting.second;

		else if (setting.first == "logprefix")
			program_data::logPrefix = setting.second;

		else if (setting.first == "logsfolder")
			program_data::logsFolder = setting.second;

		lower(setting.second);

		if (setting.first == "chunksize")
			program_data::chunkSize = std::stoi(setting.second);

		else if (setting.first == "enablelogging")
			program_data::enableLogging = (setting.second == "true") ? true : false;

		else if (setting.first == "debug")
			program_data::debug = (setting.second == "true") ? true : false;

		else if (setting.first == "writedebug")
			program_data::writeDebug = (setting.second == "true") ? true : false;
	}
}
