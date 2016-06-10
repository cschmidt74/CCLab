#!/bin/bash

echo "Compiling: parser.y => parser.cpp & parser.hpp"
bison -o parser.cpp parser.y

echo "Compiling: lexer.l => lexer.cpp"
flex -o lexer.cpp lexer.l

echo "Compiling: main.cpp => main"
g++ -o main parser.cpp lexer.cpp main.cpp