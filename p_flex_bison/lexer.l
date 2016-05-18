%{
	using namespace std;
	// global value for int tokens
	int yylval = 0;

	typedef enum {
		PACKAGE, IMPORT, FUNC, 				/* 0, 1, 2 */
		IDENTIFIER, LITERAL, NUMBER, 		/* 3, 4, 5 */
		PAREN_L, PAREN_R, /* '(' ')' */     /* 6, 7 */
		BRACE_L, BRACE_R, /* '{' '}' */		/* 8, 9 */
		BRACK_L, BRACK_R, /* '[' ']' */		/* 10, 11 */
		SEMICOLON, COMMA, DOT, 				/* 12, 13, 14 */
		FINISHED, UNKNOWN					/* 15, 16 */
	} tokenType;
%}

digit [1-9]
letter [a-zA-Z]

%%
"package"							{ return PACKAGE;				}
"import"							{ return IMPORT;				}
"func"								{ return FUNC;					}
"(" 								{ return PAREN_L;				}
")"									{ return PAREN_R;				}
"{"									{ return PAREN_L;				}
"}"									{ return PAREN_R;				}
"["									{ return BRACK_L;				}
"]"									{ return BRACK_R;				}
";"									{ return SEMICOLON;				}
","									{ return COMMA;					}
"."									{ return DOT;					}
[1-9]{digit}*						{ return NUMBER; 				}
({letter}|_)({letter}|{digit}|_)*	{ return IDENTIFIER;			}
\"({letter}|_)({letter}|{digit}|_)*\"   { return LITERAL; }
[ \t\n]								{ ;								}
.									{ printf("unkown character\n");	
									  return UNKNOWN;				}
<<EOF>>								{ return FINISHED;				}

%%

int yywrap(void){ return 1; }

int main( int argc, char *argv[] ) {
 yyin = ( ( 2 == argc ) ? fopen( argv[1], "r" ): stdin );

 /* Call the lexer, then quit. */
 int tok = -1;
 while ( tok != FINISHED ) {
	 tok = yylex();
	 printf("Token= %d,\t last value of yylval= %d\n", tok, yylval);
 };
 return 0;
}