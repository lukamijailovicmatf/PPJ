#ifndef SIFRA_HPP
#define SIFRA_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

class Sifra {

private:
    double m_generator;
    int m_generisanaSifra;

public:
    Sifra();
    Sifra(double generator, int generisanaSifra);
    Sifra(double generator);

    double fst() const;
    int snd() const;

    Sifra operator + (const Sifra& druga) const;
    Sifra operator - (const Sifra& druga) const;
    Sifra operator * (const Sifra& druga) const;
    Sifra operator / (const Sifra& druga) const;
    Sifra operator - () const;

    bool operator == (const Sifra& druga) const;
    bool operator != (const Sifra& druga) const;
    bool operator < (const Sifra& druga) const;
    bool operator <= (const Sifra& druga) const;
    bool operator > (const Sifra& druga) const;
    bool operator >= (const Sifra& druga) const;

    void stampaj() const;
    friend std::ostream& operator << (std::ostream& os, const Sifra& s);

};

class ListaSifri {

private:
    std::vector<Sifra> m_elementi;

public:
    ListaSifri();
    ListaSifri(const std::vector<Sifra>& elementi);

    void dodaj(const Sifra& s);
    Sifra sum() const;
    Sifra operator [] (int indeks) const;
    int size() const;
    
    void stampaj() const;
    friend std::ostream& operator << (std::ostream& os, const ListaSifri& l);

};

#endif