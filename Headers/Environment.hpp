#pragma once

class Environment {
private:
	unsigned short memory[0x752f];
	unsigned short memoryIndex = 0;

public:
	const unsigned short end = 0x752f;

	Environment(void) {
		std::fill_n(memory, end, 0);
	}

	/*
	* @return memoryPointer
	*/
	unsigned short getMemIdx(void) const;

	/*
	* Get const ref of memory[idx]
	* 
	* @return a const ref to the memory[idx]
	*/
	unsigned short const& getConstMemory(void);

	/*
	* increment the memoryPointer pointer
	*/
	void incMemPtr(void) { memoryIndex++; }

	/*
	* decrement the memoryPointer pointer
	*/
	void decMemPtr(void) { memoryIndex--; }

	/*
	* @param userLetter - set *memoryPointer to user input
	*/
	void userInputChar(const char& userLetter) {
		memory[memoryIndex] = userLetter;
	}

	/*
	* If the user enters a std::string rather than a char then add each
	* char to a memory block then move the next memory block
	* 
	* @param userLetter - set *memoryPointer to user input
	*/
	void userInputString(const char& userLetter) {
		memory[memoryIndex++] = userLetter;
	}

	/*
	* add 0x1 to *memoryPointer
	*/
	void increment(void) { memory[memoryIndex]++; }

	/*
	* subtract 0x1 from *memoryPointer
	*/
	void decrement(void) { memory[memoryIndex]--; }
};
