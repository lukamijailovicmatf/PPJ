#ifndef FORMULA_HPP
#define FORMULA_HPP

#include <iostream>
#include <string>

//  1 -> True
//  0 -> False
// -1 -> Undef

class Formula {
protected:
    int _val;

public:
    Formula(int v);
    int getValue() const;
    std::string ispisi() const;

    int negacija() const;
    int konjukcija(const Formula& f1, const Formula& f2);
    int disjunkcija(const Formula& f1, const Formula& f2);
    int implikacija(const Formula& f1, const Formula& f2);
    int ekvivalencija(const Formula& f1, const Formula& f2);
};

#endif