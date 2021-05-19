#include "pch.h"
#include "UnitHandlerModule.h"
#include "Data.h"

static vector<pair<int, Unit>> unitList;

static bool in(char toFind, vector<char>&& vec)
{
	for ( char& element : vec)
		if (element == toFind)
			return true;
	return false;
}

static void remove_whitespace_vector(vector<string>&& vec)
{
	vec.erase(remove_if(vec.begin(), vec.end(), [](string c) { return c.empty(); }), vec.end());
}

void unit::load()
{
	if (!check_translations())
		create_default_translations();

	insert_units();
	program_data::unitList = unitList;
	program_data::allBases = {
		'A', 'C', 'T', 'G', 'R', 'Y', 'M', 'K', 'S', 'W', 'H', 'B', 'V', 'D', 'N', '.', '-'
	};
}

vector<pair<char, vector<char>>> unit::parse_units()
{
	ifstream file("./bin/bases.tr");

	vector<string> contents;
	string line;
	while (getline(file, line))
		contents.push_back(line);

	remove_whitespace_vector(std::move(contents));

	vector<vector<char>> bases;
	bases.resize(contents.size());

	for (size_t i = 0; i < contents.size(); i++)
	{
		size_t pos = 0; std::string token = "";
		while ((pos = contents[i].find(" ")) != string::npos)
		{
			token = contents[i].substr(0, pos);

			char base = token[0];
			bases[i].push_back(base);

			contents[i].erase(0, pos + 1);
		}
		bases[i].push_back(contents[i][0]);
	}

	file.close();

	vector<pair<char, vector<char>>> basesContents;
	for (auto& base : bases)
	{
		char first = base[0];
		base.erase(base.begin());
		basesContents.push_back({ first, base });
	}

	return basesContents;
}

bool unit::check_translations()
{
	struct stat buffer;
	string bin = "./bin";

	if (std::filesystem::exists("./bin/bases.tr"))
		return true;
	else return false;

	if (stat(bin.c_str(), &buffer) != 0)
		return false;
	else return true;
}

void unit::create_default_translations()
{
	namespace fs = std::filesystem;
	fs::create_directories("./bin");

	ofstream tr("./bin/bases.tr");
	tr << "N A C G T" << '\n';

	tr << "H A C T" << '\n';
	tr << "B C G T" << '\n';
	tr << "V A C G" << '\n';
	tr << "D A G T" << '\n';

	tr << "R A G" << '\n';
	tr << "Y C T" << '\n';
	tr << "M A C" << '\n';
	tr << "K G T" << '\n';
	tr << "S C G" << '\n';
	tr << "W A T" << '\n';

	tr << "A A" << '\n';
	tr << "C C" << '\n';
	tr << "G G" << '\n';
	tr << "T T" << '\n';
	tr << ". ." << '\n';
	tr << "- -" << '\n';

	tr.close();
}

void unit::insert_units()
{
	vector<pair<char, vector<char>>> parsedUnits = parse_units();
	vector<char> normalBases = { 'A','C','T','G' };
	vector<char> doubleBases = { 'R','Y','M','K','S','W' };
	vector<char> tripleBases = { 'H','B', 'V', 'D' };
	vector<char> gaps = { '.','-' };

	for (auto& unit : parsedUnits)
	{
		Unit temp(unit.first, std::move(unit.second));

		if (unit.first == 'N')
			unitList.push_back({ 4, temp });
		else if (in(unit.first, std::move(tripleBases)))
			unitList.push_back({ 3, temp });
		else if (in(unit.first, std::move(doubleBases)))
			unitList.push_back({ 2, temp });
		else if (in(unit.first, std::move(normalBases)))
			unitList.push_back({ 1, temp });
		else if (in(unit.first, std::move(gaps)))
			unitList.push_back({ 1, temp });
	}
}
