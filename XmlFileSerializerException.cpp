#include "XmlFileSerializerException.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

namespace planning {

XmlFileSerializerException::XmlFileSerializerException() {
    setMessage("Xml File Serializer Error");
    setCode(0);
}

XmlFileSerializerException::XmlFileSerializerException(int code) {
    setMessage("Xml File Serializer Error");
    setCode(code);
}

XmlFileSerializerException::XmlFileSerializerException(const XmlFileSerializerException& other) {
    setMessage(other.getMessage());
    setCode(other.getCode());
}

XmlFileSerializerException::~XmlFileSerializerException() {

}

int XmlFileSerializerException::getCode() const {
    return code;
}

void XmlFileSerializerException::setCode(int co) {
    code = co;
}
}