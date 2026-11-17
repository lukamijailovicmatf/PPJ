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
void IZRAZ();
void IZRAZ_P();
void TERM();
void TERM_P();
void FAKTOR();
void FAKTOR_1();
void FAKTOR_2();
void LISTA_SIFRI();
void LISTA_SIFRI_P();

// gramatika:                               skupovi izbora:
//          
// NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI'      { sifra, stampaj, lista_sifri}
//
// NIZ_NAREDBI' -> NAREDBA NIZ_NAREDBI'     { sifra, stampaj, lista_sifri }
//               | eps                      { eoi }
//
// NAREDBA -> sifra id NAREDBA ;            { sifra }
//          | stampaj IZRAZ ;               { stampaj }
//          | lista_sifri id = IZRAZ ;      { lista_sifri }
//
// NAREDBA' -> ;                            { ; }
//           | ( broj , broj ) ;            { ( }
//           | = IZRAZ ;                    { = }
//
// IZRAZ -> TERM IZRAZ'                     { (, id, -, [, broj }
//
// IZRAZ' -> + TERM IZRAZ'                  { + }
//         | - TERM IZRAZ'                  { - }
//         | eps                            { ;, ), ], , }
//
// TERM -> FAKTOR TERM'                     { (, id, -, [, broj }
//
// TERM' -> * FAKTOR TERM'                  { * }
//        | eps                             { +, -, ;, ), , }
//
// FAKTOR -> ( IZRAZ FAKTOR_1               { ( }
//         | id FAKTOR_2                    { id }
//         | - FAKTOR                       { - }
//         | [ LISTA_SIFRI ]                { [ }
//         | broj                           { broj }
//
// FAKTOR_1 -> )                            { ) }
//           | , IZRAZ )                    { , }
//
// FAKTOR_2 -> eps                          { *, +, -, ;, ), , }
//           | . sum ( )                    { . }
//           | [ broj ]                     { [ }
//
// LISTA_SIFRI -> IZRAZ LISTA_SIFRI'        { (, id, -, [, broj}
//
// LISTA_SIFRI' -> , IZRAZ LISTA_SIFRI'     { , }
//               | eps                      { ] }

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
    if (preduvid == sifra_token || preduvid == stampaj_token || preduvid == lista_sifri_token) {
        std::cout << " NIZ_NAREDBI => NAREDBA NIZ_NAREDBI' " << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI]: Ocekujem sifra, stampaj ili lista_sifri");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == sifra_token || preduvid == stampaj_token || preduvid == lista_sifri_token) {
        std::cout << " NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI' " << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else if (preduvid == eoi) {
        std::cout << " NIZ_NAREDBI' => eps " << std::endl;
    } else {
        greska("[NIZ_NAREDBI']: Ocekujem sifra, stampaj, lista_sifri ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == sifra_token) {
        std::cout << " NAREDBA => sifra id NAREDBA' " << std::endl;
        preduvid = yylex();
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        NAREDBA_P();
    } else if (preduvid == stampaj_token) {
        std::cout << " NAREDBA => stampaj IZRAZ ; " << std::endl;
        preduvid = yylex();
        IZRAZ();
        if (preduvid != ';') {
            greska("[NAREDBA]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == lista_sifri_token) {
        std::cout << " NAREDBA => lista_sifri id = IZRAZ ; " << std::endl;
        preduvid = yylex();
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        if (preduvid != '=') {
            greska("[NAREDBA]: Ocekujem =");
        } else {
            preduvid = yylex();
        }
        IZRAZ();
        if (preduvid != ';') {
            greska("[NAREDBA]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA]: Ocekujem sifra, stampaj ili lista_sifri");
    }
}

void NAREDBA_P() {
    if (preduvid == ';') {
        std::cout << " NAREDBA' => ; " << std::endl;
        preduvid = yylex();
    } else if (preduvid == '(') {
        std::cout << " NAREDBA' => ( broj , broj ) ; " << std::endl;
        preduvid = yylex();
        if (preduvid != broj_token) {
            greska("[NAREDBA']: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ',') {
            greska("[NAREDBA']: Ocekujem ,");
        } else {
            preduvid = yylex();
        }
        if (preduvid != broj_token) {
            greska("[NAREDBA']: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ')') {
            greska("[NAREDBA']: Ocekujem )");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA']: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == '=') {
        std::cout << " NAREDBA' => = IZRAZ ; " << std::endl;
        preduvid = yylex();
        IZRAZ();
        if (preduvid != ';') {
            greska("[NAREDBA']: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA']: Ocekujem ;, ( ili =");
    }
}

void IZRAZ() {
    if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
        std::cout << " IZRAZ => TERM IZRAZ' " << std::endl;
        TERM();
        IZRAZ_P();
    } else {
        greska("[IZRAZ]: Ocekujem (, id, -, [ ili broj");
    }
}

void IZRAZ_P() {
    if (preduvid == '+') {
        std::cout << " IZRAZ' => + TERM IZRAZ' " << std::endl;
        preduvid = yylex();
        TERM();
        IZRAZ_P();
    } else if (preduvid == '-') {
        std::cout << " IZRAZ' => - TERM IZRAZ' " << std::endl;
        preduvid = yylex();
        TERM();
        IZRAZ_P();
    } else if (preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
        std::cout << " IZRAZ' => eps " << std::endl;
    } else {
        greska("[IZRAZ']: Ocekujem +, -, ;, ), ] ili ,");
    }
}

void TERM() {
    if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
        std::cout << " TERM => FAKTOR TERM' " << std::endl;
        FAKTOR();
        TERM_P();
    } else {
        greska("[TERM]: Ocekujem (, id, -, [ ili broj");
    }
}

void TERM_P() {
    if (preduvid == '*') {
        std::cout << " TERM' => * FAKTOR TERM' " << std::endl;
        preduvid = yylex();
        FAKTOR();
        TERM_P();
    } else if (preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
        std::cout << " TERM' => eps " << std::endl;
    } else {
        greska("[TERM']: Ocekujem *, +, -, ;, ) ili ,");
    }
}

void FAKTOR() {
    if (preduvid == '(') {
        std::cout << " FAKTOR => ( IZRAZ FAKTOR_1 " << std::endl;
        preduvid = yylex();
        IZRAZ();
        FAKTOR_1();
    } else if (preduvid == id_token) {
        std::cout << " FAKTOR => id FAKTOR_2 " << std::endl;
        preduvid = yylex();
        FAKTOR_2();
    } else if (preduvid == '-') {
        std::cout << " FAKTOR => - FAKTOR " << std::endl;
        preduvid = yylex();
        FAKTOR();
    } else if (preduvid == '[') {
        std::cout << " FAKTOR => [ LISTA_SIFRI ] " << std::endl;
        preduvid = yylex();
        LISTA_SIFRI();
        if (preduvid != ']') {
            greska("[FAKTOR]: Ocekujem ]");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == broj_token) {
        std::cout << " FAKTOR => broj " << std::endl;
        preduvid = yylex();
    } else {
        greska("[FAKTOR]: Ocekujem (, id, -, [ ili broj");
    }
}

void FAKTOR_1() {
    if (preduvid == ')') {
        std::cout << " FAKTOR_1 => ) " << std::endl;
        preduvid = yylex();
    } else if (preduvid == ',') {
        std::cout << " FAKTOR_1 => , IZRAZ ) " << std::endl;
        preduvid = yylex();
        IZRAZ();
        if (preduvid != ')') {
            greska("[FAKTOR_1]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[FAKTOR_1]: Ocekujem ) ili ,");
    }
}

void FAKTOR_2() {
    if (preduvid == '*' || preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
        std::cout << " FAKTOR_2 => eps " << std::endl;
    } else if (preduvid == '.') {
        std::cout << " FAKTOR_2 => . sum ( ) " << std::endl;
        preduvid = yylex();
        if (preduvid != sum_token) {
            greska("[FAKTOR_2]: Ocekujem sum");
        } else {
            preduvid = yylex();
        }
        if (preduvid != '(') {
            greska("[FAKTOR_2]: Ocekujem (");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ')') {
            greska("[FAKTOR_2]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == '[') {
        std::cout << " FAKTOR_2 => [ broj ] " << std::endl;
        preduvid = yylex();
        if (preduvid != broj_token) {
            greska("[FAKTOR_2]: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ']') {
            greska("[FAKTOR_2]: Ocekujem ]");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[FAKTOR_2]: Ocekujem *, +, -, ;, ), ., [ ili ,");
    }
}

void LISTA_SIFRI() {
    if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
        std::cout << " LISTA_SIFRI => IZRAZ LISTA_SIFRI' " << std::endl;
        IZRAZ();
        LISTA_SIFRI_P();
    } else {
        greska("[LISTA_SIFRI]: Ocekujem (, id, -, [ ili broj");
    }
}

void LISTA_SIFRI_P() {
    if (preduvid == ',') {
        std::cout << " LISTA_SIFRI' => , IZRAZ LISTA_SIFRI' " << std::endl;
        preduvid = yylex();
        IZRAZ();
        LISTA_SIFRI_P();
    } else if (preduvid == ']') {
        std::cout << " LISTA_SIFRI' => eps " << std::endl;
    } else {
        greska("[LISTA_SIFRI']: Ocekujem , ili ]");
    }
}
