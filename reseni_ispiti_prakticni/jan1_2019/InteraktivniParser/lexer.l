%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>

    #include "parser.tab.hpp"    
%}

%%

"print"                                     { return PRINT_T; }

"int"                                       { return INT_T; }

"list"                                      { return LIST_T; }

"<<"                                        { return SHL_T; }

">>"                                        { return SHR_T; }

"=="                                        { return EQV_T; }

[_][a-zA-Z][a-zA-Z0-9]*                     { 
    yylval.ime = new std::string(yytext);
    return ID_T; 
}

(0|[1-9][0-9]*)                             { 
    yylval.broj = atoi(yytext);
    return BROJ_T; 
}

0x(0|[1-9A-F][0-9A-F]*)                     { 
    sscanf(yytext, "%x", &yylval.broj);
    return BROJ_T; 
}

0(0|[1-7][0-7]*)                            { 
    sscanf(yytext, "%o", &yylval.broj);
    return BROJ_T; 
}

l[a-zA-Z0-9_]+                              { 
    yylval.ime = new std::string(yytext);
    return LID_T; }

[=;(),+*/~&|\[\]-]                          { return *yytext; }

[ \t\n]                                     { }

.                                           {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%