%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"    
%}

%%

"print"                             { return print_token; }

":="                                { return dodela_token; }

[a-zA-Z_][a-zA-Z0-9_]*              { return id_token; }

(0|[1-9][0-9]*)(\.[0-9]+)?          { return broj_token; }

[<>.,;()+*-]                        { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%