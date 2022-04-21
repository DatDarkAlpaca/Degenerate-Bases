#include "pch.h"
#include "srwa.h"
#include "settings/settings.h"

void dgn::SRWA::Open(const std::string& filepath, std::ios_base::openmode mode)
{
	if (!file.is_open())
		file.open(filepath, mode);
}

void dgn::SRWA::Close()
{
	if (!file.is_open())
		return;

	file.close();
	index = 0;
}

void dgn::SRWA::CreateDefault()
{
	using namespace std::filesystem;

	auto directory = Settings::Get("results", "directory");
	if (!is_directory(directory))
		create_directory(directory);
}

void dgn::SRWA::Write(const std::string& data)
{
	if (!file.is_open())
		return;

	const std::string headerCharacter = Settings::Get("fasta", "header_character");
	const std::string headerTemplate = Settings::Get("fasta", "header_template");

	const std::string header = headerCharacter + headerTemplate;

	std::lock_guard<std::mutex> lock(m_WriteMutex);

	file << header << std::to_string(index) << '\n';
	file << data << '\n';

	++index;
}

std::vector<std::string> dgn::SRWA::Read(const std::string& filepath)
{
	Open(filepath, std::ios_base::in);

	std::vector<std::string> results;

	bool firstLine = true;
	char headerCharacter;
	for (std::string line; std::getline(file, line); )
	{
		if (firstLine)
		{
			headerCharacter = line[0];
			firstLine = false;
		}

		if (line[0] != headerCharacter)
			results.push_back(line);
	}

	Close();

	return results;
}
