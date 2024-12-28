#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <set>
#include <string>
#include <iostream>
#include "Classroom.h"  // Inclut la définition de la classe Classroom
#include "Professor.h"  // Inclut la définition de la classe Professor
#include "Group.h"      // Inclut la définition de la classe Group
#include <algorithm>

using namespace std;

class Timetable {
private:
    set<Classroom> classrooms; // Ensemble des salles de classe
    set<Professor> professors; // Ensemble des professeurs
    set<Group> groups;         // Ensemble des groupes
    Timetable();
    Timetable(const Timetable& t) = delete;
    Timetable& operator=(const Timetable& other) = delete;
    static Timetable instance;
public:
    // Constructeur et destructeur
    
    ~Timetable();

    // Méthodes pour les salles de classe
    int addClassroom(const string& name, int seatingCapacity);
    void displayClassrooms() const;
    Classroom findClassroomByIndex(int index) const;
    Classroom findClassroomById(int id) const;
    void deleteClassroomByIndex(int index);
    void deleteClassroomById(int id);

    // Méthodes pour les professeurs
    int addProfessor(const string& lastName, const string& firstName);
    void displayProfessors() const;
    Professor findProfessorByIndex(int index) const;
    Professor findProfessorById(int id) const;
    void deleteProfessorByIndex(int index);
    void deleteProfessorById(int id);

    // Méthodes pour les groupes
    int addGroup(const string& name);
    void displayGroups() const;
    Group findGroupByIndex(int index) const;
    Group findGroupById(int id) const;
    void deleteGroupByIndex(int index);
    void deleteGroupById(int id);
    static Timetable& getInstance();
};

#endif // TIMETABLE_H