#include "io.h"
#include <fstream>
#include <string>
#include <iostream>

const char* ReadFile(const char* fileName)
{
	std::string text{};
	std::fstream newfile;
	newfile.open(fileName, std::ios::in);
	if (newfile.is_open())
	{
		std::string tp;
		while (std::getline(newfile, tp))
		{
			text += tp + "\n";
		}

		newfile.close();
	}

	std::cout << text.c_str();
	return text.c_str();
}
