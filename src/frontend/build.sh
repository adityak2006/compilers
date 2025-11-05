#!/bin/bash
flex lexer.l
bison -d parser.y
g++ -std=c++17 -I. lex.yy.c parser.tab.c symbol_table_printer.cpp ast.cpp -o sim
