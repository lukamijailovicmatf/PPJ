#include <iostream>
#include <string>
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
void IZRAZ();
void IZRAZ_P();
void T();
void TP();
void F();
void NIZ_BROJEVA();
void NIZ_BROJEVA_P();
void KONST();

// gramatika:                                   skupovi izbora:
//
// NIZ_NAREDBI -> NAREDBA ; NIZ_NAREDBI'        { id, print }
//
// NIZ_NAREDBI' -> NIZ_NAREDBI                  { id, print }
//               | eps                          { -| }
//
// NAREDBA -> id dodela IZRAZ                   { id }
//          | print ( IZRAZ )                   { print }
//
// IZRAZ -> T IZRAZ'                            { <, id, broj }
//
// IZRAZ' -> + T IZRAZ'                         { + }
//         | - T IZRAZ'                         { - }
//         | eps                                { ;, ) }
//
// T -> F T'                                    { <, id, broj }
//
// T' -> * F T'                                 { * }
//     | eps                                    { +, -, ;, ) }
//
// F -> < NIZ_BROJEVA >                         { < }
//    | id                                      { id }
//    | broj                                    { broj }
//
// NIZ_BROJEVA -> KONST NIZ_BROJEVA'            { broj, - }
//
// NIZ_BROJEVA' -> , KONST NIZ_BROJEVA'         { , }
//               | eps                          { > }
//
// KONST -> broj                                { broj }
//        | - broj                              { - }

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
    if (preduvid == id_token || preduvid == print_token) {
        std::cout << "NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI'" << std::endl;
        NAREDBA();
        if (preduvid != ';') {
            greska("[NIZ_NAREDBI]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI]: Ocekujem id ili print");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == id_token || preduvid == print_token) {
        std::cout << "NIZ_NAREDBI' => NIZ_NAREDBI" << std::endl;
        NIZ_NAREDBI();
    } else if (preduvid == eoi) {
        std::cout << "NIZ_NAREDBI' => eps" << std::endl;
    } else {
        greska("[NIZ_NAREDBI']: Ocekujem id, print ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == id_token) {
        std::cout << "NAREDBA => id dodela IZRAZ" << std::endl;
        preduvid = yylex();
        if (preduvid != dodela_token) {
        greska("[NAREDBA]: Ocekujem :=");
        } else {
            preduvid = yylex();
        }
        IZRAZ();
    } else if (preduvid == print_token) {
        std::cout << "NAREDBA => print ( IZRAZ )" << std::endl;
        preduvid = yylex();
        if (preduvid != '(') {
        greska("[NAREDBA]: Ocekujem (");
        } else {
            preduvid = yylex();
        }
        IZRAZ();
        if (preduvid != ')') {
        greska("[NAREDBA]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA]: Ocekujem id ili print");
    }
}

void IZRAZ() {
    if (preduvid == '<' || preduvid == id_token || preduvid == broj_token) {
        std::cout << "IZRAZ => T IZRAZ'" << std::endl;
        T();
        IZRAZ_P();
    } else {
        greska("[IZRAZ]: Ocekujem <, id ili broj");

    }
}

void IZRAZ_P() {
    if (preduvid == '+') {
        std::cout << "IZRAZ' => + T IZRAZ'" << std::endl;
        preduvid = yylex();
        T();
        IZRAZ_P();
    } else if (preduvid == '-') {
        std::cout << "IZRAZ' => - T IZRAZ'" << std::endl;
        preduvid = yylex();
        T();
        IZRAZ_P();
    } else if (preduvid == ';' || preduvid == ')') {
        std::cout << "IZRAZ' => eps" << std::endl;
    } else {
        greska("[IZRAZ']: Ocekujem +, -, ; ili )");

    }
}

void T() {
    if (preduvid == '<' || preduvid == id_token || preduvid == broj_token) {
        std::cout << "T => F T'" << std::endl;
        F();
        TP();
    } else {
        greska("[T]: Ocekujem <, id ili broj");

    }
}

void TP() {
    if (preduvid == '*') {
        std::cout << "T' => * F T'" << std::endl;
        preduvid = yylex();
        F();
        TP();
    } else if (preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')') {
        std::cout << "T' => eps" << std::endl;
    } else {
        greska("[T']: Ocekujem +, -, ; ili )");

    }
}

void F() {
    if (preduvid == '<') {
        std::cout << "F => < NIZ_BROJEVA >" << std::endl;
        preduvid = yylex();
        NIZ_BROJEVA();
        if (preduvid != '>') {
            greska("[F]: Ocekujem >");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == id_token) {
        std::cout << "F => id" << std::endl;
        preduvid = yylex();
    } else if (preduvid == broj_token) {
        std::cout << "F => broj" << std::endl;
        preduvid = yylex();
    } else {
        greska("[F]: Ocekujem <, id ili broj");

    }
}

void NIZ_BROJEVA() {
    if (preduvid == broj_token || preduvid == '-') {
        std::cout << "NIZ_BROJEVA => KONST NIZ_BROJEVA'" << std::endl;
        KONST();
        NIZ_BROJEVA_P();
    } else {
        greska("[NIZ_BROJEVA]: Ocekujem broj ili -");

    }
}

void NIZ_BROJEVA_P() {
    if (preduvid == ',') {
        std::cout << "NIZ_BROJEVA' => , KONST NIZ_BROJEVA'" << std::endl;
        preduvid = yylex();
        KONST();
        NIZ_BROJEVA_P();
    } else if (preduvid == '>') {
        std::cout << "NIZ_BROJEVA' => eps" << std::endl;
    } else {
        greska("[NIZ_BROJEVA']: Ocekujem , ili >");

    }
}

void KONST() {
    if (preduvid == broj_token) {
        std::cout << "KONST => broj" << std::endl;
        preduvid = yylex();
    } else if (preduvid == '-') {
        std::cout << "KONST => - broj" << std::endl;
        preduvid = yylex();
        if (preduvid != broj_token) {
        greska("[KONST]: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[KONST]: Ocekujem broj ili -");

    }
}