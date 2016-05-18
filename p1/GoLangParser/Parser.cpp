#include "Parser.h"

Parser::Parser() {
    DEBUG = false;
    timeout = 0;
    tabCount = 0;
    hasParsed = false;
    cellar.erase(cellar.begin(), cellar.end());
    errorCount = 0;
    errorLine = 0;
}

Parser::~Parser() {
}

void Parser::lex(std::string filepath) {
    // Lexer Stuff
    lexer.initKeywords();
    lexer.readSourcecode(filepath);

    if(DEBUG){
        std::cout << "Sourcecode:" << std::endl;
        lexer.printSourcecode();
    }

    int failed = lexer.createTokens();
    if (failed) {
        std::cout << "Lexing failed on line " << failed << "." << std::endl;
        errorLine = failed;
    }
    else {
        if(DEBUG){
            std::cout << "Lexing succeeded." << std::endl;
            std::cout << "Tokens:" << std::endl;
            lexer.printTokens();
        }
    }
}

void Parser::parse() {
    //Parser Stuff
    lexer.resetTokenCount();

    if(DEBUG)
        std::cout << "starting parser ..." << std::endl;

    if(lexer.getNextToken(currentToken) == false){
        std::cout << "Either an error has occured or the file is empty." << std::endl;
    }

    root = parseStartingPoint(); 

    if (root != nullptr && root->getNodeType() == ast::nt_startingPoint){
        hasParsed = true;
        if(DEBUG)
            std::cout << "Parsing succeeded." << std::endl;
    }

}

bool Parser::start(std::string filepath) {
    lex(filepath);
    parse();

    if(DEBUG && hasParsed){
        printAST();
    }

    if(errorLine)
        return true;
    return false;
}

void Parser::printAST(){
    if(hasParsed == false){
        std::cout << "No AST to print! Either the input was empty or it wasn't parsed yet." << std::endl;
        return;
    }

    tabCount = 0;

    std::cout << "Printing generated AST... " << std::endl;

    printNonTerminal( (ast::NonTerminalNode*) root);
}

void Parser::printNonTerminal(ast::NonTerminalNode* nrNode){
    using namespace std;
    using namespace ast;

    //print own type, then increase tabCount
    cout << nttos(nrNode->getNodeType()) << "<" << endl;

    ++tabCount;

    TreeNode* child;
    for (size_t i = 0; i < 3; ++i){

        if(i == 0) child = nrNode->getLeftChild(); //
        else if(i == 1) child = nrNode->getMiddleChild();
        else child = nrNode->getRightChild();

        if(child != nullptr) { //ignore dead children

        for (size_t i = 0; i < tabCount; ++i)
            cout << "\t";

            if(child->getNodeType() < 100) //another NonTerminal
                printNonTerminal( (NonTerminalNode*) child);

            else if(child->getNodeType() < 200) //terminal
                printTerminal( (TerminalNode*) child);

            else //literal
                printLiteral( (LiteralNode*) child);
        } //else

    } //for
    
    --tabCount;
}
void Parser::printTerminal(ast::TerminalNode* ntNode){
    using namespace std;
    using namespace ast;

    cout << nttos(ntNode->getNodeType()) << ": " << ntNode->getName() << " (" << dttos(ntNode->getDataType()) << ")" << endl;
}
void Parser::printLiteral(ast::LiteralNode* nlNode){
    using namespace std;
    using namespace ast;

    cout << nttos(nlNode->getNodeType()) << ": " << nlNode->getValue() << " (" << dttos(nlNode->getDataType()) << ")" << endl;
}

