#ifndef EVENT_H
#define EVENT_H

#include "Timing.h"
#include "TimingException.h"

namespace planning {

class Event 
{
  private:
    int code;
    char* title;
    Timing* timing;

  public:
    static int currentCode;
    Event() noexcept;
    // Constructeur d'initialisation
    Event(int c, const char* t);
    // Constructeur de copie
    Event(const Event& e) noexcept;
    ~Event() noexcept;

    int getCode() const;
    const char* getTitle() const;
    Timing getTiming() const;

    void setCode(int c);
    void setTitle(const char* t);
    void setTiming(const Timing& t);

    friend ostream& operator<<(ostream& os, const Event& t);
    friend istream& operator>>(istream& is, Event& t);

    void display() const ;
    string toString() const;
};
}
#endif