%option noyywrap

%{
    #include <iostream>
    #include "tokeni.hpp"    
%}

%%

"razlomak"                          { return razlomak_token; }

"stampaj"                           { return stampaj_token; }

[a-zA-Z_][a-zA-Z_0-9]*              { return id_token; }

[-]?(0|[1-9][0-9]*)                 { return broj_token; }

[;=\[\],]                           { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%