std::string Parser::nttos(ast::nodeType nt){
    using namespace ast;
    switch(nt){
        case nt_startingPoint: return "Starting Point";
        case nt_packageClause: return "Package Clause";
        case nt_packageName: return "Package Name";
        case nt_importdecl:  return "Import Decleration";
        case nt_ImportPackageName: return "Import Package Name";
        case nt_functionDecl: return "Function Decleration";
        case nt_functionName: return "Function Name";
        case nt_function: return "Function";
        case nt_functionBody: return "Function Body";
        case nt_block: return "Block";
        case nt_statementList: return "Statement List";
        case nt_statement: return "Statement";
        case nt_functionCall: return "Function Call";
        case nt_functionCallCont: return "Function Call Continued";
        case nt_arguments: return "Arguments";
        case nt_argumentsCont: return "Arguments Continued";
        case nt_argument: return "Argument";
        case nt_identifier: return "Identifier";
        case nt_literal: return "Literal";
        case nt_signature: return "Signature";
        case nt_keyword: return "Keyword"; 
        case nt_symbol: return "Symbol";
        default : return "unkown node";
    }
}

std::string Parser::dttos(ast::dataType dt){
    using namespace ast;
    switch(dt){
        case dt_string: return "String"; 
        case dt_char: return "Char";
        case dt_int: return "Integer";
        case dt_float: return "Float";
        default: return "unkown type";
    }
}

void Parser::errormsg(std::string whoami, std::string type, std::string value){
    std::cout << "!!! " << whoami << " threw an error on line " << currentToken.getLine() << std::endl;

    std::cout << "\texpected '" << type                   << ": " << value                   << "'" <<
    std::endl << "\treceived '" << currentToken.getType() << ": " << currentToken.getValue() << "'" <<
    std::endl ;
    ++errorCount;
}

void Parser::debugmsg(std::string node){
    if(DEBUG){
    std::cout << "DebugInfo from '" << node << "' at line " << currentToken.getLine() << 
                 ". Type: " << currentToken.getType() << ", Value: " << currentToken.getValue() << std:: endl;
    }
}

bool Parser::consumeToken(bool suppress_errormsg){
    if(lexer.getNextToken(currentToken) == false){
        if(suppress_errormsg == false){
            std::cout << "Cannot read next token. Error @line: " << currentToken.getLine() << 
            std::endl << "Last token was: " << currentToken.getValue() << 
            std::endl ;
        }
        return false;
    }
    return true;
}

/* --------------------------------------------------------------------------------------------------------------- */
/* StartingPoint */
ast::TreeNode* Parser::parseStartingPoint(){
    debugmsg("parseStartingPoint");
    //StartingPoint -> PackageClause ImportDecl FunctionDecl
    return new ast::NonTerminalNode( parsePackageClause(), parseImportDecl(), parseFunctionDecl(), ast::nt_startingPoint );
}

/* --------------------------------------------------------------------------------------------------------------- */
/* PackageClause */
ast::TreeNode* Parser::parsePackageClause(){

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "package") {
        debugmsg("parsePackageClause");

        ast::TreeNode* pkg_iden = new ast::LiteralNode("package", ast::dt_string, ast::nt_keyword);

        if(consumeToken() == false) //consume 'package'
            return nullptr; 

        ast::TreeNode* pkg_name = parsePackageName(); //will consume package name, leaving a semicolon

        if(currentToken.getValue() == ";"){
            debugmsg("parsePackageClause");

            if(consumeToken() == false) //consume ;
                return nullptr;

            //PackageClause -> package PackageName ";"
            return new ast::NonTerminalNode(
                pkg_iden
                , pkg_name
                , new ast::LiteralNode(";", ast::dt_char, ast::nt_symbol)
                , ast::nt_packageClause
                );
        }

        errormsg("parsePackageClause", "Some Symbol", ";");
    }

    errormsg("parsePackageClause", "KEYWORD", "package");
    return nullptr; 
}
ast::TreeNode* Parser::parsePackageName(){

    if(currentToken.getType() == "IDENTIFIER"){ 
        if(currentToken.getValue() == "main" || currentToken.getValue() == "fmt"){ //cheaply catching main and fmt
            debugmsg("parsePackageName");

            //PackageName -> Identifier
            return new ast::NonTerminalNode( parseIdentifier(), nullptr, nullptr, ast::nt_packageName );
        }
    }

    errormsg("parsePackageName", "IDENTIFIER", "main");
    return nullptr; 
}

