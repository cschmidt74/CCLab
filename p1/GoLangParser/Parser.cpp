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
    DEBUG = true;
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

    if(DEBUG)
        std::cout << "starting parser ..." << std::endl;

    if(lexer.getNextToken(currentToken) == false){
        std::cout << "Cannot Read next Token. Are you sure, the test-file is not empty?" << std::endl;
    }

    root = parsePackageClause(); // usually start at parseStartingPoint!!!!

}

void Parser::start(std::string filepath) {
    lex(filepath);
    parse();
}

void Parser::errormsg(std::string type, std::string value){
    std::cout << "Error @PackageClause on line " << currentToken.getLine() << std::endl;

    std::cout << "expected '" << type                   << ": " << value                   << "'" <<
    std::endl << "received '" << currentToken.getType() << ": " << currentToken.getValue() << "'" <<
    std::endl ;
}

void Parser::debugmsg(std::string node){
    if(DEBUG){
    std::cout << "DebugInfo from '" << node << "' at line " << currentToken.getLine() << 
                 ". Type: " << currentToken.getType() << ", Value: " << currentToken.getValue() << std:: endl;
    }
}

bool Parser::consumeToken(){
    if(lexer.getNextToken(currentToken) == false){
        std::cout << "Cannot read next token. Error @line: " << currentToken.getLine() << 
        std::endl << "Last token was: " << currentToken.getValue() << 
        std::endl ;
        return false;
    }
    return true;
}

/* StartingPoint */
TreeNode* Parser::parseStartingPoint(){
    debugmsg("parseStartingPoint");
    return new StartingPointNode( parsePackageClause(), parseImportDecl(), parseFunctionDecl() );
}

/* PackageClause */
TreeNode* Parser::parsePackageClause(){

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "package") {
        debugmsg("parsePackageClause");

        if(consumeToken() == false) //consume 'package'
            return nullptr; 

        return new PackageClauseNode( parsePackageName() );
    }

    errormsg("KEYWORD", "package");
    return nullptr; 
}
TreeNode* Parser::parsePackageName(){

    if(currentToken.getType() == "IDENTIFIER" && currentToken.getValue() == "main"){
        debugmsg("parsePackageName");
        return new PackageNameNode( parseIdentifier() );
    }

    errormsg("IDENTIFIER", "main");
    return nullptr; 
}
TreeNode* Parser::parseIdentifier(){

    if(currentToken.getType() == "IDENTIFIER"){
        debugmsg("parseIdentifier");
        return new IdentifierNode( currentToken.getValue() );
    }

    errormsg("IDENTIFIER", "[some string]");
    return nullptr; 
}

/* Import declarations */
TreeNode* Parser::parseImportDecl(){   
    return nullptr; //just to keep warning-messages away
}
TreeNode* Parser::parseImportDeclCont(){
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