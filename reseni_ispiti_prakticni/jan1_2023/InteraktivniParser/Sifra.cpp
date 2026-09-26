#include "Sifra.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

Sifra::Sifra() {
    m_generator = 0.0;
    m_generisanaSifra = 0;
}

Sifra::Sifra(double generator, int generisanaSifra) {
    m_generator = generator;
    m_generisanaSifra = generisanaSifra;
}

Sifra::Sifra(double generator) {
    m_generator = generator;
    m_generisanaSifra = static_cast<int>(std::round(generator * 1000.0));
}

double Sifra::fst() const {
    return m_generator;
}

int Sifra::snd() const {
    return m_generisanaSifra;
}

Sifra Sifra::operator + (const Sifra& druga) const {
    double novi_generator = m_generator + druga.m_generator;
    return Sifra(novi_generator);
}

Sifra Sifra::operator - (const Sifra& druga) const {
    double novi_generator = m_generator - druga.m_generator;
    return Sifra(novi_generator);
}

Sifra Sifra::operator * (const Sifra& druga) const {
    double novi_generator = m_generator * druga.m_generator;
    return Sifra(novi_generator);
}

Sifra Sifra::operator / (const Sifra& druga) const {
    if (druga.m_generator == 0.0) {
        std::cerr << "Greska: deljenje nulom" << std::endl;
        return Sifra(0.0, 0);
    }
    double novi_generator = m_generator / druga.m_generator;
    return Sifra(novi_generator);
}

Sifra Sifra::operator - () const {
    return Sifra(-m_generator);
}

bool Sifra::operator == (const Sifra& druga) const {
    return m_generisanaSifra == druga.m_generisanaSifra;
}

bool Sifra::operator != (const Sifra& druga) const {
    return !(*this == druga);
}

bool Sifra::operator < (const Sifra& druga) const {
    return m_generisanaSifra < druga.m_generisanaSifra;
}

bool Sifra::operator <= (const Sifra& druga) const {
    return m_generisanaSifra <= druga.m_generisanaSifra;
}

bool Sifra::operator > (const Sifra& druga) const {
    return m_generisanaSifra > druga.m_generisanaSifra;
}

bool Sifra::operator >= (const Sifra& druga) const {
    return m_generisanaSifra >= druga.m_generisanaSifra;
}

void Sifra::stampaj() const {
    std::cout << "(" << m_generator << ", " << m_generisanaSifra << ")" << std::endl;
}

std::ostream& operator << (std::ostream& os, const Sifra& s) {
    os << "(" << s.m_generator << ", " << s.m_generisanaSifra << ")";
    return os;
}



ListaSifri::ListaSifri() {}

ListaSifri::ListaSifri(const std::vector<Sifra>& elementi) {
    m_elementi = elementi;
}

void ListaSifri::dodaj(const Sifra& s) {
    m_elementi.push_back(s);
}

Sifra ListaSifri::sum() const {
    Sifra suma(0.0, 0);
    for (const auto& s : m_elementi) {
        suma = suma + s;
    }
    return suma;
}

Sifra ListaSifri::operator [] (int indeks) const {
    if (indeks < 0 || indeks >= static_cast<int>(m_elementi.size())) {
        std::cerr << "Greska: indeks van opsega" << std::endl;
        return Sifra(0.0, 0);
    }
    return m_elementi[indeks];
}

int ListaSifri::size() const {
    return static_cast<int>(m_elementi.size());
}

void ListaSifri::stampaj() const {
    std::cout << "[";
    for (size_t i = 0; i < m_elementi.size(); i++) {
        std::cout << m_elementi[i];
        if (i + 1 < m_elementi.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

std::ostream& operator << (std::ostream& os, const ListaSifri& l) {
    os << "[";
    for (size_t i = 0; i < l.m_elementi.size(); i++) {
        os << l.m_elementi[i];
        if (i + 1 < l.m_elementi.size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}