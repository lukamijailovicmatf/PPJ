#include <iostream>
#include <stack>
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

int main() {

    preduvid = yylex();

    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == list_token || preduvid == id_token) {
                    std::cout << " NIZ_NAREDBI => NAREDBA NIZ_NAREDBI' " << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI]: Ocekujem list ili id");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == list_token || preduvid == id_token) {
                    std::cout << " NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI' " << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else if (preduvid == eoi) {
                    std::cout << " NIZ_NAREDBI' => eps " << std::endl;
                } else {
                    greska("[NIZ_NAREDBI']: Ocekujem list, id ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == list_token) {
                    std::cout << " list < NAREDBA_1 " << std::endl;
                    stek.push(NAREDBA_1);
                    stek.push('<');
                    stek.push(list_token);
                } else if (preduvid == id_token) {
                    std::cout << " id NAREDBA_2 " << std::endl;
                    stek.push(NAREDBA_2);
                    stek.push(id_token);
                } else {
                    greska("[NAREDBA]: Ocekujem list ili id");
                }
                break;
            case NAREDBA_1:
                if (preduvid == number_tip_token) {
                    std::cout << " number > id NAREDBA_3 " << std::endl;
                    stek.push(NAREDBA_3);
                    stek.push(id_token);
                    stek.push('>');
                    stek.push(number_tip_token);
                } else if (preduvid == string_tip_token) {
                    std::cout << " string > id = { NIZ_STRINGOVA } ; " << std::endl;
                    stek.push(';');
                    stek.push('}');
                    stek.push(NIZ_STRINGOVA);
                    stek.push('{');
                    stek.push('=');
                    stek.push(id_token);
                    stek.push('>');
                    stek.push(string_tip_token);
                } else {
                    greska("[NAREDBA_1]: Ocekujem number ili string");
                }
                break;
            case NAREDBA_2:
                if (preduvid == '=') {
                    std::cout << " NAREDBA_2 => = id ; " << std::endl;
                    stek.push(';');
                    stek.push(id_token);
                    stek.push('=');
                } else if (preduvid == '.') {
                    std::cout << " NAREDBA_2 => . NAREDBA_4 " << std::endl;
                    stek.push(NAREDBA_4);
                    stek.push('.');
                } else {
                    greska("[NAREDBA_2]: Ocekujem = ili .");
                }
                break;
            case NAREDBA_3:
                if (preduvid == ';') {
                    std::cout << " NAREDBA_3 => ; " << std::endl;
                    stek.push(';');
                } else if (preduvid == '=') {
                    std::cout << " NAREDBA_3 => = { NIZ_BROJEVA } ; " << std::endl;
                    stek.push(';');
                    stek.push('}');
                    stek.push(NIZ_BROJEVA);
                    stek.push('{');
                    stek.push('=');
                } else {
                    greska("[NAREDBA_3]: Ocekujem ; ili =");
                }
                break;
            case NAREDBA_4:
                if (preduvid == print_token) {
                    std::cout << " NAREDBA_4 => print ( ) ; " << std::endl;
                    stek.push(';');
                    stek.push(')');
                    stek.push('(');
                    stek.push(print_token);
                } else if (preduvid == print_r_token) {
                    std::cout << " NAREDBA_4 => print_r ( ) ; " << std::endl;
                    stek.push(';');
                    stek.push(')');
                    stek.push('(');
                    stek.push(print_r_token);
                } else {
                    greska("[NAREDBA_4]: Ocekujem print ili print_r");
                }
                break;
            case NIZ_BROJEVA:
                if (preduvid == broj_token) {
                    std::cout << " NIZ_BROJEVA => broj NIZ_BROJEVA' " << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(broj_token);
                } else {
                    greska("[NIZ_BROJEVA]: Ocekujem broj");
                }
                break;
            case NIZ_BROJEVA_P:
                if (preduvid == ',') {
                    std::cout << " NIZ_BROJEVA' => , broj NIZ_BROJEVA' " << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(broj_token);
                    stek.push(',');
                } else if (preduvid == '}') {
                    std::cout << " NIZ_BROJEVA' => eps " << std::endl;
                } else {
                    greska("[NIZ_BROJEVA']: Ocekujem , ili }");
                }
                break;
            case NIZ_STRINGOVA:
                if (preduvid == niska_token) {
                    std::cout << " niska NIZ_STRINGOVA' " << std::endl;
                    stek.push(NIZ_STRINGOVA_P);
                    stek.push(niska_token);
                } else {
                    greska("[NIZ_STRINGOVA]: Ocekujem nisku");
                }
                break;
            case NIZ_STRINGOVA_P:
                if (preduvid == ',') {
                    std::cout << " NIZ_STRINGOVA' => , niska NIZ_STRINGOVA' " << std::endl;
                    stek.push(NIZ_STRINGOVA_P);
                    stek.push(niska_token);
                    stek.push(',');
                } else if (preduvid == '}') {
                    std::cout << " NIZ_STRINGOVA' => eps " << std::endl;
                } else {
                    greska("[NIZ_STRINGOVA']: Ocekujem , ili }");
                }
                break;
            default:
                if (element != preduvid) {
                    greska("Nepoklapanje tokena sa ulaza i sa vrha steka");
                } else {
                    preduvid = yylex();
                }
        }
    }

    if (preduvid != eoi) {
        greska("Recenica se ne prihvata");
    } else {
        std::cout << "Recenica se prihvata" << std::endl;
    }

    return 0;
}