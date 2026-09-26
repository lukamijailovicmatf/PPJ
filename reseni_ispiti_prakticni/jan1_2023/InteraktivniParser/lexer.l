%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    #include "Sifra.hpp"
    #include "parser.tab.hpp"    
%}

%%

"sifra"                     { return SIFRA_T; }

"lista_sifri"               { return LISTA_SIFRI_T; }

"stampaj"                   { return STAMPAJ_T; }

"fst"                       { return FST_T; }

"snd"                       { return SND_T; }

"sum"                       { return SUM_T; }

"=="                        { return EQ_T; }

"!="                        { return NEQ_T; }

"<"                         { return LT_T; }

"<="                        { return LE_T; }

">"                         { return GT_T; }

">="                        { return GE_T; }

[a-zA-Z_][a-zA-Z0-9_]*      { 
    yylval.s_val = new std::string(yytext);
    return ID_T; 
}

[0-9]+\.[0-9]+              { 
    yylval.d_val = std::stod(yytext);
    return REAL_T; 
}

[0-9]+                      { 
    yylval.i_val = std::stoi(yytext);
    return INT_T; 
}

[;()\[\],=+*/.?-]           { return *yytext; }

"//".*                      { }

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%