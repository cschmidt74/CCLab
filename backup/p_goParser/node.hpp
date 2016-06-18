#include <string>
#include <vector>
#include <iostream>

//Terminals
class Nidentifier;
class Nstring_literal;
class Ninteger;
//Productions
class NProgramStart;
class NPackageClause;
class NFunctionDecl;
class NFunction;
class NParameter;
class NFunctionBody;
class NStatement;
class NDecleration; 
class NNumber;
class NExpression; 
class NTerm;
class NAssignment; 
class NCall; 
//Lists
typedef std::vector<NParameter*> ParameterList;
typedef std::vector<NStatement*> StatementList;
typedef std::vector<NDecleration*> ParamDeclList;


class Node{
public:
    virtual ~Node() {}
};

class NProgramStart : public Node {
    //ProgramStart -> PackageClause FunctionDecl
public:
    NPackageClause* cpackageclause;
    NFunctionDecl* cfunctiondecl;
    NProgramStart(NPackageClause* _cpackageclause, NFunctionDecl* _cfunctiondecl)
    : cpackageclause(_cpackageclause), cfunctiondecl(_cfunctiondecl) {}
};

class Nidentifier : public Node {
    //identifier -> letter(letter|number|"_")*
public:
    std::string name;
    Nidentifier(std::string& _name) 
    : name(_name) {}
};

class Nstring_literal : public Node {
    //""" letter(letter|number|"_")* """
public:
    std::string value;
    Nstring_literal(std::string & _value)
    : value(_value) {}
};

class Ninteger : public Node{
    //number -> (0-9)(0-9)*
public:
    int value;
    Ninteger(int& _value)
    : value(_value){}
};

class NNumber : public Node{
    //Number -> integer | identifier 
public:
    Ninteger* cinteger;
    Nidentifier* cidentifier;
    NNumber(Ninteger* _cinteger)
    : cinteger(_cinteger), cidentifier(nullptr) {}
    NNumber(Nidentifier* _cidentifier)
    : cinteger(nullptr), cidentifier(_cidentifier) {}
};

class NPackageClause : public Node {
    //PackageClause -> "package" identifier ";"
public:
    Nidentifier* cidentifier;
    NPackageClause(Nidentifier* _cidentifier) 
    : cidentifier(_cidentifier) {}
};

class NFunctionDecl : public Node {
    //FunctionDecl -> "func" identifier Function
public:
    Nidentifier* cidentifier;
    NFunction* cFunction;
    NFunctionDecl(Nidentifier* _cidentifier, NFunction* _cFunction)
    : cidentifier(_cidentifier), cFunction(_cFunction) {}
};

class NFunction : public Node {
    //Function -> "(" ParameterList ")" FunctionBody
public:
    ParamDeclList cParamDeclList;
    NFunctionBody* cFunctionBody;
    NFunction(ParamDeclList& _cParamDeclList, NFunctionBody* _cFunctionBody)
    : cParamDeclList(_cParamDeclList), cFunctionBody(_cFunctionBody) {}
    NFunction(NFunctionBody* _cFunctionBody) 
    : cFunctionBody(_cFunctionBody) {}
};

class NParameter : public Node {
    //Parameter -> string_literal | Expression
public:
    Nstring_literal* cstring_literal;
    NExpression* cexpression;
    NParameter(Nstring_literal* _cstring_literal)
    : cstring_literal(_cstring_literal), cexpression(nullptr) {}
    NParameter(NExpression* _cexpression)
    : cstring_literal(nullptr), cexpression(_cexpression) {}
};

class NFunctionBody : public Node {
    //FunctionBody -> "{" StatementList "}"
public:
    StatementList cStatementList;
    NFunctionBody(StatementList& _cStatementList) : cStatementList(_cStatementList) {}
    NFunctionBody() {}
};

