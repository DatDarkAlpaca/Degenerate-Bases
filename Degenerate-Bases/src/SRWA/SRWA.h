#pragma once
#include "pch.h"
#include "../settings/settings.h"

namespace dgn
{
    class SRWA
    {
    public:
        SRWA() = delete;

    public:
        static void Open(const std::string& filepath, std::ios_base::openmode mode = std::ios_base::app)
        {
            if(!s_File.is_open())
                s_File.open(filepath, mode);
        }

        static void Close()
        {
            if (!s_File.is_open())
                return;

            s_File.close();
            index = 0;
        }

        static void CreateDefault()
        {
            using namespace std::filesystem;

            auto directory = Settings::Get("results", "directory");
            if (!is_directory(directory))
                create_directory(directory);
        }

    public:
        static void Write(const std::string& data)
        {
            if (!s_File.is_open())
                return;

            const std::string headerCharacter = Settings::Get("fasta", "header_character");
            const std::string headerTemplate = Settings::Get("fasta", "header_template");

            const std::string header = headerCharacter + headerTemplate;

            std::lock_guard<std::mutex> lock(m_WriteMutex);

            s_File << header << std::to_string(index) << '\n';
            s_File << data << '\n';

            ++index;
        }

        static std::vector<std::string> Read(const std::string& filepath)
        {
            Open(filepath, std::ios_base::in);

            std::vector<std::string> results;

            bool firstLine = true;
            char headerCharacter;
            for (std::string line; std::getline(s_File, line); )
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

    private:
        static inline std::mutex m_WriteMutex;
        static inline std::fstream s_File;

    public:
        static inline size_t index = 0;
    };
}
