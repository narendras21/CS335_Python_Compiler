#!/bin/bash
# Run Flex on lexer.l
flex lexer.l
# Run Bison on parser.y./
bison -d parser.y
# Compile the generated files with g++
g++ -o compiler.exe lex.yy.c parser.tab.c
