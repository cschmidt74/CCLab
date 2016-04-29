/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.cpp
 * Author: Luqzn
 * 
 * Created on 26. April 2016, 15:55
 */

#include "Token.h"

Token::Token(std::string type, std::string value, int line){
    this->type = type;
    this->value = value;
    this->line = line;
}

Token::~Token() {
}

std::string Token::getType() {
    return type;
}

std::string Token::getValue() {
    return value;
}

int Token::getLine() {
    return line;
}