#include "skup.hpp"

Skup::Skup()
    : _elementi() {}

Skup::Skup(int v)
    : _elementi() {
        _elementi.insert(v);
    }

Skup::Skup(int start, int end)
    : _elementi() {
        if (start > end)
            throw std::invalid_argument("start < end");
        for (int i = start; i <= end; i++) {
            _elementi.insert(i);
        }
    }

Skup::Skup(const std::set<int>& s)
    : _elementi() {
        for (auto& v : s) {
            _elementi.insert(v);
        }
    }

Skup::Skup(const Skup& s)
    : _elementi() {
        for (auto& v : s._elementi) {
            _elementi.insert(v);
        }
    }

Skup::~Skup() {}

Skup& Skup::operator = (const Skup& s) {

    if (this == &s)
        return *this;

    _elementi.clear();
    for (auto& v : s._elementi) {
        _elementi.insert(v);
    }

    return *this;
}

void Skup::Dodaj(int v) {
    _elementi.insert(v);
}

bool Skup::Sadrzi(int v) const {
    return _elementi.find(v) != _elementi.end();
}

bool Skup::Sadrzi(const Skup& s) const {

    for (auto& v : s._elementi) {
        if (_elementi.find(v) == _elementi.end())
            return false;
    }

    return true;
}

int Skup::Size() const {
    return _elementi.size();
}

Skup* Skup::operator + (const Skup& s) const {
    
    Skup* result = new Skup();

    for (auto& v : _elementi) {
        result->Dodaj(v);
    }

    for (auto& v : s._elementi) {
        result->Dodaj(v);
    }

    return result;
}

Skup* Skup::operator - (const Skup& s) const {

    Skup* result = new Skup();

    for (auto& v : _elementi) {
        if (s._elementi.find(v) == s._elementi.end())
            result->Dodaj(v);
    }

    return result;
}

Skup* Skup::operator * (const Skup& s) const {

    Skup* result = new Skup();

    for (auto& v : _elementi) {
        if (s._elementi.find(v) != s._elementi.end())
            result->Dodaj(v);
    }

    return result;
}

bool Skup::operator == (const Skup& s) const {
    
    if (_elementi.size() != s._elementi.size())
        return false;

    for (auto& v : s._elementi) {
        if (_elementi.find(v) == _elementi.end())
            return false;
    }

    return true;
}

bool Skup::operator != (const Skup& s) const {
    return !(*this == s);
}

void Skup::show(std::ostream& s) const {

    s << "{";
    for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
        if (it != _elementi.begin())
            s << ", ";
        s << (*it);
    }
    s << "}";
}

std::ostream& operator << (std::ostream& s, const Skup& ss) {
    ss.show(s);
    return s;
}