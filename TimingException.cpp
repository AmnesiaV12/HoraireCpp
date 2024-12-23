#include "TimingException.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

namespace planning {

TimingException::TimingException() {
    setMessage("Timing error");
    setCode(0);
}

TimingException::TimingException(const string& msg, int code) {
    setMessage(msg);
    setCode(code);
}

TimingException::TimingException(const TimingException& other) {
    setMessage(other.getMessage());
    setCode(other.getCode());
}

TimingException::~TimingException() {
    
}

int TimingException::getCode() const {
    return code;
}

void TimingException::setCode(int co) {
    code = co;
}
}