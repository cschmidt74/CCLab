%option noyywrap 

%{
#include <string>
#include "node.hpp"
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

%}

%%

 /* whitespace */
[ \t\n] {/**/;}

 /* keywords */
"package"	{ return TOKEN(tpackage); }
"func"		{ return TOKEN(tfunc); }
"quit" 		{ return TOKEN(tquit);}
"var"		{ return TOKEN(tvar); }
"int"		{ return TOKEN(tint); }
"string"	{ return TOKEN(tstring); }

 /* data & types */
[a-zA-Z][a-zA-Z0-9_]*	{ SAVE_TOKEN; return tidentifier; }
\"[a-zA-Z0-9_]*\"		{ SAVE_TOKEN; return tstring_literal; }
[0-9]+					{ SAVE_TOKEN; return tnumber; }

 /* operators */
"+"	{ return TOKEN(taddop); }
"-" { return TOKEN(tsubtractop); }
"*" { return TOKEN(tmultiplyop); }
"/" { return TOKEN(tdivideop); }
"=" { return TOKEN(tequalop); }

 /* parens */
"("	{ return TOKEN(tlparen); }
")" { return TOKEN(trparen); }
"{" { return TOKEN(tlbrace); }
"}" { return TOKEN(trbrace); }

 /* dots'n'commas */
","	{ return TOKEN(tcomma); }
";"	{ return TOKEN(tsemicolon); }

 /* everything else */
.	{ printf("Unknown token!n"); yyterminate(); }


%%