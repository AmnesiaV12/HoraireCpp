#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H

#include "Exception.h"
#include <iostream>
#include <string>
using namespace std;

namespace planning {

class TimeException : public Exception {
private:
    int code;

public:
    static const int INVALID_HOUR = 1;
    static const int INVALID_MINUTE = 2;
    static const int OVERFLOW = 3;

    TimeException();
    TimeException(const string& msg, int code);
    TimeException(const TimeException& other);
    ~TimeException() override;

    int getCode() const;
    void setCode(int co);

};
}
#endif