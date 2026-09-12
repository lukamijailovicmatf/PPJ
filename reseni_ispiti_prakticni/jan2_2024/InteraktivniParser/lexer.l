%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <map>
    #include <exception>
    
    #include "SymbolTable.hpp"
    #include "parser.tab.hpp"
%}

%%

"start"                     { return START; }

"string"                    { return STRING; }

"std_output"                { return OUT; }

"std_input"                 { return IN; }

"std_error"                 { return ERR; }

"print_ALL"                 { return PRINT; }

"end"                       { return END; }

"if"                        { return IF; }

"else"                      { return ELSE; }

"<<"                        { return SHL; }

">>"                        { return SHR; }

[a-zA-Z_][a-zA-Z0-9_]*      {
    yylval.s = new std::string(yytext);
    return ID; 
}

[""][^""]*[""]              { 
    yylval.s = new std::string(yytext);
    return STRING_CONST; 
}

"=="                        { return EQ; }

"!="                        { return NEQ; }

[:;=*+~(){}]                { return *yytext; }

"//".*                      { }

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%