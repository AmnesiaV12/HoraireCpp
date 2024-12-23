#ifndef XmlFileSerializerException_H
#define XmlFileSerializerException_H

#include "Exception.h"
#include <iostream>
#include <string>

using namespace std;

namespace planning {

class XmlFileSerializerException : public Exception {
private:
    int code;  

public:
    // Codes d'erreur statiques
    static const int NOT_ALLOWED = 1;
    static const int FILE_NOT_FOUND = 2;
    static const int END_OF_FILE = 3;

    // Constructeurs
    XmlFileSerializerException();  // Constructeur par défaut
    XmlFileSerializerException(int code);  // Constructeur avec code d'erreur
    XmlFileSerializerException(const XmlFileSerializerException& other);  // Constructeur de copie
    ~XmlFileSerializerException() override;  // Destructeur

    int getCode() const;
    void setCode(int co);
};
}

#endif