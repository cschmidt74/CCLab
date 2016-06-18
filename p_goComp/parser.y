%{
    #include <iostream>
    #include <vector>
    #include "node.hpp"
    
    /* AST-Root */
    NProgramStart* root; 

    extern int yylex();
    void yyerror(const char *s) { std::cout << "ERROR: " << s << std::endl; }
%}

/* Data-Access-Representatiobn */
%union {
    Node* node;

    Nidentifier* identifier;
    Nstring_literal* string_literal;
    Ninteger* integer;

    NProgramStart* programstart;
    NPackageClause* packageclause;
    NFunctionDecl* functiondecl;
    NFunction* function;
    NParameter* parameter;
    NFunctionBody* functionbody;
    NStatement* statement;
    NDecleration* decleration; 
    NExpression* expression; 
    NTerm* term;
    NAssignment* assignment;
    NCall* call; 
    NNumber* number;

    std::vector<NParameter*> *parametervec;
    std::vector<NStatement*> *statementvec;
    std::vector<NDecleration*> *paramdeclvec;

    std::string *string;
    int token;
}

/* match lexer.l */
%token <string> tidentifier tstring_literal tnumber
%token <token> tlparen trparen tlbrace trbrace tcomma tsemicolon
%token <token> tpackage tfunc tquit tvar tint tstring
%token <token> taddop tsubtractop tmultiplyop tdivideop tequalop

/* refer to %union declaration */
%type <identifier> IDENTIFIER;
%type <string_literal> STRING_LITERAL;
%type <number> NUMBER;
%type <packageclause> PACKAGECLAUSE;
%type <functiondecl> FUNCTIONDECL;
%type <function> FUNCTION;
%type <parameter> PARAMETER;
%type <functionbody> FUNCTIONBODY;
%type <statement> STATEMENT;
%type <expression> EXPRESSION; 
%type <term> TERM;
%type <decleration> DECLERATION;
%type <integer> INTEGER;
%type <assignment> ASSIGNMENT;
%type <call> CALL; 
%type <parametervec> PARAMETERLIST;
%type <statementvec> STATEMENTLIST;
%type <paramdeclvec> PARAMDECLLIST;

%start PROGRAM

%%
/* ProgramStart -> PackageClause FunctionDecl */
PROGRAM : PACKAGECLAUSE FUNCTIONDECL
  { root = new  NProgramStart($1, $2); } 
;

/* identifier -> letter(letter|number|"_")* */
IDENTIFIER : tidentifier 
  { $$ = new Nidentifier(*$1); delete $1; } 
;

/* string_literal -> """ letter(letter|number|"_")* """ */
STRING_LITERAL : tstring_literal
  { $$ = new Nstring_literal(*$1); delete $1; }
;

/* number -> (0-9)(0-9)* */
INTEGER : tnumber
  { int value = atoi($1->c_str());
    $$ = new Ninteger(value); 
    delete $1; 
  }
;

/* PackageClause -> "package" IDENTIFIER ";" */
PACKAGECLAUSE : tpackage IDENTIFIER tsemicolon 
  { $$ = new NPackageClause($2); } 
;

/* FunctionDecl -> "func" identifier Function */
FUNCTIONDECL : tfunc IDENTIFIER FUNCTION 
  { $$ = new NFunctionDecl($2, $3); } 
;

/* Function -> "(" ParameterList ")" FunctionBody */
FUNCTION : tlparen PARAMDECLLIST trparen FUNCTIONBODY 
  { $$ = new NFunction(*$2, $4); delete $2; } 
;

/* ParamDeclList -> ParamDeclList "," Decleration | Decleration | € */
PARAMDECLLIST : PARAMDECLLIST tcomma DECLERATION
  { $1->push_back($<decleration>3); }
  | DECLERATION
    { $$ = new ParamDeclList(); $$->push_back($<decleration>1); }
  | /*epsilon*/
    { $$ = new ParamDeclList(); }

/* ParameterList -> ParameterList "," Parameter | Parameter | € */
PARAMETERLIST : PARAMETERLIST tcomma PARAMETER 
  { $1->push_back($<parameter>3); } 
  | PARAMETER 
    { $$ = new ParameterList();  $$->push_back($<parameter>1); }
  | /*epsilon*/ 
    { $$ = new ParameterList(); }
;

/* Parameter -> string_literal | Expression */
PARAMETER : STRING_LITERAL
  { $$ = new NParameter($1); }
  | EXPRESSION
    { $$ = new NParameter($1); }
;    

/* FunctionBody -> "{" StatementList "}" */
FUNCTIONBODY : tlbrace STATEMENTLIST trbrace 
  { $$ = new NFunctionBody(*$2); delete $2; } 
;

/* StatementList -> StatementList Statement ";" | € */
STATEMENTLIST : STATEMENTLIST STATEMENT tsemicolon 
  { $1->push_back($<statement>2); }
  | /*epsilpn*/ 
    { $$ = new StatementList(); }
;

/* Statement -> Decleration | FunctionBody | Expression | Assignment | Call */
STATEMENT : FUNCTIONBODY
  { $$ = new NStatement($1); }
  | CALL 
    { $$ = new NStatement($1); }
  | EXPRESSION
    { $$ = new NStatement($1); }
  | DECLERATION
    { $$ = new NStatement($1); }
  | ASSIGNMENT
    { $$ = new NStatement($1); }
;

/* Decleration -> "var" identifier "int" "=" Expression 
       | "var" identifier "string" "=" string_literal
       | "var" identifier "string" "=" identifier
       | "var" identifier "int"
       | "var" identifier "string" */
DECLERATION : tvar IDENTIFIER tint tequalop EXPRESSION  
  { new NDecleration($2, $5); }
  | tvar IDENTIFIER tstring tequalop STRING_LITERAL
    { new NDecleration($2, $5); }
  | tvar IDENTIFIER tstring tequalop IDENTIFIER
    { new NDecleration($2, $5); }
  | tvar IDENTIFIER tint 
    { new NDecleration($2); }
  | tvar IDENTIFIER tstring
    { new NDecleration($2); }
;

/* Expression -> Term | Expression "+" Term | Expression "-" Term */
EXPRESSION : TERM
  { $$ = new NExpression($1); }
  | EXPRESSION taddop TERM
    { $$ = new NExpression($1, $3); }
  | EXPRESSION tsubtractop TERM
    { $$ = new NExpression($1, $3); }
;

/* Term -> Number | Term "*" Number | Term "/" Number */
TERM : NUMBER
  { $$ = new NTerm($1); }
  | TERM tmultiplyop NUMBER
    { $$ = new NTerm($1, $3); }
  | TERM tdivideop NUMBER
    { $$ = new NTerm($1, $3); }
;

/* Number -> integer | identifier */
NUMBER : INTEGER
  { $$ = new NNumber($1); }
  | IDENTIFIER
    { $$ = new NNumber($1); }
;

/* Assignment -> identifier "=" Expression */
ASSIGNMENT : IDENTIFIER tequalop EXPRESSION
  { $$ = new NAssignment($1, $3); }
;

/* Call -> identifier "(" ParameterList ")" */
CALL : IDENTIFIER tlparen PARAMETERLIST trparen
  { $$ = new NCall($1, *$3); delete $3; }
;

%%