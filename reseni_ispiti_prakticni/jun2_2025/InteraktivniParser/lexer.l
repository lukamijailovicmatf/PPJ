%option noyywrap


%{
    #include <iostream> 
    #include <cstdlib>
    #include <string>

    #include "parser.tab.hpp"

%}

%%

"print"                         { return PRINT_T; }

"broj_jedinica"                 { return BROJ_JEDINICA_T; }

"broj_nula"                     { return BROJ_NULA_T; }

">>"                            { return SHR_T; }

"<<"                            { return SHL_T; }

[a-zA-Z_][a-zA-Z0-9_]*          { 
    yylval.niska = new std::string(yytext);
    return ID_T; 
}

[01]+                           { 
    yylval.niska = new std::string(yytext);
    return BINARNI_T; 
}

[=;()~&|?:\[\]]                 { return *yytext; }

"//".*                          { }

[ \t\n]                         { }

.                               {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
