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

    root = parseStartingPoint(); // usually start at parseStartingPoint!!!!

}

void Parser::start(std::string filepath) {
    lex(filepath);
    parse();
}

void Parser::errormsg(std::string whoami, std::string type, std::string value){
    std::cout << "!!! " << whoami << " threw an error on line " << currentToken.getLine() << std::endl;

    std::cout << "\texpected '" << type                   << ": " << value                   << "'" <<
    std::endl << "\treceived '" << currentToken.getType() << ": " << currentToken.getValue() << "'" <<
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

/* --------------------------------------------------------------------------------------------------------------- */
/* StartingPoint */
TreeNode* Parser::parseStartingPoint(){
    debugmsg("parseStartingPoint");
    //StartingPoint -> PackageClause ImportDecl FunctionDecl
    return new NonTerminalNode( parsePackageClause(), parseImportDecl(), parseFunctionDecl(), nt_startingPoint );
}

/* --------------------------------------------------------------------------------------------------------------- */
/* PackageClause */
TreeNode* Parser::parsePackageClause(){

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "package") {
        debugmsg("parsePackageClause");

        if(consumeToken() == false) //consume 'package'
            return nullptr; 

        //PackageClause -> package PackageName ";"
        return new NonTerminalNode( 
            new LiteralNode("package", dt_string, nt_keyword)
            , parsePackageName()
            , new LiteralNode(";", dt_char, nt_symbol)
            , nt_packageClause 
            );

        //TODO implement catching ";"
    }

    errormsg("parsePackageClause", "KEYWORD", "package");
    return nullptr; 
}
TreeNode* Parser::parsePackageName(){

    if(currentToken.getType() == "IDENTIFIER"){ 
        if(currentToken.getValue() == "main"){ //cheaply catching main
            debugmsg("parsePackageName");

            //PackageName -> Identifier
            return new NonTerminalNode( parseIdentifier(), nullptr, nullptr, nt_packageName );
        }
    }

    errormsg("parsePackageName", "IDENTIFIER", "main");
    return nullptr; 
}

TreeNode* Parser::parseIdentifier(){ 

    if(currentToken.getType() == "IDENTIFIER"){ //would this build a symbol table?
        debugmsg("parseIdentifier");
        
        std::string identifierValue = currentToken.getValue(); //temporarily get Value for IdentifierNode

        if(consumeToken() == false) //consume identifier
            return nullptr;

        //Identifier -> string
        return new TerminalNode( identifierValue, dt_string,  nt_identifier, 0); 
        //since no symbol-table is beeing built yet, always have index of 0
    }

    errormsg("parseIdentifier", "IDENTIFIER", "[some string]");
    return nullptr; 
}

/* --------------------------------------------------------------------------------------------------------------- */
/* Import declarations */
TreeNode* Parser::parseImportDecl(){   

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "import"){
        debugmsg("parseImportDecl");

        if(consumeToken() == false) //consume 'import'
            return nullptr;

        //ImportDecl -> import ImportPackageName ";"
        return new NonTerminalNode( 
            new LiteralNode("import", dt_string, nt_keyword)
            , parseImportPackageName()
            , new LiteralNode(";", dt_char, nt_symbol)
            , nt_importdecl 
            );

        //TODO implement catching ";"
    }

    errormsg("parseImportDecl", "KEYWORD", "import");
    return nullptr; 
}
TreeNode* Parser::parseImportPackageName(){

    if(currentToken.getType() == "LITERAL"){ 
        if(currentToken.getValue() == "\"fmt\""){ //cheaply catching "fmt"
            debugmsg("parseImportPackageName");

            //ImportPackageName -> Literal
            return new NonTerminalNode( parseLiteral(), nullptr, nullptr, nt_ImportPackageName );
        }
    }

    errormsg("parseImportPackageName", "LITERAL", "\"fmt\"");
    return nullptr; //just to keep warning-messages away
}

TreeNode* Parser::parseLiteral(){
    if(currentToken.getType() == "LITERAL"){
        debugmsg("parseLiteral");

        std::string literalValue = currentToken.getValue(); //temporarily get Value for IdentifierNode

        if(consumeToken() == false) //consume literal
            return nullptr;

        return new LiteralNode( literalValue, dt_string, nt_literal );
    }

    errormsg("parseLiteral", "LITERAL", "\"[some string]\"");
    return nullptr;
}

/* --------------------------------------------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------------------------------------------- */
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