#include "TimeException.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

namespace planning {

TimeException::TimeException() {
    setMessage("Time Error");
    setCode(0);
}

TimeException::TimeException(const string& msg, int code) {
    setMessage(msg);
    setCode(code);
}

TimeException::TimeException(const TimeException& other) {
    setMessage(other.getMessage());
    setCode(other.getCode());
}

TimeException::~TimeException() {
    
}

int TimeException::getCode() const {
    return code;
}

void TimeException::setCode(int co) {
    code = co;
}

}