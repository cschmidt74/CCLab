/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lexer.h
 * Author: Luqzn
 *
 * Created on 15. April 2016, 21:12
 */

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Token.h"

class Lexer {
public:
    Lexer();
    virtual ~Lexer();
    
    bool readSourcecode(std::string filepath);
    void printSourcecode();
    
    int createTokens();
    bool splitLine(std::string line, int lineNumber);
    bool checkForSemicolonOnLineEnd(Token t);
    void printTokens();
    bool getNextToken(Token& t);
    void resetTokenCount();
    
    void initKeywords();
    bool isKeyword(std::string word);
    bool isSimpleOperator(char c);
    void initOperators();
    bool isOperator(std::string word);
    bool isSpace(char c);
    bool isLetter(char c);
    bool isNumber(char c);
    bool isLetterOrNumber(char c);
    bool isBracket(char c);
private:
    std::vector<std::string> lines;
    std::vector<std::string> keywords;
    std::vector<std::string> operators;
    std::vector<Token> tokens;
    int tokenCount;
};

#endif /* LEXER_H */

