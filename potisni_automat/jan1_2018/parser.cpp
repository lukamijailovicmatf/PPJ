#include <iostream>
#include <stack>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

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

    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == id_token || preduvid == print_token) {
                    std::cout << "NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI'" << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI]: Ocekujem id ili print");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == id_token || preduvid == print_token) {
                    std::cout << "NIZ_NAREDBI' => NIZ_NAREDBI" << std::endl;
                    stek.push(NIZ_NAREDBI);
                } else if (preduvid == eoi) {
                    std::cout << "NIZ_NAREDBI' => eps" << std::endl;
                } else {
                    greska("[NIZ_NAREDBI']: Ocekujem id, print ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == id_token) {
                    std::cout << "NAREDBA => id dodela IZRAZ" << std::endl;
                    stek.push(IZRAZ);
                    stek.push(dodela_token);
                    stek.push(id_token);
                } else if (preduvid == print_token) {
                    std::cout << "NAREDBA => print ( IZRAZ )" << std::endl;
                    stek.push(')');
                    stek.push(IZRAZ);
                    stek.push('(');
                    stek.push(print_token);
                } else {
                    greska("[NAREDBA]: Ocekujem id ili print");
                }
                break;
            case IZRAZ:
                if (preduvid == '<' || preduvid == id_token || preduvid == broj_token) {
                    std::cout << "IZRAZ => T IZRAZ'" << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(T);
                } else {
                    greska("[IZRAZ]: Ocekujem <, id ili print");
                }
                break;
            case IZRAZ_P:
                if (preduvid == '+') {
                    std::cout << "IZRAZ' => + T IZRAZ'" << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == '-') {
                    std::cout << "IZRAZ' => - T IZRAZ'" << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(T);
                    stek.push('-');
                } else if (preduvid == ';' || preduvid == ')') {
                    std::cout << "IZRAZ' => eps" << std::endl;
                } else {
                    greska("[IZRAZ']: Ocekujem +, -, ; ili )");
                }
                break;
            case T:
                if (preduvid == '<' || preduvid == id_token || preduvid == broj_token) {
                    std::cout << "T => F T'" << std::endl;
                    stek.push(TP);
                    stek.push(F);
                } else {
                    greska("[T]: Ocekujem <, id ili broj");
                }
                break;
            case TP:
                if (preduvid == '*') {
                    std::cout << "T' => * F T'" << std::endl;
                    stek.push(TP);
                    stek.push(F);
                    stek.push('*');
                } else if (preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')') {
                    std::cout << "T' => eps" << std::endl;
                } else {
                    greska("[T']: Ocekujem *, +, -, ; ili )");
                }
                break;
            case F:
                if (preduvid == '<') {
                    std::cout << "F => < NIZ_BROJEVA >" << std::endl;
                    stek.push('>');
                    stek.push(NIZ_BROJEVA);
                    stek.push('<');
                } else if (preduvid == id_token) {
                    std::cout << "F => id" << std::endl;
                    stek.push(id_token);
                } else if (preduvid == broj_token) {
                    std::cout << "F => broj" << std::endl;
                    stek.push(broj_token);
                } else {
                    greska("[F]: Ocekujem <, id ili broj");
                }
                break;
            case NIZ_BROJEVA:
                if (preduvid == broj_token || preduvid == '-') {
                    std::cout << "NIZ_BROJEVA => KONST NIZ_BROJEVA'" << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(KONST);
                } else {
                    greska("[NIZ_BROJEVA]: Ocekujem broj ili -");
                }
                break;
            case NIZ_BROJEVA_P:
                if (preduvid == ',') {
                    std::cout << "NIZ_BROJEVA' => , KONST NIZ_BROJEVA'" << std::endl;
                    stek.push(NIZ_BROJEVA_P);
                    stek.push(KONST);
                    stek.push(',');
                } else if (preduvid == '>') {
                    std::cout << "NIZ_BROJEVA' => eps" << std::endl;
                } else {
                    greska("[NIZ_BROJEVA']: Ocekujem , ili >");
                }
                break;
            case KONST:
                if (preduvid == broj_token) {
                    std::cout << "KONST => broj" << std::endl;
                    stek.push(broj_token);
                } else if (preduvid == '-') {
                    std::cout << "KONST => - broj" << std::endl;
                    stek.push(broj_token);
                    stek.push('-');
                } else {
                    greska("[KONST]: Ocekujem broj ili -");
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