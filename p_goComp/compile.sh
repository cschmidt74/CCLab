#!/bin/bash

echo "compiling (bison): parser.y => parser.cpp, parser.hpp"
bison -d -o parser.cpp parser.y

echo "compiling (lex): lexer.l => lexer.cpp"
lex -o lexer.cpp lexer.l

echo "compiling (g++): parser.cpp, lexer.cpp, main.cpp => parser"
g++ -o parser parser.cpp lexer.cpp main.cpp