#include <iostream>
#include <stack>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void greska(std::string poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

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
//        | eps                             { +, -, ;, ), ], , }
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
// FAKTOR_2 -> eps                          { *, +, -, ;, ), ], , }
//           | . sum ( )                    { . }
//           | [ broj ]                     { [ }
//
// LISTA_SIFRI -> IZRAZ LISTA_SIFRI'        { (, id, -, [, broj}
//
// LISTA_SIFRI' -> , IZRAZ LISTA_SIFRI'     { , }
//               | eps                      { ] }

int main() {

    preduvid = yylex();

    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch (element) {
            case NIZ_NAREDBI:
                if (preduvid == sifra_token || preduvid == stampaj_token || preduvid == lista_sifri_token) {
                    std::cout << " NIZ_NAREDBI => NAREDBA NIZ_NAREDBI' " << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI]: Ocekujem sifra, stampaj ili lista_sifri");
                }
                break;
            case NIZ_NAREDBI_P:
                if (preduvid == sifra_token || preduvid == stampaj_token || preduvid == lista_sifri_token) {
                    std::cout << " NIZ_NAREDBI' => NAREDBA NIZ_NAREDBI' " << std::endl;
                    stek.push(NIZ_NAREDBI_P);
                    stek.push(NAREDBA);
                } else if (preduvid == eoi) {
                    std::cout << " NIZ_NAREDBI => eps " << std::endl;
                } else {
                    greska("[NIZ_NAREDBI']: Ocekujem sifra, stampaj, lista_sifri ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == sifra_token) {
                    std::cout << " NAREDBA => sifra id NAREDBA' " << std::endl;
                    stek.push(NAREDBA_P);
                    stek.push(id_token);
                    stek.push(sifra_token);
                } else if (preduvid == stampaj_token) {
                    std::cout << " NAREDBA => stampaj IZRAZ ; " << std::endl;
                    stek.push(';');
                    stek.push(IZRAZ);
                    stek.push(stampaj_token);
                } else if (preduvid == lista_sifri_token) {
                    std::cout << " NAREDBA => lista_sifri id = IZRAZ ; " << std::endl;
                    stek.push(';');
                    stek.push(IZRAZ);
                    stek.push('=');
                    stek.push(id_token);
                    stek.push(lista_sifri_token);
                } else {
                    greska("[NAREDBA]: Ocekujem sifra, stampaj ili lista_sifri");
                }
                break;
            case NAREDBA_P:
                if (preduvid == ';') {
                    std::cout << " NAREDBA' => ; " << std::endl;
                    stek.push(';');
                } else if (preduvid == '(') {
                    std::cout << " NAREDBA' => ( broj , broj ) ; " << std::endl;
                    stek.push(';');
                    stek.push(')');
                    stek.push(broj_token);
                    stek.push(',');
                    stek.push(broj_token);
                    stek.push('(');
                } else if (preduvid == '=') {
                    std::cout << " NAREDBA' => = IZRAZ ; " << std::endl;
                    stek.push(';');
                    stek.push(IZRAZ);
                    stek.push('=');
                } else {
                    greska("[NAREDBA']: Ocekujem ;, ( ili =");
                }
                break;
            case IZRAZ:
                if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
                    std::cout << " IZRAZ => TERM IZRAZ' " << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(TERM);
                } else {
                    greska("[IZRAZ]: Ocekujem (, id, -, [ ili broj");
                }
                break;
            case IZRAZ_P:
                if (preduvid == '+') {
                    std::cout << " IZRAZ' => + TERM IZRAZ' " << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(TERM);
                    stek.push('+');
                } else if (preduvid == '-') {
                    std::cout << " IZRAZ' => - TERM IZRAZ' " << std::endl;
                    stek.push(IZRAZ_P);
                    stek.push(TERM);
                    stek.push('-');
                } else if (preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
                    std::cout << " IZRAZ' => eps " << std::endl;
                } else {
                    greska("[IZRAZ']: Ocekujem +, -, ;, ), ] ili ,");
                }
                break;
            case TERM:
                if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
                    std::cout << " TERM => FAKTOR TERM' " << std::endl;
                    stek.push(TERM_P);
                    stek.push(FAKTOR);
                } else {
                    greska("[TERM]: Ocekujem (, id, -, [ ili broj");
                }
                break;
            case TERM_P:
                if (preduvid == '*') {
                    std::cout << " TERM' => * FAKTOR TERM' " << std::endl;
                    stek.push(TERM_P);
                    stek.push(FAKTOR);
                    stek.push('*');
                } else if (preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
                    std::cout << " TERM' => eps " << std::endl;
                } else {
                    greska("[TERM']: Ocekujem *, +, -, ;, ), ] ili ,");
                }
                break;
            case FAKTOR:
                if (preduvid == '(') {
                    std::cout << " FAKTOR => ( IZRAZ FAKTOR_1 " << std::endl;
                    stek.push(FAKTOR_1);
                    stek.push(IZRAZ);
                    stek.push('(');
                } else if (preduvid == id_token) {
                    std::cout << " FAKTOR => id FAKTOR_2 " << std::endl;
                    stek.push(FAKTOR_2);
                    stek.push(id_token);
                } else if (preduvid == '-') {
                    std::cout << " FAKTOR => - FAKTOR " << std::endl;
                    stek.push(FAKTOR);
                    stek.push('-');
                } else if (preduvid == '[') {
                    std::cout << " FAKTOR => [ LISTA_SIFRI ] " << std::endl;
                    stek.push(']');
                    stek.push(LISTA_SIFRI);
                    stek.push('[');
                } else if (preduvid == broj_token) {
                    std::cout << " FAKTOR => broj " << std::endl;
                    stek.push(broj_token);
                } else {
                    greska("[FAKTOR]: Ocekujem (, id, -, [ ili broj");
                }
                break;
            case FAKTOR_1:
                if (preduvid == ')') {
                    std::cout << " FAKTOR_1 => ) " << std::endl;
                    stek.push(')');
                } else if (preduvid == ',') {
                    std::cout << " FAKTOR_1 => , IZRAZ ) " << std::endl;
                    stek.push(')');
                    stek.push(IZRAZ);
                    stek.push(',');
                } else {
                    greska("[FAKTOR_1]: Ocekujem ) ili ,");
                }
                break;
            case FAKTOR_2:
                if (preduvid == '*' || preduvid == '+' || preduvid == '-' || preduvid == ';' || preduvid == ')' || preduvid == ',' || preduvid == ']') {
                    std::cout << " FAKTOR_2 => eps " << std::endl;
                } else if (preduvid == '.') {
                    std::cout << " FAKTOR_2 => . sum ( ) " << std::endl;
                    stek.push(')');
                    stek.push('(');
                    stek.push(sum_token);
                    stek.push('.');
                } else if (preduvid == '[') {
                    std::cout << " FAKTOR_2 => [ broj ] " << std::endl;
                    stek.push(']');
                    stek.push(broj_token);
                    stek.push('[');
                } else {
                    greska("[FAKTOR_2]: Ocekujem *, +, -, ;, ), ], ., [ ili ,");
                }
                break;
            case LISTA_SIFRI:
                if (preduvid == '(' || preduvid == id_token || preduvid == '-' || preduvid == '[' || preduvid == broj_token) {
                    std::cout << " LISTA_SIFRI => IZRAZ LISTA_SIFRI' " << std::endl;
                    stek.push(LISTA_SIFRI_P);
                    stek.push(IZRAZ);
                } else {
                    greska("[LISTA_SIFRI]: Ocekujem (, id, -, [ ili broj");
                }
                break;
            case LISTA_SIFRI_P:
                if (preduvid == ',') {
                    std::cout << " LISTA_SIFRI' => , IZRAZ LISTA_SIFRI' " << std::endl;
                    stek.push(LISTA_SIFRI_P);
                    stek.push(IZRAZ);
                    stek.push(',');
                } else if (preduvid == ']') {
                    std::cout << " LISTA_SIFRI' => eps " << std::endl;
                } else {
                    greska("[LISTA_SIFRI']: Ocekujem , ili ]");
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