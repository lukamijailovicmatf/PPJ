%option noyywrap

%{
    #include <iostream>    
    #include <cstdlib>

    #include "Razlomak.hpp"
    #include "parser.tab.hpp"
%}

%%

"razlomak"                              { return RAZLOMAK_T; }

"stampaj"                               { return STAMPAJ_T; }

"proveri"                               { return PROVERI_T; }

[a-z]                                   { 
    yylval.ime = new std::string(yytext);
    return ID_T; 
}

[-]?[0-9]+                              { 
    yylval.vrednost = atoi(yytext);
    return BROJ_T; 
}

"<="                                    { return LE_T; }

">="                                    { return GE_T; }

"=="                                    { return EQ_T; }

"!="                                    { return NEQ_T; }

[\[\];,=+*/^()~<>-]                     { return *yytext; }

[ \t\n]                                 { }

.                                       {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%