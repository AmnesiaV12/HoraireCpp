#include "Professor.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Constructeur par défaut
Professor::Professor() {
    setId(0);
    setLastName("");
    setFirstName("");
}

// Constructeur avec paramètres
Professor::Professor(int id, const string& lastName, const string& firstName) {
    setId(id);
    setLastName(lastName);
    setFirstName(firstName);
}

// Constructeur de copie
Professor::Professor(const Professor& other) {
    setId(other.getId());
    setLastName(other.getLastName());
    setFirstName(other.getFirstName());
}

// Destructeur
Professor::~Professor() {

}

// Accesseur pour le nom de famille
string Professor::getLastName() const {
    return lastName;
}

// Accesseur pour le prénom
string Professor::getFirstName() const {
    return firstName;
}

// Mutateur pour le nom de famille
void Professor::setLastName(const string& lN) {
    this->lastName = lN;
}

// Mutateur pour le prénom
void Professor::setFirstName(const string& fN) {
    this->firstName = fN;
}

// Méthode toString
string Professor::toString() const {
    return "Professor[ID=" + to_string(getId()) + 
           ", LastName=" + lastName + 
           ", FirstName=" + firstName + "]";
}

// Méthode tuple
string Professor::tuple() const {
    return "(" + to_string(getId()) + ", " + lastName + ", " + firstName + ")";
}

// Opérateur affichage
ostream& operator<<(ostream& os, const Professor& p) {
    os << p.toString();
    return os;
}

// Opérateur d'affectation
Professor& Professor::operator=(const Professor& other) {
    if (this != &other) {
        setId(other.getId());
        setLastName(other.getLastName());
        setFirstName(other.getFirstName());
    }
    return *this;
}

// Opérateur<
bool Professor::operator<(const Professor& other) const {
    return getLastName() < other.getLastName(); 
}
