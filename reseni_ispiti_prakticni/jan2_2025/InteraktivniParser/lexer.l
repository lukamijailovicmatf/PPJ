%option noyywrap

%{
    #include <iostream>    
    #include <cstdlib>
    #include <string>

    #include "Kompleksni.hpp"
    #include "parser.tab.hpp"    
%}

%%

"def"                               { return DEF_T; }

"print"                             { return PRINT_T; }

"delete"                            { return DELETE_T; }

"arg"                               { return ARG_T; }

"=="                                { return EQ_T; }

"!="                                { return NEQ_T; }

[a-zA-Z_][a-zA-Z0-9_]*              { 
    yylval.ime = new std::string(yytext);
    return ID_T; 
}

[-]?[0-9]+(\.[0-9]+)?               { 
    yylval.vrednost = atof(yytext);
    return BROJ_T; 
}

[;,.()=<>+*/~|-]                    { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%