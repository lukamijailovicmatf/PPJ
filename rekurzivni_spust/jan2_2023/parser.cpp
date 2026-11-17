#include <iostream>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

// NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI'                              { list, id }
//
// NIZ_NAREDBI' -> NAREDBA NIZ_NAREDBI'                             { list, id }
//               | eps                                              { -| }
//
// NAREDBA -> list < NAREDBA_1                                      { list }
//          | id NAREDBA_2                                          { id }
//
// NAREDBA_1 -> number > id NAREDBA_3                               { number }
//            | string > id = { NIZ_STRINGOVA } ;                   { string }
//
// NAREDBA_2 -> = id ;                                              { = }
//            | . NAREDBA_4                                         { . }
//
// NAREDBA_3 -> ;                                                   { ; }
//            | = { NIZ_BROJEVA } ;                                 { = }
//
// NAREDBA_4 -> print ( ) ;                                         { print }
//            | print_r () ;                                        { print_r }
//
// NIZ_BROJEVA -> broj NIZ_BROJEVA'                                 { broj }
//
// NIZ_BROJEVA' -> , broj NIZ_BROJEVA'                              { , }
//               | eps                                              { } }
//
// NIZ_STRINGOVA -> niska NIZ_STRINGOVA'                            { niska }
//
// NIZ_STRINGOVA' -> , niska NIZ_STRINGOVA'                         { , }
//                 | eps                                            { } }

void NIZ_NAREDBI();
void NIZ_NAREDBI_P();
void NAREDBA();
void NAREDBA_1();
void NAREDBA_2();
void NAREDBA_3();
void NAREDBA_4();
void NIZ_BROJEVA();
void NIZ_BROJEVA_P();
void NIZ_STRINGOVA();
void NIZ_STRINGOVA_P();

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
    if (preduvid == list_token || preduvid == id_token) {
        std::cout << " NIZ_NAREDBI => NAREDBA NIZ_NAREDBI' " << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI]: Ocekujem list ili id");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == list_token || preduvid == id_token) {
        std::cout << " NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI' " << std::endl;
        NAREDBA();
        NIZ_NAREDBI_P();
    } else if (preduvid == eoi) {
        std::cout << " NIZ_NAREDBI' => eps " << std::endl;
    } else {
        greska("[NIZ_NAREDBI']: Ocekujem list, id ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == list_token) {
        std::cout << " NAREDBA => list < NAREDBA_1 " << std::endl;
        preduvid = yylex();
        if (preduvid != '<') {
            greska("[NAREDBA]: Ocekujem <");
        } else {
            preduvid = yylex();
        }
        NAREDBA_1();
    } else if (preduvid == id_token) {
        std::cout << " NAREDBA => id NAREDBA_2 " << std::endl;
        preduvid = yylex();
        NAREDBA_2();
    } else {
        greska("[NAREDBA]: Ocekujem list ili id");
    }
}

