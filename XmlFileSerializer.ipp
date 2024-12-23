#include <iostream>
#include <string>
#include <fstream>
#include "Exception.h"
#include <sstream>
#include <algorithm>
#include "XmlFileSerializer.hpp"
#include "XmlFileSerializerException.h"
using namespace std;

namespace planning {

// Constructeur
template <typename T>
XmlFileSerializer<T>::XmlFileSerializer(const string &fn, char m, const string &cn)
{
    filename = fn;
    mode = m;
    collectionName = cn;

    // (READ)
    if (mode == READ)
    {
        file.open(filename, ios::in);  // ios::in est utilisé pour ouvrir en lecture seule
        if (!file.is_open())
        {
            throw(XmlFileSerializerException(XmlFileSerializerException::FILE_NOT_FOUND));
        }
        // Lire l'entête XML
        string tag;
        getline(file, tag);
        getline(file, tag); // Lire la ligne suivante qui contient la balise de collection
        size_t startPos = tag.find('<');
        size_t endPos = tag.find('>', startPos);
        collectionName = tag.substr(startPos + 1, endPos - startPos - 1);
    }
    else
    {
        // (WRITE)
        file.open(filename, ios::out); // ios::out est utilisé pour ouvrir en écriture seule
        // Écrire l'entête XML
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        // Écrire la balise de début de collection
        file << "<" << collectionName << ">" << endl;
    }
}
// Destructeur
template <typename T>
XmlFileSerializer<T>::~XmlFileSerializer()
{
    if (mode == WRITE)
    {
        file << "</" << collectionName << ">" << endl; // Si Mode écriture / écrire balise fin collection
    }
    file.close();
}

// Méthodes d'accès
template <typename T>
string XmlFileSerializer<T>::getFilename() const
{
    return filename;
}

template <typename T>
string XmlFileSerializer<T>::getCollectionName() const
{
    return collectionName;
}

template <typename T>
bool XmlFileSerializer<T>::isReadable() const // Vérifie si en mode lecture
{
    if(file.is_open())
        {
            if(mode == READ)
            {
                return true;
            }
        }
        return false;
}

template <typename T>
bool XmlFileSerializer<T>::isWritable() const // Vérifie si en mode écriture
{
    if(file.is_open())
        {
            if(mode == WRITE)
            {
                return true;
            }
        }
        return false;
}

template <typename T>
void XmlFileSerializer<T>::write(const T& val) // Méthode write Sérialise un objet T / l'écrit dans fichier
{
    if (!isWritable())
    {
        throw(XmlFileSerializerException(XmlFileSerializerException::NOT_ALLOWED));
    }
    file << val; // Sérialiser l'objet / l'écrire dans le fichier
}

template <typename T>
T XmlFileSerializer<T>::read() // Méthode read Désérialise un objet T du fichier
{
    if (!file.is_open())
    {
        throw(XmlFileSerializerException(XmlFileSerializerException::FILE_NOT_FOUND));
    }
    if (!isReadable())
    {
        throw(XmlFileSerializerException(XmlFileSerializerException::NOT_ALLOWED));
    }

    streampos positionAvantLecture = file.tellg();
    string val;
    file >> val; // Lire ligne fichier

    cout << "Valeur lue : " << val << endl; // Message de débogage
    
    if (val == "</" + collectionName + ">") // Vérifier si fin du fichier
    {
        throw(XmlFileSerializerException(XmlFileSerializerException::END_OF_FILE));
    }
    // Rétablir la position dans le fichier pour commencer la lecture de l'objet
    file.seekg(positionAvantLecture, ios::beg);
    
    T v;
    
    file >> v; // Désérialiser l'objet du fichier
    
    return v;
}
}