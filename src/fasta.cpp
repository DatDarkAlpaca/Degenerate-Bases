#include "pch.h"
#include "fasta.h"
#include "data.h"

bool existsResultsFolder = false;

size_t resultIndex = 0;

void fasta::load()
{
	bool existsResults = exists_results_folder();
	existsResultsFolder = existsResults;

	if (!existsResults)
		create_results_folder();

	check_last_filename();
}

void fasta::write_vector(vector<string>&& results, ofstream&& mFastaFile)
{
	if (!mFastaFile.is_open())
		throw "A problem has occurred while writing to the fasta file. It appears that the file is closed.";

	string strTemplate = program_data::initializationCharacter + program_data::sequenceTemplate;
	for (string& result : results)
	{
		mFastaFile << strTemplate << std::to_string(resultIndex) << '\n';
		mFastaFile << result << '\n';

		resultIndex++;
	}
}

void fasta::write_result(string&& result, ofstream&& mFastaFile)
{
	if (!mFastaFile.is_open())
		throw "A problem has occurred while writing to the fasta file. It appears that the file is closed.";

	string strTemplate = program_data::initializationCharacter + program_data::sequenceTemplate;

	mFastaFile << strTemplate << std::to_string(existsResultsFolder) << '\n';
	mFastaFile << result << '\n';

	resultIndex++;
}

void fasta::open_file(ofstream&& mFastaFile)
{
	string fileName = program_data::resultsFolder + program_data::resultPrefix
		+ std::to_string(program_data::fastaIndex) + program_data::resultFormat;

	mFastaFile.open(fileName, std::ios_base::app);
}

void fasta::close_file(ofstream&& mFastaFile)
{
	mFastaFile.close();

	program_data::fastaIndex++;
	resultIndex = 0;
}

bool fasta::exists_results_folder()
{
	struct stat buffer;
	return (stat(program_data::resultsFolder.c_str(), &buffer) == 0);
}

void fasta::create_results_folder()
{
	using namespace std::filesystem;
	create_directories(program_data::resultsFolder);
}

void fasta::check_last_filename()
{
	namespace fs = std::filesystem;

	vector<string> resultFiles;
	for (auto& entry : fs::directory_iterator(program_data::resultsFolder))
		resultFiles.push_back(entry.path().filename().string());

	program_data::fastaIndex = resultFiles.size();
}
