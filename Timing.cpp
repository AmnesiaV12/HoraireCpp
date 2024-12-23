#include "Timing.h"
#include "TimingException.h"
#include <iostream>
#include <cstring>
using namespace std;

namespace planning {

// Définition des jours de la semaine
const std::string Timing::MONDAY = "Lundi";
const std::string Timing::TUESDAY = "Mardi";
const std::string Timing::WEDNESDAY = "Mercredi";
const std::string Timing::THURSDAY = "Jeudi";
const std::string Timing::FRIDAY = "Vendredi";
const std::string Timing::SATURDAY = "Samedi";
const std::string Timing::SUNDAY = "Dimanche";

// Constructeur par défaut
Timing::Timing() noexcept {
    day[0] = '\0';
    start = Time();
    duration = Time();
}

// Constructeur avec paramètres
Timing::Timing(const string& d, const Time &s, const Time &dur) {
    if (convert(d) == -1) {
        throw planning::TimingException("Jour invalide", planning::TimingException::INVALID_DAY);
    }
    setDay(d);
    start = Time(s);
    duration = Time(dur);
}

// Constructeur de copie
Timing::Timing(const Timing &other) noexcept {
    setDay(other.day);
    start = Time((other.start));
    duration = Time((other.duration));
}

// Destructeur
Timing::~Timing() noexcept {
    
}

int Timing::convert(const std::string& day) const {
    if (day == MONDAY) return 1;
    if (day == TUESDAY) return 2;
    if (day == WEDNESDAY) return 3;
    if (day == THURSDAY) return 4;
    if (day == FRIDAY) return 5;
    if (day == SATURDAY) return 6;
    if (day == SUNDAY) return 7;
    return -1; // Cas invalide
}

int Timing::operator<(const Timing& other) const {
    if (day < other.day) return 1;
    if (day > other.day) return 0;
    
    // Si les jours sont égaux, on compare les heures de début
    if (start < other.start) return 1;
    if (start > other.start) return 0;

    return (duration < other.duration) ? 1 : 0;
}

int Timing::operator>(const Timing& other) const {
    if (day > other.day) return 1; // Comparaison des jours de la semaine
    if (day < other.day) return 0;

    if (start > other.start) return 1;
    if (start < other.start) return 0;

    return (duration > other.duration) ? 1 : 0;
}

int Timing::operator==(const Timing& other) const {
    return (day == other.day && start == other.start && duration == other.duration) ? 1 : 0;
}

std::ostream& operator<<(std::ostream& os, const Timing& t) {
    os << "<Timing>\n"
       << "<day>\n" << t.getDay() << "\n</day>\n"
       << "<start>\n" << t.start << "\n</start>\n"
       << "<duration>\n" << t.duration << "\n</duration>\n"
       << "</Timing>";
    return os;
}

istream& operator>>(istream& is, Timing& t) {
    //cout << "000" << endl;
    string line;
    string day;
    Time start, duration;

    getline(is, line); // <Timing>
    getline(is, line); // <day>
    getline(is, line); // valeur du jour
    //cout << "aaa" << endl;
    std::istringstream iss_day(line);
    if (!(iss_day >> day)) {
        is.setstate(ios::failbit);
        return is;
    }
    //cout << "bbb" << endl;
    getline(is, line); // </day>
    getline(is, line); // <start>
    cout << "-----" << line << "-----" << endl;
    is >> start;
    getline(is, line); // </start>
    getline(is, line); // <duration>
    is >> duration; // Lecture de la durée
    getline(is, line); // </duration>
    getline(is, line); // </Timing>

    // Mise à jour des attributs
    t.setDay(day);
    t.setStart(start);
    t.setDuration(duration);

    return is;
}

// Getter pour `day`
string Timing::getDay() const {
    return day;
}

// Getter pour `start`
Time Timing::getStart() const {
    return start;
}

// Getter pour `duration`
Time Timing::getDuration() const {
    return duration;
}

// Setter pour `day`
void Timing::setDay(const string& d) {
    if (convert(d) == -1) {
        throw planning::TimingException("Jour invalide", planning::TimingException::INVALID_DAY);
    }
   day = d;
}

// Setter pour `start`
void Timing::setStart(const Time &s) {
    
    start = s;
}

// Setter pour `duration`
void Timing::setDuration(const Time &dur) {
    
    duration = dur;
}

// Méthode pour afficher les informations de l'événement
void Timing::display() const {
    std::cout << "Day: " << day << ", Start: ";
    start.display();
    std::cout << ", Duration: ";
    duration.display();
    std::cout << std::endl;
}

string Timing::toString() const {
    return "Timing[Day=" + day + ", Start=" + start.toString() + ", Duration=" + duration.toString() + "]";
}
}