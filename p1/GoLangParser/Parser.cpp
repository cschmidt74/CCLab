/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: Luqzn
 * 
 * Created on 28. April 2016, 17:49
 */

#include "Parser.h"

Parser::Parser() {
}

Parser::~Parser() {
}

void Parser::lex(std::string filepath) {
    // Lexer Stuff
    lexer.initKeywords();
    lexer.readSourcecode(filepath);

    std::cout << "Sourcecode:" << std::endl;
    lexer.printSourcecode();

    int failed = lexer.createTokens();
    if (failed) std::cout << "Lexing failed on line " << failed << "." << std::endl;
    else {
        std::cout << "Lexing succeeded." << std::endl;
        std::cout << "Tokens:" << std::endl;
        lexer.printTokens();
    }
}

void Parser::parse() {
    //Parser Stuff
    lexer.resetTokenCount();
    Token currentToken("","",0);
    while(lexer.getNextToken(currentToken)) {
        //Start Parsing here with currentToken
        std::cout << "Test: " << currentToken.getValue() << std::endl;
    }
}

void Parser::start(std::string filepath) {
    lex(filepath);
    parse();
}