#include "Kompleksni.hpp"
#include <cstdlib>
#include <cmath>

Kompleksni::Kompleksni(double r, double i)
    : _re(r), _im(i) {}

Kompleksni Kompleksni::operator + (const Kompleksni& drugi) const {
    return Kompleksni(_re + drugi._re, _im + drugi._im);
}

Kompleksni Kompleksni::operator - (const Kompleksni& drugi) const {
    return Kompleksni(_re - drugi._re, _im - drugi._im);
}

Kompleksni Kompleksni::operator - () const {
    return Kompleksni(-_re, -_im);
}

Kompleksni Kompleksni::operator * (const Kompleksni& drugi) const {
    double novi_re = _re * drugi._re - _im * drugi._im;
    double novi_im = _re * drugi._im + _im * drugi._re;
    return Kompleksni(novi_re, novi_im);
}

Kompleksni Kompleksni::operator / (const Kompleksni& drugi) const {
    double imenilac = drugi._re * drugi._re + drugi._im * drugi._im;
    if (std::abs(imenilac) < 1e-12) {
        std::cerr << "Nema deljenja nulom!" << std::endl;
        exit(EXIT_FAILURE);
    }
    double novi_re = (_re * drugi._re + _im * drugi._im) / imenilac;
    double novi_im = (_im * drugi._re - _re * drugi._im) / imenilac;
    return Kompleksni(novi_re, novi_im);
}

Kompleksni Kompleksni::operator ~ () const {
    return Kompleksni(_re, -_im);
}

bool Kompleksni::operator == (const Kompleksni& drugi) const {
    return std::abs(_re - drugi._re) < 1e-7 && std::abs(_im - drugi._im) < 1e-7;
}

bool Kompleksni::operator != (const Kompleksni& drugi) const {
    return !(*this == drugi);
}

double Kompleksni::moduo() const {
    return std::sqrt(_re * _re + _im * _im);
}

double Kompleksni::argument() const {
    return std::atan2(_im, _re);
}

void Kompleksni::ispisi() const {
    if (std::abs(_im) < 1e-7) {
        std::cout << _re << std::endl;
    } else {
        std::cout << _re << (_im > 0 ? "+" : "") << _im << "i" << std::endl; 
    }
}
