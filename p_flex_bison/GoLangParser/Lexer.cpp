/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lexer.cpp
 * Author: Luqzn
 * 
 * Created on 15. April 2016, 21:12
 */

#include "Lexer.h"

Lexer::Lexer() {
    lines.clear();
    keywords.clear();
    operators.clear();
    tokens.clear();
    tokenCount = 0;
}

Lexer::~Lexer() {
}

/*
 * Reads each line from sourcefile and stores in sourcecode member variable 
 */
bool Lexer::readSourcecode(std::string filepath) {
    std::fstream filestream;
    filestream.open(filepath.c_str(), std::fstream::in);
    std::string line;
    while (getline(filestream, line)) {
        lines.push_back(line);
    }
    filestream.close();
}

/*
 * Prints out each line of the sourcecode member variable
 */
void Lexer::printSourcecode() {
    for (int i = 0; i < lines.size(); i++) std::cout << std::setw(4) << std::left << i + 1 << lines[i] << std::endl;
}

/*
 * Calls splitLine() for every element in lines member variable
 */
int Lexer::createTokens() {
    for (int i = 0; i < lines.size(); i++) {
        if (!splitLine(lines[i], i + 1)) {
            return i + 1;
        }
    }
    return 0;
}

/*
 * Checks if a semicolon on line end is needed
 */
bool Lexer::checkForSemicolonOnLineEnd(Token t) {
    if (t.getType() == "IDENTIFIER" || t.getType() == "LITERAL" || t.getType() == "NUMBER") return true;
    else if (t.getType() == "BRACKET" && (t.getValue() == "}" || t.getValue() == "]" || t.getValue() == ")")) return true;
    else if (t.getValue() == "KEYWORD" && (t.getValue() == "break" || t.getValue() == "continue" || t.getValue() == "fallthrough" || t.getValue() == "return")) return true;
    else return false;
}

/*
 * Returns the adress of the next token based on tokenCount
 */
bool Lexer::getNextToken(Token& t) {
    if (tokenCount < tokens.size()) {
        t = tokens[tokenCount++];
        return true;
    } else {
        resetTokenCount();
        return false;
    }
}

/*
 * Set tokenCount to 0
 */
void Lexer::resetTokenCount() {
    tokenCount = 0;
}

/*
 * Splits a string into tokens and stores them in tokens member variable
 */
bool Lexer::splitLine(std::string line, int lineNumber) {
    char currentChar = ' ';
    std::string tokenValue = "";

    std::vector<char> data(line.begin(), line.end()); // convert string to vector of char
    std::reverse(data.begin(), data.end()); // reverse elements to acces data in right order from back via pop_back())

    while (!data.empty()) {

        // handle whitespace
        while (isSpace(currentChar) && !data.empty()) {
            currentChar = data.back();
            data.pop_back();
        }

        // handle semicolon
        if (currentChar == ';') {
            currentChar = ' ';
            Token t("TERMINATOR", ";", lineNumber);
            tokens.push_back(t);
			if(data.empty()) return true;
        }

        // handle comments
        if (currentChar == '/') {
            if (!data.empty()) {
                currentChar = data.back();
                data.pop_back();
                if (currentChar == '/') return true; //comment: ignore the rest of the line
            }
            return false; //comment failure: single / not valid
        }
            // handle if the next token starts with a letter
        else if (isLetter(currentChar)) {
            tokenValue = currentChar;
            if (!data.empty()) {
                currentChar = data.back();
                data.pop_back();
                while (isLetterOrNumber(currentChar)&&!data.empty()) {
                    tokenValue += currentChar;
                    currentChar = data.back();
                    data.pop_back();
                }
            }

            if (isKeyword(tokenValue)) {
                Token t("KEYWORD", tokenValue, lineNumber);
                tokens.push_back(t);
            } else {
                Token t("IDENTIFIER", tokenValue, lineNumber);
                tokens.push_back(t);
            }
        }
            // handle if the next token starts with a number
        else if (isNumber(currentChar)) {
            tokenValue = currentChar;
            if (!data.empty()) {
                currentChar = data.back();
                data.pop_back();
                while ((isNumber(currentChar) || currentChar == '.') && !data.empty()) {
                    tokenValue += currentChar;
                    currentChar = data.back();
                    data.pop_back();
                }
                if (!isSpace(currentChar)) return false;
            }
            Token t("NUMBER", tokenValue, lineNumber);
            tokens.push_back(t);
        }
            // handle brackets
        else if (isBracket(currentChar)) {
            tokenValue = currentChar;
            currentChar = ' ';
            Token t("BRACKET", tokenValue, lineNumber);
            tokens.push_back(t);
        }
            // handle funtioncall
        else if (currentChar == '.') {
            tokenValue = currentChar;
            currentChar = ' ';
            Token t("FUNCTIONCALL", tokenValue, lineNumber);
            tokens.push_back(t);
        }
            // handle literals
        else if (currentChar == '"') {
            tokenValue = currentChar;
            if (!data.empty()) {
                currentChar = data.back();
                data.pop_back();
                while (currentChar != '"' && !data.empty()) {
                    tokenValue += currentChar;
                    currentChar = data.back();
                    data.pop_back();
                }
                if (data.empty() && currentChar != '"') return false;
                else {
                    tokenValue += currentChar;
                    currentChar = ' ';
                }
                Token t("LITERAL", tokenValue, lineNumber);
                tokens.push_back(t);
            }
        }
            // handle chars who are out of context
        else if (!isSpace(currentChar))return false;

    }

    if (!tokens.empty()) {
        if (checkForSemicolonOnLineEnd(tokens.back())) {
            Token t("TERMINATOR", ";", lineNumber);
            tokens.push_back(t);
        }
    }

    return true;
}

