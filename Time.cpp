#include "Time.h"
#include "TimeException.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace planning {

Time::Time() noexcept {
    setHour(0);
    setMinute(0);
}

Time::Time(int h, int m) { // Page 16
    if (h < 0 || h > 23) {
        throw planning::TimeException("Heure invalide", planning::TimeException::INVALID_HOUR);
    }
    if (m < 0 || m > 59) {
        throw planning::TimeException("Minute invalide", planning::TimeException::INVALID_MINUTE);
    }
    setHour(h);
    setMinute(m);
}

Time::Time(int d) {
    //if (d >= 24 *) throw
    if (d < 0 || d > 1439) {  // 1439 m = 23h59
        throw planning::TimeException("Nombre de minutes invalide", planning::TimeException::INVALID_HOUR);
    }   
    setHour(d/60);
    setMinute(d%60);
}

Time::Time(const Time &other) noexcept {
    setHour(other.getHour());
    setMinute(other.getMinute());
}

Time::~Time() noexcept {}

// Opérateur d'assignation
Time& Time::operator=(const Time& other) {
    if (this != &other) {  // Eviter l'auto-assignation
        hour = other.hour;
        minute = other.minute;
    }
    return *this;
}

// Surcharge +
Time Time::operator+(int minutesToAdd) const {
    int totalMinutes = (hour * 60 + minute) + minutesToAdd;
    if (totalMinutes < 0 || totalMinutes >= 1440) { // sup 1440 minute Vérifie si total minutes dépasse 23h59 (1440 minutes)
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    totalMinutes = (totalMinutes + 1440) % 1440;
    return Time(totalMinutes / 60, totalMinutes % 60);
}

Time Time::operator+(const Time& duration) const {
    return *this + (duration.hour * 60 + duration.minute);
}

// Surcharge -
Time Time::operator-(int minutesToSubtract) const {
    int totalMinutes = (hour * 60 + minute) - minutesToSubtract;
    if (totalMinutes < 0 || totalMinutes >= 1440) { // inf 1440 minute
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    totalMinutes = (totalMinutes + 1440) % 1440;
    return Time(totalMinutes / 60, totalMinutes % 60);
}

Time Time::operator-(const Time& other) const {
    int diffMinutes = (hour * 60 + minute) - (other.hour * 60 + other.minute);
    if (diffMinutes < 0) {
        diffMinutes += 1440;
    }
    if (diffMinutes < 0 || diffMinutes >= 1440) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    return Time(diffMinutes / 60, diffMinutes % 60);
}

Time operator-(int a,const Time& t)  {
    int totalMinutes = a - (t.getHour() * 60 + t.getMinute());
    if (totalMinutes < 0 || totalMinutes >= 1440) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    totalMinutes = (totalMinutes + 1440) % 1440;
    return Time(totalMinutes / 60, totalMinutes % 60);
}

Time operator+(int minutes, const Time& t) {
    return t + minutes;
}

// Surcharge de l'opérateur <
int Time::operator<(const Time& other) const {
    return (hour * 60 + minute) < (other.hour * 60 + other.minute) ? 1 : 0;
}

// Surcharge de l'opérateur >
int Time::operator>(const Time& other) const {
    return (hour * 60 + minute) > (other.hour * 60 + other.minute) ? 1 : 0;
}

// Surcharge de l'opérateur ==
int Time::operator==(const Time& other) const {
    return (hour == other.hour) && (minute == other.minute) ? 1 : 0;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << "<Time>\n"
       << "<hour>\n" << t.getHour() << "\n</hour>\n"
       << "<minute>\n" << t.getMinute() << "\n</minute>\n"
       << "</Time>";
    return os;
}

std::istream& operator>>(std::istream& is, planning::Time& t) { // PAge 34 ET 35
    //cout << "coucou" << endl;
    string line;
    int hour = 0, minute = 0;

    // Vérification et lecture des balises
    getline(is, line); // <Time>
    //cout << "line --" << line << endl;
    if (line != "<Time>") {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // <hour>
    //cout << "line --" << line << endl;

    if (line != "<hour>") {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // valeur de l'heure
    cout << "valeur heure " << line << endl;
    istringstream iss_hour(line);
    if (!(iss_hour >> hour)) {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // </hour>
    if (line != "</hour>") {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // <minute>
    if (line != "<minute>") {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // valeur des minutes
    istringstream iss_minute(line); // Convertit la chaine 
    if (!(iss_minute >> minute)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    getline(is, line); // </minute>
    if (line != "</minute>") {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // </Time>
    if (line != "</Time>") {
        is.setstate(ios::failbit);
        return is;
    }
    // Validation des données avec les setters
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        is.setstate(ios::failbit);
        return is;
    }
    // Mise à jour des attributs
    t.setHour(hour);
    t.setMinute(minute);
    return is;
}

// Pré-incrémentation ++h
Time& Time::operator++() {
    *this = *this + 30; //Page 20 du cours
    if (hour == 0 && minute == 0) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    return *this;
}

// Post-incrémentation h++
Time Time::operator++(int) {
    Time temp = *this;  // Sauvegarde l'état avant ++
    *this = *this + 30;
    if (hour == 0 && minute == 0) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    return temp;
}

// Pré-décrémentation --h
Time& Time::operator--() {
    *this = *this - 30;
    if (hour == 23 && minute == 59) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    return *this;
}

// Post-décrémentation h--
Time Time::operator--(int) {
    Time temp = *this;  // Sauvegarde l'état avant --
    *this = *this - 30;
    if (hour == 23 && minute == 59) {
        throw planning::TimeException("Overflow : dépassement de l'heure", planning::TimeException::OVERFLOW);
    }
    return temp;
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

void Time::setHour(int h) {
    if (h < 0 || h > 23) {
        throw planning::TimeException("Heure invalide", planning::TimeException::INVALID_HOUR);
    }
    //if (h < 0 || h >= 24) return;
    hour = h;
}

void Time::setMinute(int m) {
    if (m < 0 || m > 59) {
        throw planning::TimeException("Minute invalide", planning::TimeException::INVALID_MINUTE);
    }
    //if (m < 0 || m >= 60) return;
    minute = m;
}

void Time::display() const {
    std::cout << hour << "h" << minute << "m" << endl;
}

string Time::toString() const {
    return "Time[Hour=" + std::to_string(hour) + ", Minute=" + std::to_string(minute) + "]";
}
}