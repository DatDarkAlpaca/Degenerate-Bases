#pragma once
#include "pch.h"

namespace dgn
{
    class SRWA
    {
    public:
        SRWA& operator=(const SRWA&) = delete;
        SRWA(const SRWA&) = delete;
        SRWA() = delete;

    public:
        static void Open(const std::string& filepath, std::ios_base::openmode mode = std::ios_base::app);

        static void Close();

        static void CreateDefault();

    public:
        static void WriteHeader(const std::string& sequence, size_t iterations, size_t outcomes, long long permutationTime, long long writeTime);

        static void Write(const std::string& data);

        static std::vector<std::string> Read(const std::string& filepath);

    private:
        static inline std::mutex m_WriteMutex;

    public:
        static inline std::fstream file;
        static inline size_t index = 0;
    };
}
