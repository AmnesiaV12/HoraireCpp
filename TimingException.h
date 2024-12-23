#ifndef TIMINGEXCEPTION_H
#define TIMINGEXCEPTION_H

#include "Exception.h"
#include <iostream>
#include <string>
using namespace std;

namespace planning {

class TimingException : public Exception {
private:
    int code;

public:
    static const int INVALID_DAY = 1;
    static const int NO_TIMING = 2;

    TimingException();
    TimingException(const string& msg, int code);
    TimingException(const TimingException& other);
    ~TimingException() override;

    int getCode() const;
    void setCode(int co);
};
}
#endif