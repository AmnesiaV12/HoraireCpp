#include "Classroom.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Time.h"
#include "TimeException.h"
using namespace std;

Classroom::Classroom() {
    setId(0);
    setName("");
    setSeatingCapacity(0);
}

Classroom::Classroom(int id, const string& name, int seatingCapacity) {
    setId(id);
    setName(name);
    setSeatingCapacity(seatingCapacity);
}

Classroom::Classroom(const Classroom& other) {
    setId(other.getId());
    setName(other.getName());
    setSeatingCapacity(other.getSeatingCapacity());
}

Classroom::~Classroom() {}

string Classroom::getName() const {
    return name;
}

int Classroom::getSeatingCapacity() const {
    return seatingCapacity;
}

void Classroom::setName(const string &na) {
    name = na;
}

void Classroom::setSeatingCapacity(int sC) {
    seatingCapacity = sC;
}

string Classroom::toString() const {
    return "Classroom[ID=" + to_string(getId()) + ", Name=" + name + ", SeatingCapacity=" + to_string(seatingCapacity) + "]";
}

string Classroom::tuple() const {
    return to_string(getId()) + ";" + getName() + ";" + to_string(getSeatingCapacity());
}

std::ostream& operator<<(std::ostream& os, const Classroom& c) {
    os << "<Classroom>\n"
       << "<id>\n" << c.getId() << "\n</id>\n"
       << "<name>\n" << c.getName() << "\n</name>\n"
       << "<seatingCapacity>\n" << c.getSeatingCapacity() << "\n</seatingCapacity>\n"
       << "</Classroom>\n";
    return os;
}

ostream& operator<<(ostream& os, Classroom& c) {
    os << c.toString();
    return os;
}

istream& operator>>(istream& is, Classroom& c) {
    string line;
    // Vérification et lecture de la balise <Classroom>
    getline(is, line);
    if (line != "<Classroom>") {
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
    // Lecture de la capacité de sièges
    getline(is, line); // <seatingCapacity>
    getline(is, line); // Valeur de la capacité
    int seatingCapacity;
    istringstream iss_seatingCapacity(line);
    if (!(iss_seatingCapacity >> seatingCapacity)) {
        is.setstate(ios::failbit);
        return is;
    }
    c.setSeatingCapacity(seatingCapacity); // Définir la capacité de sièges
    getline(is, line); // </seatingCapacity>
    // Vérification de la fermeture </Classroom>
    getline(is, line); // </Classroom>
    if (line != "</Classroom>") {
        is.setstate(ios::failbit);
    }
    return is;
}

Classroom& Classroom::operator=(const Classroom& other) {
    if (this != &other) {
        setId(other.getId());
        setName(other.getName());
        setSeatingCapacity(other.getSeatingCapacity());
    }
    return *this;
}

// Opérateur<
bool Classroom::operator<(const Classroom& other) const {
    return getName() < other.getName();
}

bool Classroom::operator==(const Classroom& other) const {
    return this->getId() == other.getId(); 
}
