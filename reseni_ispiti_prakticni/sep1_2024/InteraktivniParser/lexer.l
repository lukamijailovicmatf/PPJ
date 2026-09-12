%option noyywrap

%{
    #include <iostream>
    #include <set>
    #include <map>
    
    #include "skup.hpp"
    #include "parser.tab.hpp"
%}

%%

"def"                           { return DEF_T; }
"print"                         { return PRINT_T; }
"univ"                              { return UNIV_T; }
"in"                            { return IN_T; }
"sub"                           { return SUB_T; }
"size"                          { return SIZE_T; }

[a-zA-Z][a-zA-Z0-9]*            { 
    yylval.s = new std::string(yytext);
    return ID_T; 
}

[0-9]+                          { 
    yylval.v = atoi(yytext);
    return BROJ_T; 
}

"\\/"                           { return UNIJA_T; }
"/\\"                           { return PRESEK_T; }
"~"                             { return CPL_T; }
"\\"                            { return RAZLIKA_T; }
"=="                            { return EQ_T; }
"!="                            { return NEQ_T; }

[;={},()\[\]]                   { return *yytext; }

[ \t\n]                         { }

"//".*                          { }

.                               {
    std::cerr << "Leksicka greska: " << (*yytext) << std::endl;
    exit(EXIT_FAILURE);
}

%%