ast::TreeNode* Parser::parseIdentifier(){ 

    if(currentToken.getType() == "IDENTIFIER"){ //would this build a symbol table?
        debugmsg("parseIdentifier");
        
        std::string identifierValue = currentToken.getValue(); //temporarily get Value for IdentifierNode

        if(consumeToken() == false) //consume identifier
            return nullptr;

        //Identifier -> string
        return new ast::TerminalNode( identifierValue, ast::dt_string,  ast::nt_identifier, 0); 
        //since no symbol-table is beeing built yet, always have index of 0
    }

    errormsg("parseIdentifier", "IDENTIFIER", "[some string]");
    return nullptr; 
}

/* --------------------------------------------------------------------------------------------------------------- */
/* Import declarations */
ast::TreeNode* Parser::parseImportDecl(){   

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "import"){
        debugmsg("parseImportDecl");

        ast::TreeNode* imp_iden = new ast::LiteralNode("import", ast::dt_string, ast::nt_keyword);

        if(consumeToken() == false) //consume 'import'
            return nullptr;

        ast::TreeNode* imp_pcknm = parseImportPackageName(); //will consume ImportPackageName, leaving ;

        if(currentToken.getValue() == ";"){
            debugmsg("parseImportDecl");

            if(consumeToken() == false) //consume ;
                return nullptr;

            return new ast::NonTerminalNode(
                imp_iden
                , imp_pcknm
                , new ast::LiteralNode(";", ast::dt_char, ast::nt_symbol)
                , ast::nt_importdecl
                );
        }

        errormsg("parseImportDecl", "Some Symbol", ";");

    }

    errormsg("parseImportDecl", "KEYWORD", "import");
    return nullptr; 
}
ast::TreeNode* Parser::parseImportPackageName(){

    if(currentToken.getType() == "LITERAL"){ 
        if(currentToken.getValue() == "\"fmt\""){ //cheaply catching "fmt"
            debugmsg("parseImportPackageName");

            //ImportPackageName -> Literal
            return new ast::NonTerminalNode( parseLiteral(), nullptr, nullptr, ast::nt_ImportPackageName );
        }
    }

    errormsg("parseImportPackageName", "LITERAL", "\"fmt\"");
    return nullptr; 
}

ast::TreeNode* Parser::parseLiteral(){
    if(currentToken.getType() == "LITERAL"){
        debugmsg("parseLiteral");

        std::string literalValue = currentToken.getValue(); //temporarily get Value for IdentifierNode

        if(consumeToken() == false) //consume literal
            return nullptr;

        return new ast::LiteralNode( literalValue, ast::dt_string, ast::nt_literal );
    }

    errormsg("parseLiteral", "LITERAL", "\"[some string]\"");
    return nullptr;
}

/* --------------------------------------------------------------------------------------------------------------- */
/* Function declarations */
ast::TreeNode* Parser::parseFunctionDecl(){

    if(currentToken.getType() == "KEYWORD" && currentToken.getValue() == "func"){
        debugmsg("parseFunctionDecl");

        if(consumeToken() == false) //consume 'func'
            return nullptr;

        //FunctionDecl -> func FunctionName Function
        return new ast::NonTerminalNode(
            new ast::LiteralNode("func", ast::dt_string, ast::nt_keyword)
            , parseFunctionName()
            , parseFunction()
            , ast::nt_functionDecl
            );
    }

    errormsg("parseFunctionDecl", "KEYWORD", "func");
    return nullptr; 
}
ast::TreeNode* Parser::parseFunctionName(){

    if(currentToken.getType() == "IDENTIFIER"){
        if(currentToken.getValue() == "main" || currentToken.getValue() == "Println"){ //cheaply catching main and Println
            debugmsg("parseFunctionName");

            //FunctionName -> Identifier
            return new ast::NonTerminalNode( parseIdentifier(), nullptr, nullptr, ast::nt_functionName );
        }
    }

    errormsg("parseFunctionName", "IDENTIFIER", "main");
    return nullptr; 
}

