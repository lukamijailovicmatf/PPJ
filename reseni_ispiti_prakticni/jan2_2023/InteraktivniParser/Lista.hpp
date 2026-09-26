#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

enum TipPodataka {
    TIP_NUMBER,
    TIP_STRING
};

class Lista {

private:
    TipPodataka tip;
    std::vector<std::string> elementi;

public:
    Lista();
    Lista(TipPodataka t);
    Lista(const std::vector<std::string>& el);

    TipPodataka get_tip() const { return tip; }
    void set_tip(TipPodataka t) { tip = t; }

    // metode nad listom, vracaju REFERENCU radi ulancavanja
    Lista& push_back(const std::string& v);
    Lista& push_front(const std::string& v);
    Lista& push(const std::string& v, int index);
    Lista& pop_back();
    Lista& pop_front();
    Lista& pop(int index);
    Lista find(const std::string& v) const;
    Lista get(int index) const;

    void print() const;
    void print_r() const;

    // operatori
    Lista operator + (const Lista& druga) const;
    Lista operator - (const Lista& druga) const;
    Lista operator * (const Lista& druga) const;
    Lista operator - () const;

    // leksikografsko poredjenje
    std::string to_string_repr() const;
    bool operator == (const Lista& druga) const;
    bool operator != (const Lista& druga) const;
    bool operator < (const Lista& druga) const;
    bool operator <= (const Lista& druga) const;
    bool operator > (const Lista& druga) const;
    bool operator >= (const Lista& druga) const;

};

#endif
