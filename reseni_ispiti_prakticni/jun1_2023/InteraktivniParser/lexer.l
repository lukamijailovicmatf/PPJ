%option noyywrap

%{
    #include <iostream>    
    #include <cstdlib>

    #include "parser.tab.hpp"    
%}

%%

"stack<int>"                    { return STEK_T; }

"queue<int>"                    { return RED_T; }

"print_stack"                   {return STAMPAJ_STEK_T; }

"print_queue"                   { return STAMPAJ_RED_T; }

":="                            { return DODELA_T; }

[0-9]+                          { return BROJ_T; }

_[a-zA-Z0-9]*                   { return ID_T; }

[;,(){}]                        { return *yytext; }

[ \t\n]                         { }

.                               {
    std::cerr << "leksicka greska: " << yytext << std::endl;
}

%%