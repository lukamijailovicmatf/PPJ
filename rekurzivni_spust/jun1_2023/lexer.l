%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"    
%}

%%

"stack"                             { return stek_token; }

"int"                               { return int_token; }

":="                                { return dodela_token; }

"print_stack"                       { return print_token; }

[_][a-zA-Z0-9][a-zA-Z0-9]*          { return id_token; }

[1-9]+                              { return broj_token; }

[;{},()<>]                          { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%