ast::TreeNode* Parser::parseFunction(){
    debugmsg("parseFunction");
    //Function -> Signature FunctionBody
    return new ast::NonTerminalNode(parseSignature(), parseFunctionBody(), nullptr, ast::nt_function);
}

ast::TreeNode* Parser::parseSignature(){

    if(currentToken.getType() == "BRACKET" && currentToken.getValue() == "("){
        debugmsg("parseSignature");

        if(consumeToken() == false) //consume '('
            return nullptr;

        if(currentToken.getType() == "BRACKET" && currentToken.getValue() == ")"){
            debugmsg("parseSignature");

            if(consumeToken() == false) //consume ')'
                return nullptr;

            //Signature -> "(" ")"  
            return new ast::LiteralNode("()", ast::dt_string, ast::nt_symbol); 
        }

        errormsg("parseSignature", "BRACKET", ")");
        return nullptr; 
    }

    errormsg("parseSignature", "BRACKET", "(");
    return nullptr; 
}
ast::TreeNode* Parser::parseFunctionBody(){
    debugmsg("parseFunctionBody");
    //FunctionBody -> Block
    return new ast::NonTerminalNode(parseBlock(), nullptr, nullptr, ast::nt_functionBody);
}

ast::TreeNode* Parser::parseBlock(){

    if(currentToken.getType() == "BRACKET" && currentToken.getValue() == "{"){
        debugmsg("parseBlock");

        cellar.push_back('{'); //construct pushdown-machine

        if(consumeToken(true) == false) //consume '{' 
            return nullptr;

        ast::TreeNode* statementlist = parseStatementList(); //will consume any statements up to following '}'

        if(currentToken.getType() == "BRACKET" && currentToken.getValue() == "}"){
            debugmsg("parseBlock");

            if(cellar.back() == '{'){ //only deconstruct, when found partner-symbol
                cellar.pop_back(); //deconstruct pushdown-machine
            }

            if(cellar.empty() == false){ //in which case we are not at EOF
                if(consumeToken() == false) //so we can keep looking, and consume }
                    return nullptr;
            }

            //Block -> "{" StatementList "}"
            return new ast::NonTerminalNode(
                new ast::LiteralNode("{", ast::dt_char, ast::nt_symbol)
                , statementlist
                , new ast::LiteralNode("}", ast::dt_char, ast::nt_symbol)
                , ast::nt_block
                );
        }

        errormsg("parseBlock", "BRACKET", "}");
        return nullptr; 

    }

    errormsg("parseBlock", "BRACKET", "{");
    return nullptr; 
}

ast::TreeNode* Parser::parseStatementList(){
    debugmsg("parseStatementList");

    if(++timeout >= 4){ // since the recursion will only stop, when a '}' is found, a failsafe is needed
        std::cout << "!!! parseStatementList threw an error on line " << currentToken.getLine() << 
        std::endl << "\tCould not find '}'" << 
        std::endl << "\tTimed out to prevent further damage" << std::endl;
        timeout = 0;
        return nullptr;
    }

    if(currentToken.getType() == "BRACKET" && currentToken.getValue() == "}"){
        // StatementList -> Statement ";" StatementList | epsilon 
        return nullptr; //end of statementlist, return to parseBlock (=> epsilon)
    }

    ast::TreeNode* statement = parseStatement(); //will consume the statement, leaving a semicolon

    if(currentToken.getValue() == ";"){
        if(consumeToken() == false) //consume ;
            return nullptr;
    } else {
        errormsg("parseStatementList", "Some Symbol", ";");
        return nullptr;
    }

    //StatementList -> Statement ";" StatementList | epsilon 
    return new ast::NonTerminalNode(
        statement
        , new ast::LiteralNode(";", ast::dt_char, ast::nt_symbol)
        , parseStatementList()
        , ast::nt_statementList
        );
}

