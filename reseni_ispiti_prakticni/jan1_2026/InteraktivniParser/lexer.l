%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <string>


    #include "parser.tab.hpp"    
%}

%%

"List"                                  { return LIST_T; }

"print"                                 { return PRINT_T; }

"append"                                { return APPEND_T; }

[a-z][a-zA-Z0-9]*                       { 
    yylval.niska = new std::string(yytext);
    return ID_T; 
}

[0-9]+                                  { 
    yylval.broj = atoi(yytext);
    return BROJ_T; 
}

\"[^"]*\"                               { 
    yylval.niska = new std::string(yytext);
    return KOMENTAR_T; 
}

[=;,\[\]()""+*.]                        { return *yytext; }

[ \t\n]                                 { }

"//".*                                  { }     

.                                       {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%