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

    void printAST();

private:
    Lexer lexer;
    Token currentToken;
    ast::TreeNode* root;
    bool DEBUG;
    bool hasParsed;

    size_t tabCount;

    void printNonTerminal(ast::NonTerminalNode* nrNode);
    void printTerminal(ast::TerminalNode* ntNode);
    void printLiteral(ast::LiteralNode* nlNode);
    std::string nttos(ast::nodeType nt);
    std::string dttos(ast::dataType dt);

	bool consumeToken(bool suppress_errormsg = false);
    void errormsg(std::string whoami, std::string type, std::string value);
    void debugmsg(std::string node);

    size_t timeout;

    /* StartingPoint */
    ast::TreeNode* parseStartingPoint();
    /* PackageClause */
    ast::TreeNode* parsePackageClause();
    ast::TreeNode* parsePackageName();
    ast::TreeNode* parseIdentifier();
    /* Import declarations */
    ast::TreeNode* parseImportDecl();
    ast::TreeNode* parseImportPackageName();
    ast::TreeNode* parseLiteral();
    /* Function declarations */
    ast::TreeNode* parseFunctionDecl();
    ast::TreeNode* parseFunctionName();
    ast::TreeNode* parseFunction();
    ast::TreeNode* parseSignature();
    ast::TreeNode* parseFunctionBody();
    ast::TreeNode* parseBlock();
    ast::TreeNode* parseStatementList();
    /* Statements */
    ast::TreeNode* parseStatement();
    ast::TreeNode* parseFunctionCall();
    ast::TreeNode* parseFunctionCallCont();
    ast::TreeNode* parseArguments();
    ast::TreeNode* parseArgumentsCont();
    ast::TreeNode* parseArgument();
};

#endif /* PARSER_H */