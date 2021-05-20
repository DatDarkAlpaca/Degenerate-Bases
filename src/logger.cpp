#include "pch.h"
#include "logger.h"

static bool existsLogFolder = false;

static string bool_to_string(bool x)
{
	if (x) return "enabled";
	else return "disabled";
}

void logger::load()
{
	existsLogFolder = logger::exists_log_folder();

	if (!existsLogFolder)
		logger::create_default();

	logger::check_last_fileName();
}

void logger::log_data()
{
	if (!program_data::enableLogging) return;

	string path = program_data::logsFolder;
	string data = program_data::logPrefix + std::to_string(program_data::logIndex);
	string suf = ".txt";

	ofstream file(path + data + suf);
	file << "-= -= : Logging Outcome for : 0x0" << program_data::fastaIndex - 1 << " : = -= -" << '\n';

	file << '\n';

	// -=-=-= Input Data =-=-=-
	file << "-= Input Data =-" << '\n';
	file << "• Entered Sequence : " << program_data::input << '\n';
	file << "• Amount of:" << '\n';
	file << "  - Quadriple Bases : " << program_data::quadriples << '\n';
	file << "  - Triples Bases   : " << program_data::triples << '\n';
	file << "  - Double Bases    : " << program_data::doubles << '\n';
	file << "  - Normal Bases    : " << program_data::normals << '\n';
	file << "  - Gaps            : " << program_data::gaps << '\n';

	file << '\n';

	file << "• Computed Cartesian Size: " << program_data::get_lazy_cartesian_size() << '\n';

	file << '\n';

	file << "-= Settings Data =-" << '\n';
	file << "• Chunk Size : " << program_data::chunkSize << '\n';
	file << '\n';
	file << "• Enable Debug       : " << bool_to_string(program_data::debug) << '\n';
	file << "• Enable Write Debug : " << bool_to_string(program_data::writeDebug) << '\n';

	file << '\n';

	file << "-= Permutation Data =-" << '\n';
	file << "• Amount of Iterations :  " << program_data::iterations << '\n';
	file << "• Amount of Outcomes   :  " << program_data::outcomes << '\n';

	file << '\n';

	file << "-= Benchmark Data =- " << '\n';
	file << "• Writing Time : " << program_data::writeDebug << "ms\n";
	file << "• Total Time   : " << program_data::permutationTime << "ms";

	file.close();
	program_data::logIndex++;
}

bool logger::exists_log_folder()
{
	struct stat buffer;
	return (stat(program_data::logsFolder.c_str(), &buffer) == 0);
}

void logger::create_default()
{
	std::filesystem::create_directories(program_data::logsFolder);
}

void logger::check_last_fileName()
{
	namespace fs = std::filesystem;
	string path = program_data::logsFolder;

	vector<string> logFiles;
	for (auto& entry : fs::directory_iterator(path))
		logFiles.push_back(entry.path().filename().string());

	program_data::logIndex = logFiles.size();
}

