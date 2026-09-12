%option noyywrap

%{
    #include <iostream> 
    #include <cstdlib>
    #include <string>
    #include <vector>

    #include "parser.tab.hpp" 
%}

%%

"out"                       { return IZLAZ_T; }

"<<"                        { return ISPISI_T; }

".reverse()"                { return REVERSE_T; }

".sort()"                   { return SORT_T; }

[a-z][a-z0-9]*              { 
    yylval.ime = new std::string(yytext);
    return ID_T; 
}

[-]?[0-9]+                  { 
    yylval.broj = atoi(yytext);
    return BROJ_T; 
}

[=,\[\]\n+*():]             { return *yytext; }

[ \t]                       { }

.                           {
    std::cout << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%