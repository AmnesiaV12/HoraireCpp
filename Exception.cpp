#include "Exception.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Exception::Exception() {
    setMessage("Erreur");
}

Exception::Exception(const string& msg) {
    setMessage(msg);
}

Exception::Exception(const Exception& other) {
    setMessage(other.getMessage());
}

Exception::~Exception() {
    
}

void Exception::setMessage(const string& msg) {
    message = msg;
}

string Exception::getMessage() const {
    return message;
}