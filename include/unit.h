#pragma once
#include "pch.h"

class Unit
{
public:
	Unit(char degenerateBase, vector<char>&& possibleBases)
	{
		this->degenerateBase = degenerateBase;
		this->possibleBases = possibleBases;

		possibleBasesSize = possibleBases.size();
	}
	Unit() = delete;

public:
	char degenerateBase = NULL;
	vector<char> possibleBases = {};
	size_t possibleBasesSize = 0;
};
