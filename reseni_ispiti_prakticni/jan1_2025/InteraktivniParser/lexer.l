%option noyywrap

%{
    #include <iostream>    
    #include <cstdlib>

    #include "parser.tab.hpp"    
%}

%%

"True"                          { return TRUE_T; }

"False"                         { return FALSE_T; }

"Undef"                         { return UNDEF_T; }

":="                            { return DODELA_T; }

[a-z]                           { 
    yylval.id = yytext[0];
    return ID_T; 
}

"/\\"                           { return AND_T; }

"\\/"                           { return OR_T; }

"=>"                            { return IMPL_T; }

"<=>"                           { return EQUIV_T; }

"!"                             { return NOT_T; }

[()]                            { return *yytext; }

[ \t\n]                         { }

.                               {
    std::cout << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%