#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Schedulable.h"
#include <iostream>
#include <string>
using namespace std;

class Professor : public Schedulable { // Page 13
private:
    string lastName;
    string firstName;

public:
    Professor();
    Professor(int id, const string& lastName, const string& firstName);
    Professor(const Professor& other);

    ~Professor() override; // Page 18
    /*Le décorateur « override » ne peut se placer que sur une méthode déclarée virtual
    dans la classe de base. De plus, il ne se place que dans le fichier .h et non .cpp*/

    void setLastName(const string& lN);
    void setFirstName(const string& fN);

    string getLastName() const;
    string getFirstName() const;

    string toString() const override;
    string tuple() const override;

    friend ostream& operator<<(std::ostream& os, const Professor& p);

    Professor& operator=(const Professor& other);
};

#endif