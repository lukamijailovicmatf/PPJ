%option noyywrap

%{
    #include <iostream>
    
    #include "Formula.hpp"
    #include "parser.tab.hpp"
%}

%%

"True"          { return TRUE_TOKEN; }

"False"         { return FALSE_TOKEN; }

"Undef"         { return UNDEF_TOKEN; }

"head"          { return HEAD; }

"tail"          { return TAIL; }

":="            { return DODELA; }

"/\\"           { return I; }

"\\/"           { return ILI; }

"<=>"           { return EQV; }

[!]             { return NOT; }

"=>"            { return IMPL; }

[0-9]*          { 
    yylval.vrednost = atoi(yytext);
    return BROJ; 
}

[A-Z][0-9]*     { 
    yylval.ime_liste = new std::string(yytext);
    return L_ID; 
}

[a-z][0-9]*     { 
    yylval.ime = new std::string(yytext);
    return ID; 
}

[()\n\[\],]     { return *yytext; }

[ \t]           { }

.               {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%