/*
 * Prints out each token in the tokens member variable
 */
void Lexer::printTokens() {
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].getType() << " on line " << tokens[i].getLine() << " has the value: " << tokens[i].getValue() << std::endl;
    }
}

/*
 * Initializes the keywords variable with language specific keywords 
 */
void Lexer::initKeywords() {
    keywords.clear();
    keywords.push_back("break");
    keywords.push_back("default");
    keywords.push_back("func");
    keywords.push_back("interface");
    keywords.push_back("select");
    keywords.push_back("case");
    keywords.push_back("defer");
    keywords.push_back("go");
    keywords.push_back("map");
    keywords.push_back("struct");
    keywords.push_back("chan");
    keywords.push_back("else");
    keywords.push_back("goto");
    keywords.push_back("package");
    keywords.push_back("switch");
    keywords.push_back("const");
    keywords.push_back("fallthrough");
    keywords.push_back("if");
    keywords.push_back("range");
    keywords.push_back("type");
    keywords.push_back("continue");
    keywords.push_back("for");
    keywords.push_back("import");
    keywords.push_back("return");
    keywords.push_back("var");
}

/*
 * Checks if a word is in the keywords vector or not
 */
bool Lexer::isKeyword(std::string word) {
    for (int i = 0; i < keywords.size(); i++) {
        if (keywords[i] == word) return true;
    }
    return false;
}

/*
 * Checks if a character is a simple operator
 */
bool Lexer::isSimpleOperator(char c) {
    // handle stuff here
}

/*
 * Checks if a Operator of more Characters is valid, in operatos vector
 */
bool Lexer::isOperator(std::string word) {
    // handle stuff here
}

/*
 * Initialize the operators vector
 */
void Lexer::initOperators() {
    operators.clear();
}

/*
 * Checks if a character is a whitespace
 */
bool Lexer::isSpace(char c) {
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') return true;
    else return false;
}

/*
 * Checks if a character is a letter
 */
bool Lexer::isLetter(char c) {
    int ascii = (int) c;
    if ((65 <= ascii && ascii <= 90) || (97 <= ascii) && (ascii <= 122)) return true;
    else return false;
}

/*
 * Checks if a character is a number
 */
bool Lexer::isNumber(char c) {
    int ascii = (int) c;
    if (48 <= ascii && ascii <= 57) return true;
    else return false;
}

/*
 * Checks if a character is a letter or number
 */
bool Lexer::isLetterOrNumber(char c) {
    if (isLetter(c) || isNumber(c)) return true;
    else return false;
}

/*
 * Checks if a character is a bracket
 */
bool Lexer::isBracket(char c) {
    if (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}') return true;
    else return false;
}