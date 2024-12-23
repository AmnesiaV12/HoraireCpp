#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "Schedulable.h"
#include <iostream>
#include <string>
using namespace std;

class Classroom : public Schedulable {
private:
    string name;
    int seatingCapacity;

public:
    // Constructeurs
    Classroom();
    Classroom(int id, const string& name, int seatingCapacity);
    Classroom(const Classroom& other);

    // Destructeur
    ~Classroom() override;

    string getName() const;
    int getSeatingCapacity() const;

    // Setters
    void setName(const string &na);
    void setSeatingCapacity(int sC);

    string toString() const override;
    string tuple() const override;

    // Opérateur d'affichage
    friend ostream& operator<<(ostream& os, const Classroom& c);
    friend istream& operator>>(istream& is, Classroom& c);
    // Opérateur d'affectation
    Classroom& operator=(const Classroom& other);
};

#endif