void NAREDBA_1() {
    if (preduvid == number_tip_token) {
        std::cout << " NAREDBA_1 => number > id NAREDBA_3 " << std::endl;
        preduvid = yylex();
        if (preduvid != '>') {
            greska("[NAREDBA_1]: Ocekujem >");
        } else {
            preduvid = yylex();
        }
        if (preduvid != id_token) {
            greska("[NAREDBA_1]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        NAREDBA_3();
    } else if (preduvid == string_tip_token) {
        std::cout << " NAREDBA_1 => string > id = { NIZ_STRINGOVA } ; " << std::endl;
        preduvid = yylex();
        if (preduvid != '>') {
            greska("[NAREDBA_1]: Ocekujem >");
        } else {
            preduvid = yylex();
        }
        if (preduvid != id_token) {
            greska("[NAREDBA_1]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        if (preduvid != '=') {
            greska("[NAREDBA_1]: Ocekujem =");
        } else {
            preduvid = yylex();
        }
        if (preduvid != '{') {
            greska("[NAREDBA_1]: Ocekujem {");
        } else {
            preduvid = yylex();
        }
        NIZ_STRINGOVA();
        if (preduvid != '}') {
            greska("[NAREDBA_1]: Ocekujem }");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA_1]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA_1]: Ocekujem number ili string");
    }
}

void NAREDBA_2() {
    if (preduvid == '=') {
        std::cout << " NAREDBA_2 => = id ; " << std::endl;
        preduvid = yylex();
        if (preduvid != id_token) {
            greska("[NAREDBA_2]: Ocekujem id");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA_2]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == '.') {
        std::cout << " NAREDBA_2 => . NAREDBA_4 " << std::endl;
        preduvid = yylex();
        NAREDBA_4();
    } else {
        greska("[NAREDBA_2]: Ocekujem = ili .");
    }
}

void NAREDBA_3() {
    if (preduvid == ';') {
        std::cout << " NAREDBA_3 => ; " << std::endl;
        preduvid = yylex();
    } else if (preduvid == '=') {
        std::cout << " NAREDBA_3 => = { NIZ_BROJEVA } ; " << std::endl;
        preduvid = yylex();
        if (preduvid != '{') {
            greska("[NAREDBA_3]: Ocekujem {");
        } else {
            preduvid = yylex();
        }
        NIZ_BROJEVA();
        if (preduvid != '}') {
            greska("[NAREDBA_3]: Ocekujem }");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA_3]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA_3]: Ocekujem ; ili =");
    }
}

void NAREDBA_4() {
    if (preduvid == print_token) {
        std::cout << " NAREDBA_4 => print ( ) ; " << std::endl;
        preduvid = yylex();
        if (preduvid != '(') {
            greska("[NAREDBA_4]: Ocekujem (");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ')') {
            greska("[NAREDBA_4]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA_4]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else if (preduvid == print_r_token) {
        std::cout << " NAREDBA_4 => print_r ( ) ; " << std::endl;
        preduvid = yylex();
        if (preduvid != '(') {
            greska("[NAREDBA_4]: Ocekujem (");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ')') {
            greska("[NAREDBA_4]: Ocekujem )");
        } else {
            preduvid = yylex();
        }
        if (preduvid != ';') {
            greska("[NAREDBA_4]: Ocekujem ;");
        } else {
            preduvid = yylex();
        }
    } else {
        greska("[NAREDBA_4]: Ocekujem print ili print_r");
    }
}

void NIZ_BROJEVA() {
    if (preduvid == broj_token) {
        std::cout << " NIZ_BROJEVA => broj NIZ_BROJEVA' " << std::endl;
        preduvid = yylex();
        NIZ_BROJEVA_P();
    } else {
        greska("[NIZ_BROJEVA]: Ocekujem broj");
    }
}

void NIZ_BROJEVA_P() {
    if (preduvid == ',') {
        std::cout << "  NIZ_BROJEVA' => , broj NIZ_BROJEVA' " << std::endl;
        preduvid = yylex();
        if (preduvid != broj_token) {
            greska("[NIZ_BROJEVA']: Ocekujem broj");
        } else {
            preduvid = yylex();
        }
        NIZ_BROJEVA_P();
    } else if (preduvid == '}') {
        std::cout << " NIZ_BROJEVA' => eps " << std::endl;
    } else {
        greska("[NIZ_BROJEVA']: Ocekujem , ili }");
    }
}

void NIZ_STRINGOVA() {
    if (preduvid == niska_token) {
        std::cout << " NIZ_STRINGOVA => niska NIZ_STRINGOVA' " << std::endl;
        preduvid = yylex();
        NIZ_STRINGOVA_P();
    } else {
        greska("[NIZ_STRINGOVA]: Ocekujem nisku");
    }
}

void NIZ_STRINGOVA_P() {
    if (preduvid == ',') {
        std::cout << " NIZ_STRINGOVA' => , niska NIZ_STRINGOVA' " << std::endl;
        preduvid = yylex();
        if (preduvid != niska_token) {
            greska("[NIZ_STRINGOVA']: Ocekujem nisku");
        } else {
            preduvid = yylex();
        }
        NIZ_STRINGOVA_P();
    } else if (preduvid == '}') {
        std::cout << " NIZ_STRINGOVA' => eps " << std::endl;
    } else {
        greska("[NIZ_STRINGOVA']: Ocekujem , ili }");
    }
}