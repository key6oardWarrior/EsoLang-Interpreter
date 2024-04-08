#include "pch.h"
#include "InterpreterUnitTest.hpp"

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Error:\n";
		std::cout << "code exited with code 6: Expected 2 command line argument, but got " << argc;
		return 0;
	}

	const std::string fileName = argv[1];

	if(fileName.substr(fileName.length() - 3) != ".bf") {
		std::cout << "Error:" << std::endl;
		std::cout << "code exited with error code 7: File must be a .bf file." << std::endl;
		return 0;
	}

	if(std::filesystem::exists(std::filesystem::path(fileName)) == 0) {
		std::cout << "Error:\n";
		std::cout << "code exited with code 8: File does not exists";
	}

	InterpreterUnitTest ut(fileName);

	ut.isBalanced();
	ut.goToEnd();
	ut.isSymbolLegal();

	std::cout << "\nTest passed";

	return EXIT_SUCCESS;
}