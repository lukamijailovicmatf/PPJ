%option noyywrap

%{
    #include <iostream>    
    #include "tokeni.hpp"    
%}

%%

"list"                              { return list_token; }

"number"                            { return number_tip_token; }

"string"                            { return string_tip_token; }

"print"                             { return print_token; }

"print_r"                           { return print_r_token; }

[a-zA-Z][a-zA-Z0-9]*                { return id_token; }

[0-9]+                              { return broj_token; }

["][^"]*["]                         { return niska_token; }

[<>;=,{}().]                        { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%