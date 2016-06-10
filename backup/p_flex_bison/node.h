#include <iostream>
#include <vector>

//NNT
class Nidentifier;
class Nstring_literal;
//NProd
class NFunctionCall;
class NPackageClause;
class NFunctionDecl;
class NImportDecl;
class NFunction;
class NFunctionBody;
class NArguments;
class NStatement; // element-type of Statementlist
class NArgument; // element-type of ArgumentList

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NArgument*> ArgumentList;

class Node {
public:
    virtual ~Node() {}
};

class NNT : public Node {
};

class NProd : public Node {
};

class Nidentifier : public NNT {
    std::string name;
    Nidentifier(const std::string& _name) : name(_name){}
};

class Nstring_literal : public NNT {
    std::string val;
    Nstring_literal(const std::string& _val) : val(_val){}
};

class NFunctionCall : public NProd {
    Nidentifier& lib; //library holding the function
    Nidentifier& fct; //function-name
    NArguments& arg;
    NFunctionCall(const Nidentifier& _lib, const Nidentifier _fct, const NArguments& _arg)
    : lib(_lib), fct(_fct), arg(_arg) {}
};

class NPackageClause : public NProd {
    Nidentifier& val;
    NPackageClause(const Nidentifier& _val) : val(_val){}
};

class NFunctionDecl : public NProd {
    Nidentifier& name;
    NFunction& val;
    NFunctionDecl(const Nidentifier& _name, const NFunction& _val)
    : name(_name), val(_val) {}
};

class NImportDecl : public NProd {
    Nstring_literal& val;
    NImportDecl(const Nstring_literal& _val) : val(_val) {}
};

class NFunction : public NProd {
    NArguments& arg;
    NFunctionBody& val;
    NFunction(const NArguments& _arg, const NFunctionBody& _val)
    : arg(_arg), val(_val) {}
};

class NFunctionBody : public NProd {
    StatementList statements;
    NFunctionBody() {}
};

class NArguments : public NProd {
    ArgumentList arguments;
    NArguments() {}
};

class NStatement : public NProd {
    NFunctionCall& val;
    bool isEps; // is this needed?
    NStatement(const NFunctionCall& _val) : val(_val) {}
};

class NArgument : public NProd {
    Nstring_literal& val;
    bool isEps; // is this needed?
    NArgument(const Nstring_literal& _val) : val(_val) {}
};