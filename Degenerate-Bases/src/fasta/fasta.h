#pragma once
#include "pch.h"
#include "chunk.h"

namespace dgn
{
    class Fasta
    {
    public:
        Fasta() = delete;

    public:
        static void Configure(char headerCharacter = ';', const std::string& headerTemplate = "base")
        {
            s_HeaderCharacter = headerCharacter;
            s_HeaderTemplate = headerTemplate;
        }

        static void SetEnabled(bool enabled) { s_Enabled = enabled; }

        static void Open(std::string&& filepath, std::ios_base::openmode mode = std::ios_base::app)
        {
            s_File.open(filepath, mode);
        }

        static void Close()
        {
            if (!s_File.is_open())
                return;

            s_File.close();
            s_Index = 0;
        }

    public:
        static void Write(const std::string& data)
        {
            if (!s_File.is_open() || !s_Enabled)
                return;

            const std::string header = s_HeaderCharacter + s_HeaderTemplate;

            s_File << header << std::to_string(s_Index);
            s_File << '\n' << data << '\n';

            ++s_Index;
        }

        static void Write(std::string&& data)
        {
            if (!s_File.is_open() || !s_Enabled)
                return;

            const std::string header = s_HeaderCharacter + s_HeaderTemplate;

            s_File << header << std::to_string(s_Index);
            s_File << '\n' << data << '\n';

            ++s_Index;
        }

        static void Write(const std::vector<std::string>& data)
        {
            if (!s_File.is_open() || !s_Enabled)
                return;

            const std::string header = s_HeaderCharacter + s_HeaderTemplate;

            for (const std::string& result : data)
            {
                s_File << header << std::to_string(s_Index) << '\n';
                s_File << result << '\n';

                ++s_Index;
            }

            ++s_Index;
        }

        static void Write(std::vector<std::string>&& data)
        {
            if (!s_File.is_open() || !s_Enabled)
                return;

            const std::string header = s_HeaderCharacter + s_HeaderTemplate;

            for (const auto& result : data)
            {
                s_File << header << std::to_string(s_Index) << '\n';
                s_File << result << '\n';

                ++s_Index;
            }

            ++s_Index;
        }

    private:
        static inline std::string s_HeaderTemplate = "base";
        static inline char s_HeaderCharacter = ';';

        static inline std::fstream s_File;

        static inline bool s_Enabled = true;
        static inline size_t s_Index = 0;
    };
}
