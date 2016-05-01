/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Luqzn
 *
 * Created on 28. April 2016, 17:49
 */

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser {
public:
    Parser();
    virtual ~Parser();
    
    void lex(std::string filepath);
    void parse();
    void start(std::string filepath);
private:
    Lexer lexer;
};

#endif /* PARSER_H */