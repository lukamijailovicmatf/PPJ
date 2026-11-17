#include <iostream>
#include <stack>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

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

    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == stek_token || preduvid == id_token || preduvid == print_token) {
                    std::cout << "NIZ_NAREDBI => NAREDBA NIZ_NAREDBI'" << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI]: Ocekujem stack, id ili print_stack");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == stek_token || preduvid == id_token || preduvid == print_token) {
                    std::cout << "NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI'" << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else if (preduvid == eoi) {
                    std::cout << "NIZ_NAREDBI' => eps" << std::endl;
                } else {
                    greska("[NIZ_NAREDBI']: Ocekujem stack, id, print_stack ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == stek_token) {
                    std::cout << "NAREDBA => stack < int_token > id NAREDBA'" << std::endl;
                    stek.push(NAREDBA_P);
                    stek.push(id_token);
                    stek.push('>');
                    stek.push(int_token);
                    stek.push('<');
                    stek.push(stek_token);
                } else if (preduvid == id_token) {
                    std::cout << "NAREDBA => id dodela_token id ;" << std::endl;
                    stek.push(';');
                    stek.push(id_token);
                    stek.push(dodela_token);
                    stek.push(id_token);
                } else if (preduvid == print_token) {
                    std::cout << "NAREDBA => print_stack ( id ) ;" << std::endl;
                    stek.push(';');
                    stek.push(')');
                    stek.push(id_token);
                    stek.push('(');
                    stek.push(print_token);
                } else {
                    greska("[NAREDBA]: Ocekujem stack, id ili print_stack");
                }
                break;
            case NAREDBA_P:
                if (preduvid == ';') {
                    std::cout << "NAREDBA' => ;" << std::endl;
                    stek.push(';');
                } else if (preduvid == dodela_token) {
                    std::cout << "NAREDBA' => dodela_token NAREDBA''" << std::endl;
                    stek.push(NAREDBA_P_P);
                    stek.push(dodela_token);
                } else {
                    greska("[NAREDBA']: Ocekujem ; ili :=");
                }
                break;
            case NAREDBA_P_P:
                if (preduvid == '{') {
                    std::cout << "NAREDBA'' => { NIZ_BROJEVA } ;" << std::endl;
                    stek.push(';');
                    stek.push('}');
                    stek.push(NIZ_BROJEVA);
                    stek.push('{');
                } else if (preduvid == id_token) {
                    std::cout << "NAREDBA'' => id ;" << std::endl;
                    stek.push(';');
                    stek.push(id_token);
                } else {
                    greska("[NAREDBA'']: Ocekujem { ili id");
                }
                break;
            case NIZ_BROJEVA:
                if (preduvid == broj_token) {
                    std::cout << "NIZ_BROJEVA -> broj NIZ_BROJEVA'" << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(broj_token);
                } else {
                    greska("[NIZ_BROJEVA]: Ocekujem broj");
                }
                break;
            case NIZ_BROJEVA_P:
                if (preduvid == ',') {
                    std::cout << "NIZ_BROJEVA' -> , broj NIZ_BROJEVA'" << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(broj_token);
                    stek.push(',');
                } else if (preduvid == '}') {
                    std::cout << "NIZ_BROJEVA' => eps" << std::endl;
                } else {
                    greska("[NIZ_BROJEVA_P]: Ocekujem , ili }");
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