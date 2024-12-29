#ifndef TIMING_H
#define TIMING_H

#include <iostream>
#include <string>
#include "Time.h"
#include "TimingException.h"
using namespace std; // permet de ne pas avoir à écrire std::

namespace planning {

class Timing {
private:
    string day;
    Time start;
    Time duration;
    //int convert(const std::string& day) const;

public:

    static const string MONDAY;
    static const string TUESDAY;
    static const string WEDNESDAY;
    static const string THURSDAY;
    static const string FRIDAY;
    static const string SATURDAY;
    static const string SUNDAY;

    // Constructeurs
    // constructeur par défaut
    Timing() noexcept;
    // constructeur avec paramètres
    Timing(const string &d, const Time &s, const Time &dur);
    // constructeur de copie
    Timing(const Timing &other) noexcept;

    // Destructeur
    ~Timing() noexcept;

    int operator<(const Timing& other) const;
    int operator>(const Timing& other) const;
    int operator==(const Timing& other) const;

    friend ostream& operator<<(ostream& os, const Timing& t);
    friend istream& operator>>(istream& is, Timing& t);

    int convert(const std::string& day) const;

    // Getters
    string getDay() const;
    Time getStart() const;
    Time getDuration() const;

    // Setters
    void setDay(const string &d);
    void setStart(const Time &s);
    void setDuration(const Time &dur);

    // Méthode pour afficher les informations de l'événement
    void display() const;
    string toString() const;
};
}

#endif