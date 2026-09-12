%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    
    #include "parser.tab.hpp"
%}

%%

"def"                           { return DEF; }

"print"                         { return PRINT; }

%[bdh]                          {
    yylval.c = yytext[1]; 
    return FMT; 
}

[a-zA-Z_][a-zA-Z0-9_]*          {
    yylval.s = new std::string(yytext); 
    return ID; 
}

[0-9]+                          { 
    yylval.d = atoi(yytext);
    return BROJ; 
}

"=="                            { return EQ; }

"!="                            { return NEQ; }

"<="                            { return LEQ; }

">="                            { return GEQ; }

"<<"                            { return SHL; }

">>"                            { return SHR; }

[=;""(),%+*/~|&^-]              { return *yytext; }

[ \t\n]                         { }

.                               {
    std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
    exit(EXIT_FAILURE);
}

%%