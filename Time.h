#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>  // pour std::setw
#include "TimeException.h"

namespace planning {

class Time {
private:
    int hour;
    int minute;

public:
    // Constructeurs
    // constructeur par défaut
    Time() noexcept; // Page 19
    // constructeur d'initialisation
    Time(int h, int m);
    Time(int d);
    // constructeur de copie
    Time(const Time &other) noexcept;
    // Destructeur
    ~Time() noexcept;

    Time& operator=(const Time& other);

    // Opérateur +
    Time operator+(int minutesToAdd) const;
    Time operator+(const Time& duration) const;

    // Opérateur -
    Time operator-(int minutesToSubtract) const;
    Time operator-(const Time& other) const;

    friend Time operator+(int minutes, const Time& t);
    friend Time operator-(int a, const Time& t);
    // Déclaration de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Time& t);
    // Déclaration de l'opérateur >>
    friend std::istream& operator>>(std::istream& is, Time& t);

    int operator<(const Time& other) const;
    int operator>(const Time& other) const;
    int operator==(const Time& other) const;

    // Surcharge des opérateurs ++ et --
    // Pré-incrémentation
    Time& operator++();
    Time& operator--();
    // Post-incrémentation
    Time operator++(int);
    Time operator--(int);

    // Getters
    int getHour() const;
    int getMinute() const;

    // Setters
    void setHour(int h);
    void setMinute(int m);

    // Méthode pour afficher l'heure
    void display() const;
    string toString() const;
};
}

#endif