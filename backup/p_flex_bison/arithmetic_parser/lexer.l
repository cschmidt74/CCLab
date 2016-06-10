%option noyywrap

%{
	#include <cstdlib>
	#include "parser.hpp"
	using namespace std;

	extern int yyparse();

%}

digits [0-9]+
binopr [-+*/]
parenthesis [()]

%%
{digits} { yylval.dbl = atof(yytext); return LITERAL_DBL; }

{binopr} { return yytext[0]; }

\n { return '\n'; }

. {}

%%
