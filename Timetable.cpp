#include "Timetable.h"
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

// Constructeur par défaut
Timetable::Timetable() {}

// Destructeur
Timetable::~Timetable() {}

// Ajout d'une salle de classe
int Timetable::addClassroom(const string& name, int seatingCapacity) {
    Classroom classroom(Schedulable::currentId, name, seatingCapacity);
    classrooms.insert(classroom);
    return classroom.getId();
}

// Affichage des salles de classe
void Timetable::displayClassrooms() const {
    for (const auto& classroom : classrooms) {
        cout << classroom << endl;
    }
}

// Recherche d'une salle de classe par index
Classroom Timetable::findClassroomByIndex(int index) const {
    if (index < 0 || index >= classrooms.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = classrooms.begin();
    advance(it, index);
    return *it;
}

// Recherche d'une salle de classe par ID
Classroom Timetable::findClassroomById(int id) const {
    auto it = find_if(classrooms.cbegin(), classrooms.cend(), [id](const Classroom& c) {
        return c.getId() == id;
    });
    if (it == classrooms.cend()) {
        throw invalid_argument("Salle de classe introuvable");
    }
    return *it;
}

// Suppression d'une salle de classe par index
void Timetable::deleteClassroomByIndex(int index) {
    if (index < 0 || index >= classrooms.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = classrooms.begin();
    advance(it, index);
    classrooms.erase(it);
}

// Suppression d'une salle de classe par ID
void Timetable::deleteClassroomById(int id) {
    auto it = find_if(classrooms.begin(), classrooms.end(), [id](const Classroom& c) {
        return c.getId() == id;
    });
    if (it == classrooms.end()) {
        throw invalid_argument("Salle de classe introuvable");
    }
    classrooms.erase(it);
}

// Ajout d'un professeur
int Timetable::addProfessor(const string& lastName, const string& firstName) {
    Professor professor(Schedulable::currentId, lastName, firstName);
    professors.insert(professor);
    return professor.getId();
}

// Affichage des professeurs
void Timetable::displayProfessors() const {
    for (const auto& professor : professors) {
        cout << professor << endl;
    }
}

// Recherche d'un professeur par index
Professor Timetable::findProfessorByIndex(int index) const {
    if (index < 0 || index >= professors.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = professors.begin();
    advance(it, index);
    return *it;
}

// Recherche d'un professeur par ID
Professor Timetable::findProfessorById(int id) const {
    auto it = find_if(professors.begin(), professors.end(), [id](const Professor& p) {
        return p.getId() == id;
    });
    if (it == professors.end()) {
        throw invalid_argument("Professeur introuvable");
    }
    return *it;
}

// Suppression d'un professeur par index
void Timetable::deleteProfessorByIndex(int index) {
    if (index < 0 || index >= professors.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = professors.begin();
    advance(it, index);
    professors.erase(it);
}

// Suppression d'un professeur par ID
void Timetable::deleteProfessorById(int id) {
    auto it = find_if(professors.begin(), professors.end(), [id](const Professor& p) {
        return p.getId() == id;
    });
    if (it == professors.end()) {
        throw invalid_argument("Professeur introuvable");
    }
    professors.erase(it);
}

// Ajout d'un groupe
int Timetable::addGroup(const string& name) {
    Group group(Schedulable::currentId, name);
    groups.insert(group);
    return group.getId();
}

// Affichage des groupes
void Timetable::displayGroups() const {
    for (const auto& group : groups) {
        cout << group << endl;
    }
}

// Recherche d'un groupe par index
Group Timetable::findGroupByIndex(int index) const {
    if (index < 0 || index >= groups.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = groups.begin();
    advance(it, index);
    return *it;
}

// Recherche d'un groupe par ID
Group Timetable::findGroupById(int id) const {
    auto it = find_if(groups.begin(), groups.end(), [id](const Group& g) {
        return g.getId() == id;
    });
    if (it == groups.end()) {
        throw invalid_argument("Groupe introuvable");
    }
    return *it;
}

// Suppression d'un groupe par index
void Timetable::deleteGroupByIndex(int index) {
    if (index < 0 || index >= groups.size()) {
        throw out_of_range("Index hors limites");
    }
    auto it = groups.begin();
    advance(it, index);
    groups.erase(it);
}

// Suppression d'un groupe par ID
void Timetable::deleteGroupById(int id) {
    auto it = find_if(groups.begin(), groups.end(), [id](const Group& g) {
        return g.getId() == id;
    });
    if (it == groups.end()) {
        throw invalid_argument("Groupe introuvable");
    }
    groups.erase(it);
}
