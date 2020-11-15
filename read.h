
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
//Reads a whole line of text, analogue to getline
std::string readline(const std::string prompt = "", char delimiter = '\n') {
	//Eliminate a common bug when switching from >> to getline, the >> will leave a newline in the input buffer
	std::string retval;
	std::cout << prompt;
	std::cin >> std::ws;
	std::getline(std::cin,retval,delimiter);
	if (std::cin.eof()) //We reached the end of file, or the user hit ctrl-d
		return retval;
	if (!std::cin)
		throw std::runtime_error("Error within the readline function.");
	return retval;
}