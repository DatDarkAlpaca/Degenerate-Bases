#pragma once

namespace dgn
{
	// Todo: test the wxConfig option instead.
	class SettingsHandler
	{
	public:
		static const std::string& Get(std::string&& section, std::string&& key);

	public:
		static void CreateDefault();

		static void ReadSettings();

	private:
		static bool ExistsSettings();

	private:
		static const std::string s_SettingsPath;
		static mINI::INIStructure s_Structure;
	};
}
