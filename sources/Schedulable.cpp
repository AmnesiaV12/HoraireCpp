#include "Schedulable.h"
#include <iostream>
#include <cstring>

int Schedulable::currentId = 1;

// Constructeur par défaut
Schedulable::Schedulable() {
    setId(0);
}

// Constructeur avec paramètre
Schedulable::Schedulable(int newId) {
    setId(newId);
}

// Constructeur de copie
Schedulable::Schedulable(const Schedulable& other) {
    setId(other.id);
}

// Destructeur virtuel
Schedulable::~Schedulable() {

}

// Accesseur pour l'ID
int Schedulable::getId() const {
    return id;
}

// Mutateur pour l'ID
void Schedulable::setId(const int newId) {
    id = newId;
}

Schedulable& Schedulable::operator=(const Schedulable &s)
{
    this->id = s.id;
    return (*this);
}

ostream & operator<<(ostream &s, const Schedulable &t)
{
    cout << t.getId() << ";";
    return s;
}