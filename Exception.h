#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

    class Exception {
    protected:
        string message;

    public:
        Exception();
        Exception(const string& msg);
        Exception(const Exception& other);
        virtual ~Exception();

        void setMessage(const string& msg);

        string getMessage() const;

    };

#endif