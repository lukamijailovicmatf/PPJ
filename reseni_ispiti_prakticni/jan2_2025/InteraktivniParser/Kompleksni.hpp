#ifndef KOMPLEKSNI_HPP
#define KOMPLEKSNI_HPP

#include <iostream>
#include <cmath>

class Kompleksni {

public:

    double _re;
    double _im;

    Kompleksni(double r = 0, double i = 0);

    Kompleksni operator + (const Kompleksni& drugi) const;
    Kompleksni operator - (const Kompleksni& drugi) const;
    Kompleksni operator - () const;
    Kompleksni operator * (const Kompleksni& drugi) const;
    Kompleksni operator / (const Kompleksni& drugi) const;
    Kompleksni operator ~ () const;

    bool operator == (const Kompleksni& drugi) const;
    bool operator != (const Kompleksni& drugi) const;

    double moduo() const;
    double argument() const;

    void ispisi() const;
};

#endif

