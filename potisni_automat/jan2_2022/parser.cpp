#include <iostream>
#include <stack>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

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

    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == razlomak_token || preduvid == stampaj_token) {
                    std::cout << " NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI' " << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI]: Ocekujem razlomak ili stampaj");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == razlomak_token || preduvid == stampaj_token) {
                    std::cout << " NIZ_NAREDBI' => NIZ_NAREDBI " << std::endl;
                    stek.push(NIZ_NAREDBI);
                } else if (preduvid == eoi) {
                    std::cout << " NIZ_NAREDBI' => eps " << std::endl;
                } else {
                    greska("[NIZ_NAREDBI']: Ocekujem razlomak, stampaj ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == razlomak_token) {
                    std::cout << " NAREDBA => razlomak id NAREDBA_1 " << std::endl;
                    stek.push(NAREDBA_1);
                    stek.push(id_token);
                    stek.push(razlomak_token);
                } else if (preduvid == stampaj_token) {
                    std::cout << " NAREDBA => stampaj id NAREDBA_2 " << std::endl;
                    stek.push(NAREDBA_2);
                    stek.push(id_token);
                    stek.push(stampaj_token);
                } else {
                    greska("[NAREDBA]: Ocekujem razlomak ili stampaj");
                }
                break;
            case NAREDBA_1:
                if (preduvid == '=') {
                    std::cout << " NAREDBA_1 => = [ broj , broj ] " << std::endl;
                    stek.push(']');
                    stek.push(broj_token);
                    stek.push(',');
                    stek.push(broj_token);
                    stek.push('[');
                    stek.push('=');
                } else if (preduvid == ';') {
                    std::cout << " NAREDBA_1 => eps " << std::endl;
                } else {
                    greska("[NAREDBA_1]: Ocekujem = ili ;");
                }
                break;
            case NAREDBA_2:
                if (preduvid == id_token) {
                    std::cout << " NAREDBA_2 => id " << std::endl;
                    stek.push(id_token);
                } else if (preduvid == ';') {
                    std::cout << " NAREDBA_2 => eps " << std::endl;
                } else {
                    greska("[NAREDBA_2]: Ocekujem id ili ;");
                }
                break;
            default:
                if (preduvid != element) {
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