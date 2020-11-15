
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
//Getline equivalent for reading from a file
std::string readline(std::istream &ins, char delimiter = '\n') {
	std::string retval;
	ins >> std::ws;
	std::getline(ins,retval,delimiter);
	if (ins.eof()) //We reached the end of file, or the user hit ctrl-d
		return retval;
	if (!ins)
		throw std::runtime_error("Error within the readline function.");
	return retval;
}

//To use read_opt requires C++17 and above
#if __cplusplus >= 201703L
#include <optional>
//Returns an optional. So if your specified type is not read, the caller will know this rather than silently discarding the error
//Recommended for more advanced programmers than read()
//If an error occurs, it does not affect the input stream at all and clears the failbit
// Example:
// auto a = read_opt<int>(); 
// if (!a) exit(EXIT_FAILURE);
// cout << *a << endl;
template<class T>
std::optional<T> read_opt(const std::string prompt = "") {
	if (std::cin.eof()) //We reached the end of file, or the user hit ctrl-d
		return std::nullopt;  //Return that nothing was read
	T retval{};
	std::cout << prompt;
	std::cin >> retval;
	if (!std::cin) {
		std::cin.clear(); //Clear error code, so the user can try again when they like
		return std::nullopt;  //Return that nothing was read
	}
	return retval;
}