#pragma once

namespace dgn
{
	class Settings
	{
	public:
		static const std::string Get(std::string&& section, std::string&& key);

	public:
		static void CreateDefault();

		static void ReadSettings();

		static size_t CountFiles();

	private:
		static bool ExistsSettings();

	private:
		static inline const std::string s_SettingsPath = "./settings.ini";
		static inline mINI::INIStructure s_Structure;
	};
}
