#pragma once
#include "Environment.hpp"

class Interpreter {
private:
	std::fstream code;
	std::string codeLine;

	Environment* env = new Environment();

	const size_t maxInt = 0x7f;
	const signed int minInt = -0x80;
	int lineNum = 1;
	bool isSameLine = 0;
	bool isMaxPositive = 0;
	bool isMaxNegative = 0;

public:
	/*
	* open the users file via std::fstream
	*
	* @param file path
	*/
	Interpreter(const std::string& filePath) { code.open(filePath); }

	~Interpreter(void) {
		delete env;
		env = nullptr;

		code.close();
	}

	void main(void);

private:
	/*
	* ensure all open brackets have an close bracket
	*
	* @param current line that is being read
	* @return true if found the closing bracket
	*/
	bool isBalanced(size_t) const;

	/*
	* Go to the end of loop
	*
	* @param starting char index
	*/
	void goToEnd(size_t&) const;

	/*
	* print the error message's char, char's index, and what line it is on
	*
	* @param the char that caused the error
	* @param which char on the line caused the error
	*/
	void errorDescription(const char&, const size_t&) const;

	/*
	* determin if the symbol in the bf file is legal
	* if it is then carry out instructions
	* else return int that correlates to enum class ErrorMessage
	*
	* @return the error code to be displayed
	*/
	ErrorMessage isSymbolLegal(void);

	/*
	* interpret code in a bf file
	*
	* @return ErrorMessage
	*/
	ErrorMessage interpret(void);
};
