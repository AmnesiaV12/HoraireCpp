#include "applichorairewindow.h"
#include "ui_applichorairewindow.h"
#include "Timetable.h"
#include "unistd.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <iostream>
#include <sstream>
using namespace std;

ApplicHoraireWindow::ApplicHoraireWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ApplicHoraireWindow)
{
    ui->setupUi(this);
    ::close(2);

    // Configuration de la table des professeurs
    ui->tableWidgetProfesseurs->setColumnCount(3);
    ui->tableWidgetProfesseurs->setRowCount(0);
    QStringList labelsTableProfesseurs;
    labelsTableProfesseurs << "id" << "Nom" << "Prenom";
    ui->tableWidgetProfesseurs->setHorizontalHeaderLabels(labelsTableProfesseurs);
    ui->tableWidgetProfesseurs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetProfesseurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetProfesseurs->horizontalHeader()->setVisible(true);
    ui->tableWidgetProfesseurs->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetProfesseurs->verticalHeader()->setVisible(false);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des groupes
    ui->tableWidgetGroupes->setColumnCount(2);
    ui->tableWidgetGroupes->setRowCount(0);
    QStringList labelsTableGroupes;
    labelsTableGroupes << "id" << "Nom";
    ui->tableWidgetGroupes->setHorizontalHeaderLabels(labelsTableGroupes);
    ui->tableWidgetGroupes->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableWidgetGroupes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetGroupes->horizontalHeader()->setVisible(true);
    ui->tableWidgetGroupes->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetGroupes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetGroupes->verticalHeader()->setVisible(false);
    ui->tableWidgetGroupes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des locaux
    ui->tableWidgetLocaux->setColumnCount(2);
    ui->tableWidgetLocaux->setRowCount(0);
    QStringList labelsTableLocaux;
    labelsTableLocaux << "id" << "Nom";
    ui->tableWidgetLocaux->setHorizontalHeaderLabels(labelsTableLocaux);
    ui->tableWidgetLocaux->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetLocaux->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLocaux->horizontalHeader()->setVisible(true);
    ui->tableWidgetLocaux->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetLocaux->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetLocaux->verticalHeader()->setVisible(false);
    ui->tableWidgetLocaux->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des cours
    ui->tableWidgetCourss->setColumnCount(8);
    ui->tableWidgetCourss->setRowCount(0);
    QStringList labelsTableCourss;
    labelsTableCourss << "code" << "Jour" << "Heure" << "Duree" << "Local" << "Intitule" << "Professeur" << "Groupes";
    ui->tableWidgetCourss->setHorizontalHeaderLabels(labelsTableCourss);
    ui->tableWidgetCourss->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->tableWidgetCourss->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetCourss->horizontalHeader()->setVisible(true);
    ui->tableWidgetCourss->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetCourss->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetCourss->verticalHeader()->setVisible(false);
    ui->tableWidgetCourss->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Pour faire joli
    ui->pushButtonAjouterProfesseur->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterGroupe->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterLocal->setStyleSheet("background-color: lightgreen");
    ui->pushButtonSupprimerProfesseur->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerGroupe->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerLocal->setStyleSheet("background-color: orange");
    ui->pushButtonPlanifier->setStyleSheet("background-color: lightblue");
    ui->pushButtonSelectionner->setStyleSheet("background-color: lightblue");

    // On fixe la taille et la position de la fenetre
    setFixedSize(1070,647);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);

}

