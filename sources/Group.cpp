#include "Group.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
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
    return to_string(getId()) + ";" + getName();
}


// Opérateur d'affichage (<<)
/*ostream& operator<<(ostream& os, const Group& g) {
    os << g.toString();
    return os;
}*/


std::ostream& operator<<(std::ostream& os, const Group& c) {
    os << "<Group>\n"
       << "<id>\n" << c.getId() << "\n</id>\n"
       << "<name>\n" << c.getName() << "\n</name>\n"
       << "</Group>\n";
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

// Opérateur<
bool Group::operator<(const Group& other) const {
    return getName() < other.getName();  
}


istream& operator>>(istream& is, Group& c) {
    string line;
    // Vérification et lecture de la balise <Group>
    getline(is, line);
    if (line != "<Group>") {
        is.setstate(std::ios::failbit);
        return is;
    }
    // Lecture de l'id
    getline(is, line); // <id>
    getline(is, line); // Valeur de l'id
    int id;
    istringstream iss_id(line);
    if (!(iss_id >> id)) {
        is.setstate(ios::failbit);
        return is;
    }
    c.setId(id); // Définir l'ID
    getline(is, line); // </id>
    // Lecture du nom
    getline(is, line); // <name>
    getline(is, line); // Valeur du nom
    c.setName(line); // Définir le nom
    getline(is, line); // </name>
    // Vérification de la fermeture </Group>
    getline(is, line); // </Group>
    if (line != "</Group>") {
        is.setstate(ios::failbit);
    }
    return is;
}