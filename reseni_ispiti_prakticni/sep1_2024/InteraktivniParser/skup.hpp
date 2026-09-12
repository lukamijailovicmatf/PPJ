#ifndef SKUP_H
#define SKUP_H

#include <iostream>
#include <set>
#include <exception>

class Skup {
private:
    std::set<int> _elementi;
public:
    Skup();
    Skup(int v);
    Skup(int start, int end);
    Skup(const std::set<int>& s);
    Skup(const Skup& s);
    ~Skup();
    Skup& operator = (const Skup& s);

    void Dodaj(int v);
    bool Sadrzi(int v) const;
    bool Sadrzi(const Skup& s) const;
    int Size() const;

    Skup* operator + (const Skup& s) const;
    Skup* operator - (const Skup& s) const;
    Skup* operator * (const Skup& s) const;
    
    bool operator == (const Skup& s) const;
    bool operator != (const Skup& s) const;

    void show(std::ostream& s) const;
};

std::ostream& operator << (std::ostream& s, const Skup& ss);

#endif