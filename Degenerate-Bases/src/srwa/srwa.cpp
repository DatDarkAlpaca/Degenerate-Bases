#include "pch.h"
#include "srwa.h"
#include "data.h"
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
		line = std::regex_replace(line, std::regex(" +$"), "");

		std::string lineCopy = line;
		std::transform(lineCopy.begin(), lineCopy.end(), lineCopy.begin(), ::toupper);

		if (line.empty())
			continue;

		if (line[0] == ';')
		{
			size_t pos = 0;
			std::string token;
			while ((pos = line.find(":") != std::string::npos))
			{
				token = line.substr(0, pos);
				line.erase(0, pos + 1);
			}

			if (lineCopy.find("SEQUENCE") != std::string::npos)
			{
				Data::sequence = line;
			}

			else if (lineCopy.find("ITERATIONS") != std::string::npos)
				Data::iterations = std::stoi(line);

			else if (lineCopy.find("OUTCOMES") != std::string::npos)
				Data::outcomes = std::stoi(line);

			else if (lineCopy.find("PERMUTATION") != std::string::npos)
			{
				line = std::regex_replace(line, std::regex("\\ms"), "");
				Data::permutationTime = std::stoi(line);
			}

			else if (lineCopy.find("WRITING") != std::string::npos)
			{
				line = std::regex_replace(line, std::regex("\\ms"), "");
				Data::writeFastaTime = std::stoi(line);
			}
		}

		else
		{
			if (firstLine)
			{
				headerCharacter = line[0];
				firstLine = false;
			}
		}

		if (line[0] != headerCharacter && lineCopy[0] != ';')
			results.push_back(line);
	}

	Close();

	return results;
}

void dgn::SRWA::WriteHeader(const std::string& sequence, size_t iterations, size_t outcomes, long long permutationTime, long long writeTime)
{
	file.seekp(0);

	file << "; -= -= This file has been generated using Degenerate Bases v5.0 =- =-\n";
	file << "; Original Sequence: " << sequence << '\n';
	file << "; Iterations: " << iterations << '\n';
	file << "; Outcomes: " << outcomes << '\n';
	file << "; Permutation Time: " << permutationTime << '\n';
	file << "; Writing Time: " << writeTime << '\n';
}
