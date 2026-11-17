#include <iostream>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

void NIZ_NAREDBI();
void NIZ_NAREDBI_P();
void NAREDBA();
void NAREDBA_P();
void NAREDBA_P_P();
void NIZ_BROJEVA();
void NIZ_BROJEVA_P();

// gramatika                                    skupovi izbora

// NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI'          { stack, id, print_stack }
//
// NIZ_NAREDBI' -> NAREDBA NIZ_NAREDBI'         { stack, id, print_stack }
//               | eps                          { -| }
//
// NAREDBA -> stack < int_token > id NAREDBA'   { stack }
//          | id dodela_token id ;              { id }
//          | print_stack ( id ) ;              { print_stack }
//
// NAREDBA' -> ;                                { ; }
//           | dodela_token NAREDBA''           { dodela_token }
//
// NAREDBA'' -> { NIZ_BROJEVA } ;               { { }
//            | id ;                            { id }
//
// NIZ_BROJEVA -> broj NIZ_BROJEVA'             { broj }
//
// NIZ_BROJEVA' -> , broj NIZ_BROJEVA'          { , }
//               | eps                          { } } 

int main() {

    preduvid = yylex();
    NIZ_NAREDBI();

    if (preduvid != eoi) {
        greska("Recenica se ne prihvata");
    } else {
        std::cout << "Recenica se prihvata" << std::endl;
    }

    return 0;
}

void NIZ_NAREDBI() {
    if (preduvid == stek_token || preduvid == id_token || preduvid == print_token) {
        std::cout << "NIZ_NAREDBI => NAREDBA NIZ_NAREDBI'" << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI]: Ocekujem stack, id ili print_stack");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == stek_token || preduvid == id_token || preduvid == print_token) {
        std::cout << "NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI'" << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else if (preduvid == eoi) {
        std::cout << "NIZ_NAREDBI' => eps" << std::endl;
    } else {
        greska("[NIZ_NAREDBI']: Ocekujem stack, id, print_stack ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == stek_token) {
        std::cout << "NAREDBA => stack < int_token > id NAREDBA'" << std::endl;
        preduvid = yylex();
        if (preduvid != '<') {
            greska("[NAREDBA]: Ocekujem <");
        } else {
            preduvid = yylex();
        }
        if (preduvid != int_token) {
            greska("[NAREDBA]: Ocekujem int");
        } else {
            preduvid = yylex();
        }
        if (preduvid != '>') {
            greska("[NAREDBA]: Ocekujem >");
        } else {
            preduvid = yylex();
        }
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        NAREDBA_P();
    } else if (preduvid == id_token) {
        std::cout << "NAREDBA => id dodela_token id ;" << std::endl;
        preduvid = yylex();
        if (preduvid != dodela_token) {
            greska("[NAREDBA]: Ocekujem :=");
        } else {
            preduvid = yylex();
        }
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == print_token) {
        std::cout << "NAREDBA => print_stack ( id ) ;" << std::endl;
        preduvid = yylex();
        if (preduvid != '(') {
            greska("[NAREDBA]: Ocekujem (");
        } else {
            preduvid = yylex();
        }
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ')') {
            greska("[NAREDBA]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA]: Ocekujem stack, id ili print_stack");
    }
}

void NAREDBA_P() {
    if (preduvid == ';') {
        std::cout << "NAREDBA' => ;" << std::endl;
        preduvid = yylex();
    } else if (preduvid == dodela_token) {
        std::cout << "NAREDBA' => dodela_token NAREDBA''" << std::endl;
        preduvid = yylex();
        NAREDBA_P_P();
    } else {
        greska("[NAREDBA']: Ocekujem ; ili :=");
    }
}

void NAREDBA_P_P() {
    if (preduvid == '{') {
        std::cout << "NAREDBA'' => { NIZ_BROJEVA } ;" << std::endl;
        preduvid = yylex();
        NIZ_BROJEVA();
        if (preduvid != '}') {
            greska("[NAREDBA'']: Ocekujem }");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA'']: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == id_token) {
        std::cout << "NAREDBA'' => id ;" << std::endl;
        preduvid = yylex();
        if (preduvid != ';') {
            greska("[NAREDBA'']: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA'']: Ocekujem { ili id");
    }
}

void NIZ_BROJEVA() {
    if (preduvid == broj_token) {
        std::cout << "NIZ_BROJEVA => broj NIZ_BROJEVA'" << std::endl;
        preduvid = yylex();
        NIZ_BROJEVA_P();
    } else {
        greska("[NIZ_BROJEVA]: Ocekujem broj");
    }
}

void NIZ_BROJEVA_P() {
    if (preduvid == ',') {
        std::cout << "NIZ_BROJEVA' => , broj NIZ_BROJEVA'" << std::endl;
        preduvid = yylex();
        if (preduvid != broj_token) {
            greska("[NIZ_BROJEVA']: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        NIZ_BROJEVA_P();
    } else if (preduvid == '}') {
        std::cout << "NIZ_BROJEVA' => eps" << std::endl;
    } else {
        greska("[NIZ_BROJEVA']: Ocekujem , ili }");
    }
}