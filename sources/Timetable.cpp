#include "Timetable.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Schedulable.h"
#include "XmlFileSerializer.hpp"
using namespace std;

// Constructeur par défaut
Timetable::Timetable() {}

// Destructeur
Timetable::~Timetable() {}

// Ajout d'une salle de classe
int Timetable::addClassroom(const string& name, int seatingCapacity) {
    Classroom classroom(Schedulable::currentId, name, seatingCapacity);
    classrooms.insert(classroom);
    Schedulable::currentId++;
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
    auto it = find_if(classrooms.begin(), classrooms.end(), [id](const Classroom& p) {
        return p.getId() == id;
    });
    if (it == classrooms.end()) {
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
	    auto it = find_if(classrooms.begin(), classrooms.end(), [id](const Classroom& p) {
        return p.getId() == id;
    });
    if (it != classrooms.end()) {
	    classrooms.erase(it);
	} else {
	    throw invalid_argument("Salle de classe introuvable");
	}
}

// Ajout d'un professeur
int Timetable::addProfessor(const string& lastName, const string& firstName) {
    Professor professor(Schedulable::currentId, lastName, firstName);
    professors.insert(professor);
    Schedulable::currentId++;
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
    if (it != professors.end()) {
	    professors.erase(it);
	} else {
	    throw invalid_argument("Professeur introuvable");
	}
}

// Ajout d'un groupe
int Timetable::addGroup(const string& name) {
    Group group(Schedulable::currentId, name);
    groups.insert(group);
    Schedulable::currentId++;
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

Timetable Timetable::instance;

Timetable& Timetable::getInstance() {
	return instance;
}

void Timetable::save(const string& timetableName) {
    // Création des noms de fichiers
    string professorsFile = timetableName + "_professors.xml";
    string groupsFile = timetableName + "_groups.xml";
    string classroomsFile = timetableName + "_classrooms.xml";
    string configFile = timetableName + "_config.dat";

    // Sérialisation des professeurs
    planning::XmlFileSerializer<Professor> professorSerializer(professorsFile, planning::XmlFileSerializer<Professor>::WRITE, "professors");
    for (const auto& professor : professors) {
        professorSerializer.write(professor);
    }

    // Sérialisation des groupes
    planning::XmlFileSerializer<Group> groupSerializer(groupsFile, planning::XmlFileSerializer<Group>::WRITE, "groups");
    for (const auto& group : groups) {
        groupSerializer.write(group);
    }

    // Sérialisation des salles de classe
    planning::XmlFileSerializer<Classroom> classroomSerializer(classroomsFile, planning::XmlFileSerializer<Classroom>::WRITE, "classrooms");
    for (const auto& classroom : classrooms) {
        classroomSerializer.write(classroom);
    }

    // Sauvegarde de la configuration (currentId)
    ofstream configFileStream(configFile, ios::binary);
    if (!configFileStream) {
        cerr << "Erreur : impossible d'ouvrir le fichier de configuration." << endl;
        exit(EXIT_FAILURE); // Arrête le programme en cas d'erreur
    }
    configFileStream.write(reinterpret_cast<const char*>(&Schedulable::currentId), sizeof(Schedulable::currentId));
    configFileStream.close();
}

void Timetable::load(const string& timetableName) {
    // On remet afin de savoir on utilise quelle donnée afin de les lire
    string professorsFile = timetableName + "_professors.xml";
    string groupsFile = timetableName + "_groups.xml";
    string classroomsFile = timetableName + "_classrooms.xml";
    string configFile = timetableName + "_config.dat";

    professors.clear();
    groups.clear();
    classrooms.clear();

    // Charger la configuration (currentId)
    ifstream configFileStream(configFile, ios::binary);
    if (configFileStream.is_open()) {
        configFileStream.read(reinterpret_cast<char*>(&Schedulable::currentId), sizeof(Schedulable::currentId));
        configFileStream.close();
    }

    // Charger les professeurs
    planning::XmlFileSerializer<Professor> professorSerializer(professorsFile, planning::XmlFileSerializer<Professor>::READ, "professors");
    Professor professor;
    while (professorSerializer.read(professor)) { // Tant qu'il y a des données
        professors.insert(professor);            // Ajouter dans le set
    }

    // Charger les groupes
    planning::XmlFileSerializer<Group> groupSerializer(groupsFile, planning::XmlFileSerializer<Group>::READ, "groups");
    Group group;
    while (groupSerializer.read(group)) { // Tant qu'il y a des données
        groups.insert(group);             // Ajouter dans le set
    }

    // Charger les salles de classe
    planning::XmlFileSerializer<Classroom> classroomSerializer(classroomsFile, planning::XmlFileSerializer<Classroom>::READ, "classrooms");
    Classroom classroom;
    while (classroomSerializer.read(classroom)) { // Tant qu'il y a des données
        classrooms.insert(classroom);            // Ajouter dans le set
    }
    
    
    configFileStream.read(reinterpret_cast<char*>(&Schedulable::currentId), sizeof(Schedulable::currentId));
    configFileStream.close();
}

