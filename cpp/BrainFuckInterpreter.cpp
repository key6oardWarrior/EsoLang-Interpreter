#include "..\pch.h"

bool Interpreter::isBalanced(int i) const {
    int balance = 1;

    if(isSameLine) {
        return true;
    }

    do {
        i++;
        if(codeLine[i] == '[') {
            balance++;
        } else if(codeLine[i] == ']') {
            balance--;
        }

        if(balance < 0) {
            return false;
        }
    } while(i < codeLine.length());

    return (balance == 0) ? true : false;
}

void Interpreter::printErrorMessageDescription(const char& userChar, const int& charNum) const {
    std::cout << std::endl << "Error:" << std::endl;
    std::cout << "char: " << userChar << std::endl;
    std::cout << "line number: " << lineNum << std::endl;
    std::cout << "char index: " << charNum << std::endl;
}

ErrorMessage Interpreter::isSymbolLegal(Environment& env) {
    int startLoopIndex = 0;

    for(int i = 0; i < codeLine.length(); i++) {
        switch(codeLine[i]) {
            case ' ': // ignore whitespace
                continue;
            case '>': // forward pointer
                if(env.getMP() != (env.endMemPtr())) {
                    env.incMP();
                } else {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;
            case '<': // backward pointer
                if(env.getMP() != env.beginMemPtr()) {
                    env.decMP();
                } else {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;
            case '+': // increment
                env.increment();
                if(*env.getMP() == 0xffffffff) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;
            case '-': // decrement
                env.decrement();
                if((*env.getMP() == -0x80)) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::stackOverFlow;
                }
                break;
            case '.': // output
                {
                    const auto mp = *env.getMP();

                    if(isprint(mp)) {
                        std::cout << mp;
                    } else {
                        std::string prefix = (mp < 0) ? "-0x" : "0x";
                        std::cout << prefix << std::hex << abs(mp) << std::endl;
                    }
                }
                break;
            case ',': // user input
                char userLetter;

                std::cin >> userLetter;
                env.userInput(userLetter);
                break;
            case '[': // start loop
                if(isBalanced(i) == false) {
                    printErrorMessageDescription(codeLine[i], i);
                    return ErrorMessage::unmatchedBrackets;
                }
                isSameLine = true;

                startLoopIndex = i;
                break;
            case ']': // end loop
                if((*env.getMP()) != 0x0) {
                    i = startLoopIndex;
                }
                break;
            default:
                printErrorMessageDescription(codeLine[i], i);
                return ErrorMessage::invalidSymbol;
        }
    }
    return ErrorMessage::noError;
}

ErrorMessage Interpreter::interpret() {
    Environment env;
    ErrorMessage errorMsg;

    if(code.is_open()) {
        do {
            std::getline(code, codeLine);
            errorMsg = isSymbolLegal(env);
            isSameLine = false;
            lineNum++;
        } while((code.eof() == false) && (errorMsg == ErrorMessage::noError));
    } else {
        return ErrorMessage::codeNotOpen;
    }
    return errorMsg;
}

void Interpreter::main(void) {
    ErrorMessage message = Interpreter::interpret();
    std::cout << std::endl;

    switch(message) { // display error message
        case ErrorMessage::noError:
            std::cout << "code exited with error code 0." << std::endl;
            break;
        case ErrorMessage::codeNotOpen:
            std::cout << " code exited with error code 1: Either file could not be opened or it does not exist." << std::endl;
            break;
        case ErrorMessage::invalidSymbol:
            std::cout << "code exited with error code 2: invalid symbol." << std::endl;
            break;
        case ErrorMessage::unmatchedBrackets:
            std::cout << "code exited with error code 3: unmatched brackets." << std::endl;
            break;
        case ErrorMessage::stackOverFlow:
            std::cout << "code exited with error code 4: Stack overflow occurred." << std::endl;
            break;
    }
}