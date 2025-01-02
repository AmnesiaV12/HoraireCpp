#include "Professor.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iostream>
#include <sstream>
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
    return to_string(getId()) + ";" + lastName + ";" + firstName;
}


// Opérateur affichage
/*ostream& operator<<(ostream& os, const Professor& p) {
    os << p.toString();
    return os;
}*/

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


std::ostream& operator<<(std::ostream& os, const Professor& c) {
    os << "<Professor>\n"
       << "<id>\n" << c.getId() << "\n</id>\n"
       << "<lastname>\n" << c.getLastName() << "\n</lastname>\n"
        << "<firstname>\n" << c.getFirstName() << "\n</firstname>\n"
       << "</Professor>\n";
    return os;
}


istream& operator>>(istream& is, Professor& c) {
    string line;
    // Vérification et lecture de la balise <Professor>
    getline(is, line);
    if (line != "<Professor>") {
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
    getline(is, line); // <lastname>
    getline(is, line); // Valeur du nom
    c.setLastName(line); // Définir le nom
    getline(is, line); // </lastname>
    getline(is, line); // <firstname>
    getline(is, line); // Valeur du nom
    getline(is, line); // </firstname>
    c.setFirstName(line); // Définir le nom
    // Vérification de la fermeture </Professor>
    getline(is, line); // </Professor>
    if (line != "</Professor>") {
        is.setstate(ios::failbit);
    }
    return is;
}