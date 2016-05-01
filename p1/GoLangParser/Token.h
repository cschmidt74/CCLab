/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.h
 * Author: Luqzn
 *
 * Created on 26. April 2016, 15:55
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    Token(std::string type, std::string value, int line);
    virtual ~Token();
    std::string getType();
    std::string getValue();
    int getLine();
private:
    std::string type;
    std::string value;
    int line;
};
#endif /* TOKEN_H */

