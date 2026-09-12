#include "Razlomak.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

Razlomak::Razlomak(int brojilac, int imenilac)
    : _brojilac(brojilac), _imenilac(imenilac) {
        if (_imenilac == 0)
            throw std::runtime_error("Imenilac ne sme biti nula!");
        skrati();
    }

int Razlomak::nzd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

void Razlomak::skrati() {
    int f = nzd(_brojilac, _imenilac);
    _brojilac = _brojilac / f;
    _imenilac = _imenilac / f;
    if (_imenilac < 0) {
        _brojilac = - _brojilac;
        _imenilac = - _imenilac;
    }
}

// [a b] + [c d] = [a*d + b*c, b*d]
//      a          b              c          d
// [_brojilac _imenilac] + [r._brojilac r._imenilac]
Razlomak Razlomak::operator + (const Razlomak& r) const {
    return Razlomak(_brojilac * r._imenilac + _imenilac * r._brojilac, _imenilac * r._imenilac);
}

// [a b] - [c d] = [a*d - b*c, b*d]
//      a          b              c          d
// [_brojilac _imenilac] - [r._brojilac r._imenilac]
Razlomak Razlomak::operator - (const Razlomak& r) const {
    return Razlomak(_brojilac * r._imenilac - _imenilac * r._brojilac, _imenilac * r._imenilac);
}

// [a b] * [c d] = [a*c, b*d]
//      a          b              c          d
// [_brojilac _imenilac] * [r._brojilac r._imenilac]
Razlomak Razlomak::operator * (const Razlomak& r) const {
    return Razlomak(_brojilac * r._brojilac, _imenilac * r._imenilac);
}

// [a b] / [c d] = [a*d, b*c] --> pravilo dvojnog razlomka!
//      a          b              c          d
// [_brojilac _imenilac] / [r._brojilac r._imenilac]
Razlomak Razlomak::operator / (const Razlomak& r) const {
    if (r._brojilac == 0)
        throw std::runtime_error("Nema deljenja nulom!");
    return Razlomak(_brojilac * r._imenilac, _imenilac * r._brojilac);
}

Razlomak Razlomak::operator - () const {
    return Razlomak(-_brojilac, _imenilac);
}

Razlomak Razlomak::reciprocan() const {
    if (_brojilac == 0)
        throw std::runtime_error("Nula nema reciprocnu vrednost!");
    return Razlomak(_imenilac, _brojilac);
}

// x^-2 = (1/x)^2
Razlomak Razlomak::stepen(int exp) const {
    if (exp == 0)
        return Razlomak(1, 1);
    if (exp < 0)
        return this->reciprocan().stepen(-exp);
    return Razlomak((int)std::pow(_brojilac, exp), (int)std::pow(_imenilac, exp));
}

/* *************************************************** */

// koristimo unakrsno mnozenje kod relacije poredjenja
// [a b] < [c d] => a*d < b*c
// [_brojilac _imenilac] < [r._brojilac r._imenilac]

// _brojilac * r._imenilac < _imenilac * r._brojilac
//                         <=
//                         >
//                         ...

/* *************************************************** */

bool Razlomak::operator < (const Razlomak& r) const {
    return _brojilac * r._imenilac < _imenilac * r._brojilac;
}

bool Razlomak::operator > (const Razlomak& r) const {
    return _brojilac * r._imenilac > _imenilac * r._brojilac;
}

bool Razlomak::operator <= (const Razlomak& r) const {
    return _brojilac * r._imenilac <= _imenilac * r._brojilac;
}

bool Razlomak::operator >= (const Razlomak& r) const {
    return _brojilac * r._imenilac >= _imenilac * r._brojilac;
}

bool Razlomak::operator == (const Razlomak& r) const {
    return _brojilac == r._brojilac && _imenilac == r._imenilac;
}

bool Razlomak::operator != (const Razlomak& r) const {
    return !(*this == r);
}

void Razlomak::stampaj() const {
    std::cout << "[" << _brojilac << ", " << _imenilac << "]" << std::endl;
}