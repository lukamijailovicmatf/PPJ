#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include "Lista.hpp"

// podrazumevani konstruktor
Lista::Lista() {
    tip = TIP_NUMBER;
}

// konstruktor koji postavlja samo tip podataka
Lista::Lista(TipPodataka t) {
    tip = t;
}

// konstruktor koji inicijalizuje listu sa vec postojecim elementima
Lista::Lista(const std::vector<std::string>& el) {
    tip = TIP_NUMBER;
    elementi = el;
}

// metode nad listom (vracaju REFERENCU *this)
Lista& Lista::push_back(const std::string& v) {
    elementi.push_back(v);
    return *this;
}

Lista& Lista::push_front(const std::string& v) {
    elementi.insert(elementi.begin(), v);
    return *this;
}

Lista& Lista::push(const std::string& v, int index) {
    if (index >= 0 && index <= (int)elementi.size()) {
        elementi.insert(elementi.begin() + index, v);
    }
    return *this;
}

Lista& Lista::pop_back() {
    if (!elementi.empty()) {
        elementi.pop_back();
    }
    return *this;
}

Lista& Lista::pop_front() {
    if (!elementi.empty()) {
        elementi.erase(elementi.begin());
    }
    return *this;
}

Lista& Lista::pop(int index) {
    if (index >= 0 && index <= (int)elementi.size()) {
        elementi.erase(elementi.begin() + index);
    }
    return *this;
}

Lista Lista::find(const std::string& v) const {
    Lista rez(TIP_NUMBER);
    for (size_t i = 0; i < elementi.size(); i++) {
        if (elementi[i] == v) {
            rez.push_back(std::to_string(i));
            break;
        }
    }
    return rez;
}

Lista Lista::get(int index) const {
    Lista rez(tip);
    if (index >= 0 && index < (int)elementi.size()) {
        rez.push_back(elementi[index]);
    }
    return rez;
}

void Lista::print() const {
    std::cout << "[";
    for (size_t i = 0; i < elementi.size(); i++) {
        std::cout << elementi[i] << (i + 1 < elementi.size() ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

void Lista::print_r() const {
    std::cout << "[";
    for (int i = (int)elementi.size() - 1; i >= 0; i--) {
        std::cout << elementi[i] << (i > 0 ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

// operatori
Lista Lista::operator + (const Lista& druga) const {
    Lista rez = *this;
    rez.elementi.insert(rez.elementi.end(), druga.elementi.begin(), druga.elementi.end());
    return rez;
}

Lista Lista::operator - (const Lista& druga) const {
    Lista rez = *this;
    for (const auto& el : druga.elementi) {
        auto it = std::find(rez.elementi.begin(), rez.elementi.end(), el);
        if (it != rez.elementi.end()) {
            rez.elementi.erase(it);
        }
    }
    return rez;
}

Lista Lista::operator * (const Lista& druga) const {
    Lista rez(tip);
    for (size_t i = 0; i < elementi.size(); i++) {
        std::string trenutni = elementi[i];
        auto it = std::find(druga.elementi.begin(), druga.elementi.end(), trenutni);
        if (it != druga.elementi.end()) {
            rez.elementi.push_back(trenutni);
        }
    }
    return rez;
}

Lista Lista::operator - () const {
    Lista rez = *this;
    std::reverse(rez.elementi.begin(), rez.elementi.end());
    return rez;
}

// leksikografsko poredjenje
std::string Lista::to_string_repr() const {
    std::string s = "[";
    for (size_t i = 0; i < elementi.size(); i++) {
        s += elementi[i] + (i + 1 < elementi.size() ? ", " : "");
    }
    s += "]";
    return s;
}

bool Lista::operator == (const Lista& druga) const {
    return to_string_repr() == druga.to_string_repr();
}

bool Lista::operator != (const Lista& druga) const {
    return to_string_repr() != druga.to_string_repr();
}

bool Lista::operator < (const Lista& druga) const {
    return to_string_repr() < druga.to_string_repr();
}

bool Lista::operator <= (const Lista& druga) const {
    return to_string_repr() <= druga.to_string_repr();
}

bool Lista::operator > (const Lista& druga) const {
    return to_string_repr() > druga.to_string_repr();
}

bool Lista::operator >= (const Lista& druga) const {
    return to_string_repr() >= druga.to_string_repr();
}
