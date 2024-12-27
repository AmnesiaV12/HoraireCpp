#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H

#include <iostream>
#include <string>
#include "Time.h"
using namespace std;


class Schedulable { // Page 32 du cours
protected:
    int id;
    

public:
    
    static int currentId;

    // Constructeur par défaut
    Schedulable();

    // Constructeur avec paramètre
    Schedulable(int id);

    // Constructeur de copie
    Schedulable(const Schedulable& other);

    // Destructeur virtuel
    virtual ~Schedulable();

    // Accesseur pour l'ID
    int getId() const;

    // Mutateur pour l'ID
    void setId(int newId);

    // Méthode virtuelle pure pour retourner une description
    virtual string toString() const = 0;

    // Méthode virtuelle pure pour retourner un tuple
    virtual string tuple() const = 0;

    // Opérateur d'affectation
    Schedulable& operator=(const Schedulable& s);

    // Opérateur d'insertion dans un flux
    friend ostream& operator<<(ostream& s, const Schedulable& t);
};

#endif