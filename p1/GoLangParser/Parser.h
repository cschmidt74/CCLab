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
#include "TreeNode.h"

class Parser {
public:
    Parser();
    virtual ~Parser();
    
    void lex(std::string filepath);
    void parse();
    void start(std::string filepath);
private:
    Lexer lexer;
    Token currentToken;
    TreeNode* root;
    bool DEBUG;

	bool consumeToken();
    void errormsg(std::string whoami, std::string type, std::string value);
    void debugmsg(std::string node);

    /* StartingPoint */
    TreeNode* parseStartingPoint();
    /* PackageClause */
    TreeNode* parsePackageClause();
    TreeNode* parsePackageName();
    TreeNode* parseIdentifier();
    /* Import declarations */
    TreeNode* parseImportDecl();
    TreeNode* parseImportDeclCont();
    /* Function declarations */
    TreeNode* parseFunctionDecl();
    TreeNode* parseFunctionName();
    TreeNode* parseFunction();
    TreeNode* parseSignature();
    TreeNode* parseFunctionBody();
    TreeNode* parseBlock();
    TreeNode* parseStatementList();
    /* Statements */
    TreeNode* parseStatement();
    TreeNode* parseSimpleStmt();
    TreeNode* parseEmptyStmt();
    TreeNode* parseDeclaration();
    TreeNode* parseReturnStmt();
    TreeNode* parseExpressionStmt();
    TreeNode* parseAssignment();
};

#endif /* PARSER_H */