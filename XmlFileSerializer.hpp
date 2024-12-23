#ifndef XMLFILESERIALIZER_HPP
#define XMLFILESERIALIZER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

namespace planning {

template <typename T>
class XmlFileSerializer {
private:
    fstream file;                   // Fichier
    string filename;                // Nom du fichier
    char mode;                      // Mode d'ouverture (lecture/écriture)
    string collectionName;          // Nom collection données

public:
    static const char READ = 'R';
    static const char WRITE = 'W';

    // Constructeur avec paramètre
    XmlFileSerializer(const string &fn, char m, const string &cn = "<times>");
    
    // Interdire le constructeur par défaut et la copie
    XmlFileSerializer() = delete;
    XmlFileSerializer(const XmlFileSerializer &other) = delete;

    // Destructeur
    ~XmlFileSerializer();

    // Opérateur d'affectation interdit
    XmlFileSerializer& operator=(const XmlFileSerializer &) = delete;

    // Getters
    string getFilename() const;
    string getCollectionName() const;

    // Méthodes pour vérifier les modes
    bool isWritable() const;
    bool isReadable() const;

    // Méthodes d'entrée/sortie
    void write(const T &val);  //sérialise 1 objet type T / écrit fichier XML.
    T read();

};
}

#include "XmlFileSerializer.ipp"
#endif