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

    while(lexer.getNextToken(currentToken)) {
        //Start Parsing here with currentToken
        std::cout << "Test: " << currentToken.getValue() << std::endl;
    }
}

void Parser::start(std::string filepath) {
    lex(filepath);
    parse();
}

/* PackageClause */
TreeNode* Parser::parsePackageClause(){

    /* TODO: what can be expected as a return value from getValue() and getType() */

    if(currentToken.getValue() == "package") {
        // open parsePackageName
    }

    std::cout << "Error at PackageClause at line " << currentToken.getLine() << std::endl;
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parsePackageName(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseIdentifier(){
    return nullptr; //just to keep warning-messages away
}

/* Import declarations */
TreeNode* parseImportDecl(){   
    return nullptr; //just to keep warning-messages away
}

/* Function declarations */
TreeNode* Parser::parseFunctionDecl(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseFunctionName(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseFunction(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseSignature(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseFunctionBody(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseBlock(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseStatementList(){
    return nullptr; //just to keep warning-messages away
}

/* Statements */
TreeNode* Parser::parseStatement(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseSimpleStmt(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseEmptyStmt(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseDeclaration(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseReturnStmt(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseExpressionStmt(){
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseAssignment(){
    return nullptr; //just to keep warning-messages away
}