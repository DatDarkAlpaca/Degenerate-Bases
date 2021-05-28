#include "pch.h"
#include "Menu.h"
#include "Data.h"

void menu::header()
{
	cout << "-= Degenerate Bases : v4.6f = -" << '\n';
	cout << "Author: Paulo C." << '\n' << '\n';
}

void menu::show_information()
{
	cout << "[!] For more information, write 'help' and press Enter. If you need a list of all available bases, write 'bases'" 
		<< '\n' << '\n';
}

void menu::help_menu()
{
	cout << '\n';

	cout << "Please enter a sequence containing degenerate bases bellow. It can have spaces, uppercase letters and uppercase letters." << '\n';
	cout << "If any letter on the sequence is not a valid base, the program will tell you." << '\n';
	cout << "To list all possible bases, write 'bases' then press Enter." << '\n';

	cout << '\n';
}

void menu::base_list()
{
	cout << '\n';
	cout << "Listed bellow is a list of the available degenerate bases." << '\n' << '\n';

	cout << "N - A, C, T, G" << '\n' << '\n';

	cout << "D - A, G, T" << '\n';
	cout << "V - A, C, G" << '\n';
	cout << "B - C, T, G" << '\n';
	cout << "H - A, C, T" << '\n' << '\n';

	cout << "W - A, T" << '\n';
	cout << "S - C, G" << '\n';
	cout << "K - G, T" << '\n';
	cout << "M - A, C" << '\n';
	cout << "Y - C, T" << '\n';
	cout << "R - A, G" << '\n' << '\n';

	cout << "Normal Bases: A, C, G, T" << '\n' << '\n';

	cout << "Gaps: -, ." << '\n';
	cout << "Additional: *" << '\n';

	cout << '\n';
}

void menu::get_input()
{
	cout << "Insert a sequence: ";
}

void menu::debug_info()
{
	if (!program_data::debug) return;
	else
	{
		cout << "-=-=-=-= Debug Info. =-=-=-=-" << '\n';
		cout << "Base sequence's length  :     " << program_data::input.size() << "     -    (" << program_data::input << ")" << '\n';
		cout << "Amount of outcomes      :     " << program_data::outcomes << '\n';
		cout << "Amount of iterations    :     " << program_data::iterations << '\n';
		cout << '\n';
		cout << "Total Iteration time    :     " << program_data::permutationTime << "ms" << '\n';
		cout << "File writing time       :     " << program_data::writeFastaTime << "ms" << '\n';
		cout << '\n';
	}
}

void menu::post_execution()
{
	cout << "[!] The sequence has been successfully computed and written to a fasta file" << '\n' << '\n';

	cout << "Would you like to enter another base? (N/Y): ";
}

void menu::finalize()
{
	cout << "Bye bye!" << '\n';
}

void menu::write_chunk_size()
{
	cout << "-=-= Chunk Size : " << program_data::chunkSize << " =-=-" << '\n';
}

void menu::write_chunk(size_t chunk)
{
	cout << "[!] Writting chunk 0x0" << std::hex << chunk << "..." << '\n';
}

void menu::unmatched_bases_errors()
{
	cout << "[!!!] A LETHAL error has ocurred. \
			 The estimated amount of outcomes does not match the real amount of outcomes." << '\n';
}

void menu::cartesian_size_warning()
{
	cout << "[!] The following sequence will result in a considerable amount of outcomes." << '\n';
	cout << "It may take a long time to compute this sequence, and it will generate a massive file." << '\n';
}
