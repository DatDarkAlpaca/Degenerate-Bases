#pragma once
#include <string>
#include <ini.h>

namespace dgn
{
	class Settings
	{
	public:
		static const std::string Get(std::string&& section, std::string&& key);

		static const void Set(std::string&& section, std::string&& key, std::string&& value);

	public:
		static void CreateDefault();

		static void ReadSettings();

		static size_t CountFiles();

	private:
		static bool ExistsSettings();

	private:
		static inline const std::string s_SettingsPath = "settings.ini";
		static inline mINI::INIStructure s_Structure;
		static inline mINI::INIFile s_IniFile = mINI::INIFile("");
	};
}