class NStatement : public Node {
    //Statement -> Decleration | FunctionBody | Expression | Assignment | Call
public:
    NDecleration* cDecleration;
    NFunctionBody* cFunctionBody;
    NExpression* cExpression;
    NAssignment* cAssignment;
    NCall* cCall;
    NStatement(NDecleration* _cDecleration) 
    : cDecleration(_cDecleration), cFunctionBody(nullptr), cExpression(nullptr), cAssignment(nullptr), cCall(nullptr) {}
    NStatement(NFunctionBody* _cFunctionBody) 
    : cDecleration(nullptr), cFunctionBody(_cFunctionBody), cExpression(nullptr), cAssignment(nullptr), cCall(nullptr) {}
    NStatement(NExpression* _cExpression) 
    : cDecleration(nullptr), cFunctionBody(nullptr), cExpression(_cExpression), cAssignment(nullptr), cCall(nullptr) {}
    NStatement(NAssignment* _cAssignment) 
    : cDecleration(nullptr), cFunctionBody(nullptr), cExpression(nullptr), cAssignment(_cAssignment), cCall(nullptr) {}
    NStatement(NCall* _cCall) 
    : cDecleration(nullptr), cFunctionBody(nullptr), cExpression(nullptr), cAssignment(nullptr), cCall(_cCall) {}
};

class NDecleration : public Node {
    /* Decleration -> "var" identifier "int" "=" Expression 
             | "var" identifier "string" "=" string_literal
             | "var" identifier "string" "=" identifier 
             | "var" identifier "int"
             | "var" identifier "string" */
public:
    Nidentifier* cidentifier;
    NExpression* cexpression;
    Nstring_literal* cstring_literal;
    Nidentifier* cidentifier2;
    NDecleration(Nidentifier* _cidentifier, NExpression* _cexpression)
    : cidentifier(_cidentifier), cexpression(_cexpression), cstring_literal(nullptr), cidentifier2(nullptr) {}
    NDecleration(Nidentifier* _cidentifier, Nstring_literal* _cstring_literal)
    : cidentifier(_cidentifier), cstring_literal(_cstring_literal), cexpression(nullptr), cidentifier2(nullptr) {}
    NDecleration(Nidentifier* _cidentifier, Nidentifier* _cidentifier2)
    : cidentifier(_cidentifier), cstring_literal(nullptr), cexpression(nullptr), cidentifier2(_cidentifier2) {}
    NDecleration(Nidentifier* _cidentifier)
    : cidentifier(_cidentifier), cexpression(nullptr), cstring_literal(nullptr), cidentifier2(nullptr) {}
}; 

class NExpression : public Node {
    //Expression -> Term | Expression "+" Term | Expression "-" Term
public:
    NTerm* cterm;
    NExpression* cexpression;
    NExpression(NTerm* _cterm)
    : cterm(_cterm), cexpression(nullptr) {}
    NExpression(NExpression* _cexpression, NTerm* _cterm)
    : cexpression(_cexpression), cterm(_cterm) {}
}; 

class NTerm : public Node{
    //Term -> Number | Term "*" Number | Term "/" Number
public:
    NNumber* cnumber;
    NTerm* cterm;
    NTerm(NNumber* _cnumber)
    : cnumber(_cnumber), cterm(nullptr) {}
    NTerm( NTerm* _cterm, NNumber* _cnumber)
    : cterm(_cterm), cnumber(_cnumber) {}
};

class NAssignment : public Node {
    //Assignment -> identifier "=" Expression
public:
    Nidentifier* cidentifier;
    NExpression* cexpression;
    NAssignment(Nidentifier* _cidentifier, NExpression* _cexpression)
    : cidentifier(_cidentifier), cexpression(_cexpression) {}
}; 



class NCall : public Node {
    //Call -> identifier "(" ParameterList ")"
public:
    Nidentifier* cidentifier;
    ParameterList cParameterList;
    NCall(Nidentifier* _cidentifier, ParameterList& _cParameterList)
    : cidentifier(_cidentifier), cParameterList(_cParameterList) {}
    NCall(Nidentifier* _cidentifier)
    : cidentifier(_cidentifier) {}
}; 





