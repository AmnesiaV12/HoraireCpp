#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Constructeur par défaut
Group::Group() {
    setId(0);
    setName("");
}

// Constructeur avec paramètres
Group::Group(int id, const string& name) {
    setId(id);
    setName(name);
}

// Constructeur de copie
Group::Group(const Group& other) {
    setId(other.getId());
    setName(other.getName());
}

// Destructeur
Group::~Group() {

}

// Getter pour name
string Group::getName() const {
    return name;
}

// Setter pour name
void Group::setName(const string& n) {
    name = n;
}

// Méthode toString
string Group::toString() const {
    return "Group[ID=" + to_string(getId()) + ", Name=" + name + "]";  // Retourne une chaîne représentant l'objet
}

// Méthode tuple
string Group::tuple() const {
    return "(" + to_string(getId()) + ", " + name + ")";  // Retourne une représentation sous forme de tuple
}

// Opérateur d'affichage (<<)
ostream& operator<<(ostream& os, const Group& g) {
    os << g.toString();
    return os;
}

// Opérateur d'affectation
Group& Group::operator=(const Group& other) {
    if (this != &other) { 
        setId(other.getId());
        setName(other.getName());
    }
    return *this;
}