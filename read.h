
//read.h - a tiny header-only library to allow input in C++ to be more sensible
//by maqalaqil
#ifndef __READ_maqalaqil_H
#define __READ_maqalaqil_H
#include <iostream>
#include <fstream>
#include <string>
//Read a T from cin, reprompting if they type in something wrong
//Examples:
//int x = read<int>();
//const int x = read<int>("Please enter an int");
//string s = read<string>("What is your name?");
template<class T>
T read(const std::string prompt = "") {
	while (true) {
		if (std::cin.eof()) //We reached the end of file, or the user hit ctrl-d
			return T(); //Alternatively, we could throw an exception
		T retval;
		std::istream::pos_type pos = std::cin.tellg();
		std::cout << prompt;
		std::cin >> retval;
		if (!std::cin) {
			std::cin.clear(); //Clear error code
			if(std::cin.tellg() > pos) // check whether the stream has advanced
				continue;
			std::string s;
			std::cin >> s; //Remove the word that caused the error
			continue;
		}
		return retval;
	}
}
//Read a T from a file, so no prompt
//Example:
//auto d = read<double>(file);
template<class T>
T read(std::istream &ins) {
	while (true) {
		if (ins.eof()) //We reached the end of file, or the user hit ctrl-d
			return T();
		T retval;
		std::istream::pos_type pos = ins.tellg();
		ins >> retval;
		if (!ins) {
			ins.clear(); //Clear error code
			if(ins.tellg() > pos) // check whether the stream has advanced
				continue;
			std::string s;
			ins >> s; //Remove the word that caused the error
			continue;
		}
		return retval;
	}
}
