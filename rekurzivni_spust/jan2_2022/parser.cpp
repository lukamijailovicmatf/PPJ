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
void NAREDBA_1();
void NAREDBA_2();

// gramatika:                                       skupovi izbora:
//
// NIZ_NAREDBI -> NAREDBA ; NIZ_NAREDBI'            { razlomak, stampaj }
//
// NIZ_NAREDBI' -> NIZ_NAREDBI                      { razlomak, stampaj }
//               | eps                              { -| }
//
// NAREDBA -> razlomak id NAREDBA_1                 { razlomak }
//          | stampaj id NAREDBA_2                  { stampaj }
//
// NAREDBA_1 -> = [ broj , broj ]                   { = }
//            | eps                                 { ; }
//
// NAREDBA_2 -> id                                  { id }
//            | eps                                 { ; }

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
    if (preduvid == razlomak_token || preduvid == stampaj_token) {
        std::cout << " NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI' " << std::endl;
        NAREDBA();
        if (preduvid != ';') {
            greska("[NIZ_NAREDBI]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI]: Ocekujem razlomak ili stampaj");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == razlomak_token || preduvid == stampaj_token) {
        std::cout << " NIZ_NAREDBI' => NIZ_NAREDBI " << std::endl;
        NIZ_NAREDBI();
    } else if (preduvid == eoi) {
        std::cout << " NIZ_NAREDBI' => eps " << std::endl;
    } else {
        greska("[NIZ_NAREDBI']: Ocekujem razlomak, stampaj ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == razlomak_token) {
        std::cout << " NAREDBA => razlomak id NAREDBA_1 " << std::endl;
        preduvid = yylex();
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        NAREDBA_1();
    } else if (preduvid == stampaj_token) {
        std::cout << " NAREDBA => stampaj id NAREDBA_2 " << std::endl;
        preduvid = yylex();
        if (preduvid != id_token) {
            greska("[NAREDBA]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        NAREDBA_2();
    } else {
        greska("[NAREDBA]: Ocekujem razlomak ili stampaj");
    }
}

void NAREDBA_1() {
    if (preduvid == '=') {
        std::cout << " NAREDBA_1 => = [ broj , broj ] " << std::endl;
        preduvid = yylex();
        if (preduvid != '[') {
            greska("[NAREDBA_1]: Ocekujem [");
        } else {
            preduvid = yylex();
        }
        if (preduvid != broj_token) {
            greska("[NAREDBA_1]: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ',') {
            greska("[NAREDBA_1]: Ocekujem ,");
        } else {
            preduvid = yylex();
        }
        if (preduvid != broj_token) {
            greska("[NAREDBA_1]: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ']') {
            greska("[NAREDBA_1]: Ocekujem ]");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == ';') {
        std::cout << " NAREDBA_1 => eps " << std::endl;
    } else {
        greska("[NAREDBA_1]: Ocekujem = ili ;");
    }
}

void NAREDBA_2() {
    if (preduvid == id_token) {
        std::cout << " NAREDBA_2 => id " << std::endl;
        preduvid = yylex();
    } else if (preduvid == ';') {
        std::cout << " NAREDBA_2 => eps " << std::endl;
    } else {
        greska("[NAREDBA_2]: Ocekujem id ili ;");
    }
}