/* --------------------------------------------------------------------------------------------------------------- */
/* Statements */
ast::TreeNode* Parser::parseStatement(){
    debugmsg("parseStatement");

    if(currentToken.getValue() == ";"){
        //Statement -> FunctionCall | epsilon
        return nullptr; // end of statement, return to statementList (=> epsilon)
    }

    //Statement -> FunctionCall | epsilon
    return new ast::NonTerminalNode(parseFunctionCall(), nullptr, nullptr, ast::nt_statement);
}

ast::TreeNode* Parser::parseFunctionCall(){
    debugmsg("parseFunctionCall");

    ast::TreeNode* pcknm = parsePackageName(); //will consume packagename

    if(currentToken.getValue() == "."){ 
        if(consumeToken() == false) //consume .
            return nullptr;
    } else {
        errormsg("parseFunctionCall", "Some Symbol", ".");
        return nullptr;
    }

    //FunctionCall -> PackageName "." FunctionCallCont
    return new ast::NonTerminalNode(
        pcknm
        , new ast::LiteralNode(".", ast::dt_char, ast::nt_symbol)
        , parseFunctionCallCont()
        , ast::nt_functionCall
        );
}
ast::TreeNode* Parser::parseFunctionCallCont(){
    debugmsg("parseFunctionCallCont");

    //FunctionCallCont -> FunctionName Arguments
    return new ast::NonTerminalNode(
        parseFunctionName(),
        parseArguments(),
        nullptr,
        ast::nt_functionCallCont
        );
}
ast::TreeNode* Parser::parseArguments(){
    debugmsg("parseArguments");

    if(currentToken.getType() == "BRACKET" && currentToken.getValue() == "("){
        ast::TreeNode* rp = new ast::LiteralNode("(", ast::dt_char, ast::nt_symbol);

        if(consumeToken() == false) //consume (
            return nullptr;

        ast::TreeNode* ac = parseArgumentsCont(); // will consume arguments, leaving a left parathesis

        if(currentToken.getType() == "BRACKET" && currentToken.getValue() == ")"){

            ast::TreeNode* lp = new ast::LiteralNode(")", ast::dt_char, ast::nt_symbol);

            if(consumeToken() == false) //consume )
                return nullptr;

            //Arguments -> "(" ArgumentsCont ")"
            return new ast::NonTerminalNode(rp, ac, lp, ast::nt_arguments);
        }

        errormsg("parseArguments", "BRACKET", ")");
        return nullptr;
    }

    errormsg("parseArguments", "BRACKET", "(");
    return nullptr;
}

ast::TreeNode* Parser::parseArgumentsCont(){
    debugmsg("parseArgumentsCont");

    if(currentToken.getType() == "BRACKET" && currentToken.getValue() == ")"){
        //ArgumentsCont -> Argument | Argument "," ArgumentsCont | epsilon
        return nullptr; //end of argumentscont, return to parsearguments (=> epsilon)
    }

    ast::TreeNode* arg = parseArgument(); //will consume argument, leaving either a comma or a left parenthesis

    if(currentToken.getValue() == ","){
        debugmsg("parseArgumentsCont");

        ast::TreeNode* cm = new ast::LiteralNode(",", ast::dt_char, ast::nt_symbol);
        if(consumeToken() == false) //consume ,
            return nullptr;

        //ArgumentsCont -> Argument | Argument "," ArgumentsCont | epsilon      
        return new ast::NonTerminalNode(arg, cm, parseArgumentsCont(), ast::nt_argumentsCont);  
    }

    //ArgumentsCont -> Argument | Argument "," ArgumentsCont | epsilon
    return new ast::NonTerminalNode(arg, nullptr, nullptr, ast::nt_argumentsCont); //single argument

    return nullptr;
}

ast::TreeNode* Parser::parseArgument(){
    debugmsg("parseArgument");

    //Argument -> Literal 
    return new ast::NonTerminalNode(parseLiteral(), nullptr, nullptr, ast::nt_argument);
}