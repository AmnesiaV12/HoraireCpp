#ifndef GROUP_H
#define GROUP_H

#include "Schedulable.h"
#include <iostream>
#include <string>
using namespace std;

class Group : public Schedulable {
private:
    string name;

public:
    Group();
    Group(int id, const string& name);
    Group(const Group& other);

    ~Group() override;

    string getName() const;
    void setName(const string& n);

    string toString() const override;
    string tuple() const override;

    friend ostream& operator<<(ostream& os, const Group& g);

    Group& operator=(const Group& other);

    bool operator<(const Group& other) const;
};

#endif
