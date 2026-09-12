%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>

    #include "parser.tab.hpp"
%}

%%

"print"                     { return PRINT_T; }

"ugao"                      { return UGAO_T; }

"eqv"                       { return EQV_T; }

":="                        { return DODELA_T; }

[a-z]                       { 
    yylval.ime = new std::string(yytext);
    return ID_T; 
}

(-)?[0-9][0-9]*             { 
    yylval.vrednost = atoi(yytext);
    return BROJ_T; 
}

(-)?[0-9][.]?[0-9]*         { 
    yylval.vrednost = atof(yytext);
    return BROJ_T; 
}

[<>,;()+*||.-]              { return *yytext; }

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%