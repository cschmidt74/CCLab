%defines 

%{
	#include <iostream>
	#include <cmath>

	extern int yylex();
	extern void yyerror(char const* msg);	
%}

%union{
	double dbl;
};

%token<dbl> LITERAL_DBL

%type<dbl> expr
%type<dbl> term

%start program

%%
program: /* empty */
	| program expr '\n' { std::cout << $2 << std::endl; }
	; 

expr: term { $$ = $1; }
	| expr '+' term { $$ = $1 + $3;}
	| expr '-' term { $$ = $1 - $3; }
	;

term: LITERAL_DBL { $$ = $1; }
	| term '*' LITERAL_DBL { $$ = $1 * $3; }
	| term '/' LITERAL_DBL { $$ = $1 / $3; }
	;

%%

extern void yyerror(char const* msg){
	std::cout << "Syntax Error: " << msg << std::endl;
}