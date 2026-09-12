#ifndef RAZLOMAK_HPP
#define RAZLOMAK_HPP

#include <iostream>

class Razlomak {
protected:
    int _brojilac;
    int _imenilac;

public:
    Razlomak(int brojilac = 0, int imenilac = 1);

    int nzd(int a, int b);
    void skrati();

    // operatori da nam akcije u parseru budu proste: a + b, a * b ...
    Razlomak operator + (const Razlomak& r) const;
    Razlomak operator - (const Razlomak& r) const;
    Razlomak operator * (const Razlomak& r) const;
    Razlomak operator / (const Razlomak& r) const;
    Razlomak operator - () const;   // unarni minus
    Razlomak reciprocan() const;
    Razlomak stepen(int exp) const;
    
    // poredjenja
    bool operator < (const Razlomak& r) const;
    bool operator > (const Razlomak& r) const;
    bool operator <= (const Razlomak& r) const;
    bool operator >= (const Razlomak& r) const;
    bool operator == (const Razlomak& r) const;
    bool operator != (const Razlomak& r) const;

    void stampaj() const;
    
};

#endif