ApplicHoraireWindow::~ApplicHoraireWindow() {
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::addTupleTableProfessors(const string& tuple) {
    // Parsing du tuple recu
    istringstream ss(tuple);
    string token;

    string id, lastName, firstName;
    getline(ss,id,';');
    getline(ss,lastName,';');
    getline(ss,firstName,';');

    // Ajout dans la table
    int nbLignes = ui->tableWidgetProfesseurs->rowCount();
    nbLignes++;
    ui->tableWidgetProfesseurs->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(id));
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(lastName));
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(firstName));
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,2,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearTableProfessors() {
    ui->tableWidgetProfesseurs->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndexProfessorSelection() const {
    QModelIndexList liste = ui->tableWidgetProfesseurs->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des groupes /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::addTupleTableGroups(const string& tuple) {
    // Parsing du tuple recu
    istringstream ss(tuple);
    string token;

    string id, name;
    getline(ss,id,';');
    getline(ss,name,';');

    // Ajout possible
    int nbLignes = ui->tableWidgetGroupes->rowCount();
    nbLignes++;
    ui->tableWidgetGroupes->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(id));
    ui->tableWidgetGroupes->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(name));
    ui->tableWidgetGroupes->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearTableGroups() {
    ui->tableWidgetGroupes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
list<int> ApplicHoraireWindow::getIndexesGroupsSelection() const {
    QModelIndexList liste = ui->tableWidgetGroupes->selectionModel()->selectedRows();
    list<int> result;
    for (int i=0 ; i<liste.size() ; i++) result.push_back(liste.at(i).row());
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des locaux //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::addTupleTableClassrooms(const string& tuple) {
    // Parsing du tuple recu
    istringstream ss(tuple);
    string token;

    string id, name;
    getline(ss,id,';');
    getline(ss,name,';');

    // Ajout possible
    int nbLignes = ui->tableWidgetLocaux->rowCount();
    nbLignes++;
    ui->tableWidgetLocaux->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(id));
    ui->tableWidgetLocaux->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(name));
    ui->tableWidgetLocaux->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearTableClassrooms() {
    ui->tableWidgetLocaux->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndexClassroomSelection() const {
    QModelIndexList liste = ui->tableWidgetLocaux->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::addTupleTableCourses(const string& tuple) {
    // Parsing du tuple recu
    istringstream ss(tuple);
    string token;

    string code, day, hour, duration, classroom, title, professor, groups;
    getline(ss,code,';');
    getline(ss,day,';');
    getline(ss,hour,';');
    getline(ss,duration,';');
    getline(ss,classroom,';');
    getline(ss,title,';');
    getline(ss,professor,';');
    getline(ss,groups,';');

    // Ajout possible
    int nbLignes = ui->tableWidgetCourss->rowCount();
    nbLignes++;
    ui->tableWidgetCourss->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(code));
    ui->tableWidgetCourss->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(day));
    ui->tableWidgetCourss->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(hour));
    ui->tableWidgetCourss->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(duration));
    ui->tableWidgetCourss->setItem(nbLignes-1,3,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(classroom));
    ui->tableWidgetCourss->setItem(nbLignes-1,4,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(title));
    ui->tableWidgetCourss->setItem(nbLignes-1,5,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(professor));
    ui->tableWidgetCourss->setItem(nbLignes-1,6,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(QString::fromStdString(groups));
    ui->tableWidgetCourss->setItem(nbLignes-1,7,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearTableCourses() {
    ui->tableWidgetCourss->setRowCount(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogMessage(const string& title,const string& message) {
   QMessageBox::information(this,QString::fromStdString(title),QString::fromStdString(message));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogError(const string& title,const string& message) {
   QMessageBox::critical(this,QString::fromStdString(title),QString::fromStdString(message));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::dialogInputText(const string& title,const string& question) {
    return QInputDialog::getText(this,QString::fromStdString(title),QString::fromStdString(question)).toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::dialogInputInt(const string& title,const string& question) {
    return QInputDialog::getInt(this,QString::fromStdString(title),QString::fromStdString(question));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::dialogInputFileForLoad(const string& question)
{
  QString fileName = QFileDialog::getOpenFileName(this,QString::fromStdString(question), "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::dialogInputFileForSave(const string& question)
{
  QString fileName = QFileDialog::getSaveFileName(this,QString::fromStdString(question), "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles aux widgets de la fenetre /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getProfessorLastName() const {
    return ui->lineEditNomProfesseur->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setProfessorLastName(const string& lastName) {
    ui->lineEditNomProfesseur->setText(QString::fromStdString(lastName));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getProfessorFirstName() const {
    return ui->lineEditPrenomProfesseur->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setProfessorFirstName(const string& firstName) {
    ui->lineEditPrenomProfesseur->setText(QString::fromStdString(firstName));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getGroupName() const {
    return ui->lineEditNumeroGroupe->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearGroupName() {
    ui->lineEditNumeroGroupe->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getClassroomName() const {
    return ui->lineEditNomLocal->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setClassroomName(const string& name) {
    ui->lineEditNomLocal->setText(QString::fromStdString(name));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getDaySelection() const {
    return ui->comboBoxJour->currentText().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getHourStart() const {
    if (ui->lineEditHeuresDebut->text().toStdString() == "") return -1;
    return stoi(ui->lineEditHeuresDebut->text().toStdString());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearHourStart() {
    ui->lineEditHeuresDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getMinuteStart() const {
    if (ui->lineEditMinutesDebut->text().toStdString() == "") return -1;
    return stoi(ui->lineEditMinutesDebut->text().toStdString());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearMinuteStart() {
    ui->lineEditMinutesDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getDuration() const {
    if (ui->lineEditDuree->text().toStdString() == "") return -1;
    return stoi(ui->lineEditDuree->text().toStdString());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::clearDuration() {
    ui->lineEditDuree->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicHoraireWindow::getTitle() const {
    return ui->lineEditIntitule->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setTitle(const string& title) {
    ui->lineEditIntitule->setText(QString::fromStdString(title));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isDayChecked() const {
    return ui->checkBoxJour->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setDayChecked(bool b) {
    ui->checkBoxJour->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isProfessorChecked() const {
    return ui->checkBoxProfesseur->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setProfessorChecked(bool b) {
    ui->checkBoxProfesseur->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isGroupChecked() const {
    return ui->checkBoxGroupe->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setGroupChecked(bool b) {
    ui->checkBoxGroupe->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isClassroomChecked() const {
    return ui->checkBoxLocal->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setClassroomChecked(bool b) {
    ui->checkBoxLocal->setChecked(b);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterProfesseur_clicked() {
    cout << "Clic sur bouton Ajouter Professeur" << endl;

    // 1. Récupérer le nom et le prénom du professeur
    string lastName = getProfessorLastName();
    string firstName = getProfessorFirstName();

    // Vérifier si les informations sont valides
    if (lastName.empty() || firstName.empty()) {
        // Afficher un message d'erreur si le nom ou prénom est vide
        dialogError("Erreur", "Le nom ou le prénom du professeur est vide !");
        return;
    }

    // 2. Ajouter le professeur via le singleton Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.addProfessor(lastName, firstName);

    // 3.a. Vider la table des professeurs
    clearTableProfessors();

    // 3.b. Parcourir tous les professeurs avec un itérateur
    try {
        int index = 0;
        while (true) {
            Professor professor = timetable.findProfessorByIndex(index);
            addTupleTableProfessors(professor.tuple());
            ++index;
        }
    } catch (const std::out_of_range& e) {
        // Exception attendue lorsque tous les professeurs ont été parcourus
    }

    cout << "Professeur ajouté : " << lastName << " " << firstName << endl;
}


void ApplicHoraireWindow::on_pushButtonAjouterGroupe_clicked() {
    
    //TO DO (Etape 9)

    string groupName = getGroupName();

    if (groupName.empty()) {
        dialogError("Erreur", "Le nom du groupe est vide !");
        return;
    }

    // 2. Ajouter le groupe via le singleton Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.addGroup(groupName);
    clearTableGroups(); 

    //  Pour l'affichage
    try {
        int index = 0;
        while (true) {
            Group group = timetable.findGroupByIndex(index);
            addTupleTableGroups(group.tuple()); // Ajoutez chaque groupe sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
        // Si tous les groupes ont été parcourus
    }

    cout << "Groupe ajouté : " << groupName << endl;
}


void ApplicHoraireWindow::on_pushButtonAjouterLocal_clicked() {
    cout << "Clic sur bouton Ajouter Local" << endl;

    // 1. Récupérer le nom et la capacité d'accueil du local
    string classroomName = getClassroomName();
    int seatingCapacity = dialogInputInt("Ajouter un Local", "Entrez la capacité d'accueil du local :");

    // 2. Vérifier si les informations sont valides
    if (classroomName.empty()) {
        dialogError("Erreur", "Le nom du local est vide !");
        return;
    }
    if (seatingCapacity <= 0) {
        dialogError("Erreur", "La capacité d'accueil doit être un entier positif !");
        return;
    }

    // 3. Ajouter le local via le singleton Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.addClassroom(classroomName, seatingCapacity);

    // 4. Mettre à jour la table des locaux
    clearTableClassrooms();

    // Récupérer la liste triée des locaux et les ajouter dans la table
    try {
        int index = 0;
        while (true) {
            Classroom classroom = timetable.findClassroomByIndex(index);
            addTupleTableClassrooms(classroom.tuple()); // Ajoutez chaque local sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
        // Si tous les locaux ont été parcourus
    }

    cout << "Local ajouté : " << classroomName << " (Capacité : " << seatingCapacity << ")" << endl;
}


void ApplicHoraireWindow::on_pushButtonSupprimerProfesseur_clicked() {
    cout << "Clic sur bouton Supprimer Professeur" << endl;
    // TO DO (Etape 9)

    // 1. Récupérer l'indice du professeur sélectionné
    int index = getIndexProfessorSelection();
    if (index == -1) {
        dialogError("Erreur", "Aucun professeur sélectionné !");
        return;
    }

    // 2. Supprimer le professeur via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.deleteProfessorByIndex(index);
    clearTableProfessors();

    // 4. Ajouter les professeurs restants dans la table
    try {
        int index = 0;
        while (true) {
            Professor professor = timetable.findProfessorByIndex(index); // Récupérer le professeur par index
            addTupleTableProfessors(professor.tuple());  // Ajouter le professeur sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Professeur supprimé" << endl;
}


void ApplicHoraireWindow::on_pushButtonSupprimerGroupe_clicked() {
    cout << "Clic sur bouton Supprimer Groupe" << endl;
    // TO DO (Etape 9)

    // 1. Récupérer les indices des groupes sélectionnés
    std::list<int> indices = getIndexesGroupsSelection();
    if (indices.empty()) {
        dialogError("Erreur", "Aucun groupe sélectionné !");
        return;
    }

    // 2. Supprimer les groupes via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    
    // Supprimer chaque groupe sélectionné
    for (int index : indices) {
        timetable.deleteGroupByIndex(index);
    }

    clearTableGroups();
    
    try {
        int index = 0;
        while (true) {
            Group group = timetable.findGroupByIndex(index); // Récupérer le groupe par index
            addTupleTableGroups(group.tuple());  // Ajouter le groupe sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Groupes supprimés" << endl;
}

void ApplicHoraireWindow::on_pushButtonSupprimerLocal_clicked() {
    cout << "Clic sur bouton Supprimer Local" << endl;

    // 1. Récupérer l'indice du local sélectionné
    int index = getIndexClassroomSelection();
    if (index == -1) {
        dialogError("Erreur", "Aucun local sélectionné !");
        return;
    }

    // 2. Supprimer le local via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.deleteClassroomByIndex(index);
    clearTableClassrooms();

    // 3 Ajouter les locaux restants dans la table
    try {
        int index = 0;
        while (true) {
            Classroom classroom = timetable.findClassroomByIndex(index);
            addTupleTableClassrooms(classroom.tuple());
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Local supprimé" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonPlanifier_clicked()
{
    cout << "Clic sur bouton Planifier" << endl;
    // TO DO (Etape 11)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSelectionner_clicked()
{
    cout << "Clic sur bouton Selectionner" << endl;
    // TO DO (Etape 13)

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionQuitter_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Quitter" << endl;
    QApplication::quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void ApplicHoraireWindow::on_actionOuvrir_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Ouvrir" << endl;
    // TO DO (Etape 10)

    // Demander à l'utilisateur le nom de l'horaire à ouvrir
    string timetableName = dialogInputText("Ouvrir Horaire", "Entrez le nom de l'horaire à ouvrir :");

    // Vérifier si le nom n'est pas vide
    if (timetableName.empty()) {
        dialogError("Erreur", "Le nom de l'horaire ne peut pas être vide !");
        return;
    }

    // Charger l'horaire depuis le disque
    Timetable& timetable = Timetable::getInstance();
    timetable.load(timetableName);

    // Mettre à jour les tables
    clearTableProfessors();
    for (const auto& professor : timetable.getProfessors()) {
        addTupleTableProfessors(professor.tuple());
    }

    clearTableGroups();
    for (const auto& group : timetable.getGroups()) {
        addTupleTableGroups(group.tuple());
    }

    clearTableClassrooms();
    for (const auto& classroom : timetable.getClassrooms()) {
        addTupleTableClassrooms(classroom.tuple());
    }

    // Message de confirmation
    dialogMessage("Succès", "L'horaire a été chargé avec succès !");
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionNouveau_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Nouveau" << endl;
    // TO DO (Etape 10)

    // Récupérer l'instance de Timetable
    Timetable& timetable = Timetable::getInstance();

    // Vider tous les conteneurs de l'objet Timetable
    professors.clear();
    groups.clear();
    classrooms.clear();

    // Remettre la variable statique Schedulable::currentId à 1
    Schedulable::currentId = 1;

    // Mettre à jour les tables dans l'interface utilisateur
    clearTableProfessors();
    clearTableGroups();
    clearTableClassrooms();

    // Message de confirmation
    dialogMessage("Succès", "Un nouvel horaire a été créé avec succès !");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionEnregistrer_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Enregistrer" << endl;
    // TO DO (Etape 10)

    // Demander à l'utilisateur le nom de l'horaire
    string timetableName = dialogInputText("Enregistrer Horaire", "Entrez le nom de l'horaire à enregistrer :");
    
    // Vérifier si le nom n'est pas vide
    if (timetableName.empty()) {
        dialogError("Erreur", "Le nom de l'horaire ne peut pas être vide !");
        return;
    }

    // Appeler la méthode save de l'objet Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.save(timetableName);

    // Confirmation de l'enregistrement
    dialogMessage("Succès", "L'horaire a été enregistré avec succès !");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerProfesseur_triggered() {
    cout << "Clic sur Menu Supprimer --> Item Professeur" << endl;
    // TO DO (Etape 9)

    // 1. Demander à l'utilisateur l'identifiant du professeur à supprimer
    int professorId = dialogInputInt("Supprimer un professeur", "Entrez l'identifiant du professeur à supprimer :");

    // Vérification si l'identifiant est valide (non négatif)
    if (professorId < 0) {
        dialogError("Erreur", "Identifiant du professeur invalide !");
        return;
    }

    // 2. Supprimer le professeur via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.deleteProfessorById(professorId);
    clearTableProfessors();

    // 3 Ajouter les professeurs restants dans la table
    try {
        int index = 0;
        while (true) {
            Professor professor = timetable.findProfessorByIndex(index); // Récupérer le professeur par index
            addTupleTableProfessors(professor.tuple());  // Ajouter le professeur sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Professeur supprimé (ID: " << professorId << ")" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerGroupe_triggered() {
    cout << "Clic sur Menu Supprimer --> Item Groupe" << endl;
    // TO DO (Etape 9)

    // 1. Demander à l'utilisateur l'identifiant du groupe à supprimer
    int groupId = dialogInputInt("Supprimer un groupe", "Entrez l'identifiant du groupe à supprimer :");

    // Vérification si l'identifiant est valide (non négatif)
    if (groupId < 0) {
        dialogError("Erreur", "Identifiant du groupe invalide !");
        return;
    }

    // 2. Supprimer le groupe via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.deleteGroupById(groupId);
    clearTableGroups();

    // 3 Ajouter les groupes restants dans la table
    try {
        int index = 0;
        while (true) {
            Group group = timetable.findGroupByIndex(index); // Récupérer le groupe par index
            addTupleTableGroups(group.tuple());  // Ajouter le groupe sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Groupe supprimé (ID: " << groupId << ")" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerLocal_triggered() {
    cout << "Clic sur Menu Supprimer --> Item Local" << endl;
    // TO DO (Etape 9)
    // 1. Demander à l'utilisateur l'identifiant du local à supprimer
    int classroomId = dialogInputInt("Supprimer un local", "Entrez l'identifiant du local à supprimer :");

    // Vérification si l'identifiant est valide (non négatif)
    if (classroomId < 0) {
        dialogError("Erreur", "Identifiant du local invalide !");
        return;
    }

    // 2. Supprimer le local via la classe Timetable
    Timetable& timetable = Timetable::getInstance();
    timetable.deleteClassroomById(classroomId);
    clearTableClassrooms();  // Vider la table avant de la mettre à jour

    // 3 Ajouter les locaux restants dans la table
    try {
        int index = 0;
        while (true) {
            Classroom classroom = timetable.findClassroomByIndex(index); // Récupérer le local par index
            addTupleTableClassrooms(classroom.tuple());  // Ajouter le local sous forme de tuple
            ++index;
        }
    } catch (const std::out_of_range& e) {
    }

    cout << "Local supprimé (ID: " << classroomId << ")" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerCours_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Cours" << endl;
    // TO DO (Etape 11)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterProfesseurs_triggered()
{
    cout << "Clic sur Menu Importer --> Item Professeurs" << endl;
    // TO DO (Etape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterGroupes_triggered()
{
    cout << "Clic sur Menu Importer --> Item Groupes" << endl;
    // TO DO (Etape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterLocaux_triggered()
{
    cout << "Clic sur Menu Importer --> Item Locaux" << endl;
    // TO DO (Etape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterProfesseur_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Professeur" << endl;
    // TO DO (Etape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterGroupe_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Groupe" << endl;
    // TO DO (Etape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterLocal_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Local" << endl;
    // TO DO (Etape 12)

}
