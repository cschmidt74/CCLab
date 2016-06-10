/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tidentifier = 258,
    tstring_literal = 259,
    tnumber = 260,
    tlparen = 261,
    trparen = 262,
    tlbrace = 263,
    trbrace = 264,
    tcomma = 265,
    tsemicolon = 266,
    tpackage = 267,
    tfunc = 268,
    tquit = 269,
    tvar = 270,
    tint = 271,
    tstring = 272,
    taddop = 273,
    tsubtractop = 274,
    tmultiplyop = 275,
    tdivideop = 276,
    tequalop = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "parser.y" /* yacc.c:1909  */

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

    std::string *string;
    int token;

#line 105 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
