#include "Formula.hpp"

Formula::Formula(int v)
    : _val(v) {}

int Formula::getValue() const {
    return _val;
}

std::string Formula::ispisi() const {
    if (_val == 1)
        return "True";
    if (_val == 0)
        return "False";
    return "Undef";
}

int Formula::negacija() const {
    if (_val == 0)
        return 1;
    if (_val == 1)
        return 0;
    return -1;
}

int Formula::konjukcija(const Formula& f1, const Formula& f2) {
    if (f1._val == 0 || f2._val == 0)
        return 0;
    if (f1._val == 1 && f2._val == 1)
        return 1;
    return -1;
}

int Formula::disjunkcija(const Formula& f1, const Formula& f2) {
    if (f1._val == 1 || f2._val == 1)
        return 1;
    if (f1._val == 0 || f2._val == 0)
        return 0;
    return -1;
}

int Formula::implikacija(const Formula& f1, const Formula& f2) {
    // f1 => f2 menjamo sa ~f1 || f2
    int vrednost = f1.negacija();
    Formula negiranoF1 = Formula(vrednost);
    return disjunkcija(negiranoF1, f2);
}

int Formula::ekvivalencija(const Formula& f1, const Formula& f2) {
    // f1 <=> f2 menjamo sa (a => b) && (b => a)
    Formula tmp1 = Formula(implikacija(f1, f2));
    Formula tmp2 = Formula(implikacija(f2, f1));
    return konjukcija(tmp1, tmp2);
}