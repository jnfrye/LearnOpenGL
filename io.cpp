#include "io.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

bool TryReadFile(const std::string& fileName, std::string& outText)
{
	std::ifstream file;
	file.open(fileName, std::ios::in);
	if (!file.is_open())
		return false;

	std::stringstream textStream;
	textStream << file.rdbuf();
	file.close();

	outText = textStream.str();
	return true;
}
