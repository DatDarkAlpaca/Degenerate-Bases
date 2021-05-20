#pragma once
#include "pch.h"

class Unit
{
public:
	Unit(char degenerateBase, vector<char>&& possibleBases)
	{
		data.first = degenerateBase;
		data.second = possibleBases;
	}
	Unit() = delete;

public:
	 inline vector<char>& GetPossibleBases()  { return data.second; }
	 inline char GetDegenerateBase()  { return data.first; }

private:
	pair<char, vector<char>> data = {};
};
