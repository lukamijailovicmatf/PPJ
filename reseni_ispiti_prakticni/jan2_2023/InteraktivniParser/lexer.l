%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    #include "Lista.hpp"
    #include "parser.tab.hpp"    
%}

%%

"list"                      { return LIST_T; }

"number"                    { return NUMBER_TYPE_T; }

"string"                    { return STRING_TYPE_T; }

"print"                     { return PRINT_T; }

"print_r"                   { return PRINT_R_T; }

"push_back"                 { return PUSH_BACK_T; }

"push_front"                { return PUSH_FRONT_T; }

"push"                      { return PUSH_T; }

"pop_back"                  { return POP_BACK_T; }

"pop_front"                 { return POP_FRONT_T; }

"pop"                       { return POP_T; }

"get"                       { return GET_T; }

"find"                      { return FIND_T; }

"=="                        { return EQ_T; }

"!="                        { return NEQ_T; }

"<="                        { return LEQ_T; }

">="                        { return GEQ_T; }

[a-zA-Z_][a-zA-Z0-9_]*      { 
    yylval.niska = new std::string(yytext);
    return ID_T; 
}

[0-9]+(\.[0-9]+)?           { 
    yylval.niska = new std::string(yytext);
    return BROJ_T; 
}

\"[^\"]*\"                  { 
    yylval.niska = new std::string(yytext);
    return STRING_T; 
}

[<>;={},.()+*-]             { return *yytext; }

"//".*                      { }

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%