  #include <math.h>
#include <iostream>
using namespace std;
#include <string.h>

#include "Event.h"
#include "TimingException.h"

namespace planning {

int Event::currentCode = 1;

Event::Event() noexcept
{
  setCode(0);
  //setCode(currentCode++);
  title = nullptr;
  setTitle("default");
  timing = nullptr;
}

Event::Event(int c, const char* t)
{
  setCode(c);
  //setCode(currentCode++);
  title = nullptr;
  setTitle(t);
  timing = nullptr;
}

Event::Event(const Event& e) noexcept
{
  setCode(e.getCode());
  title = nullptr;
  setTitle(e.getTitle());
  if (e.timing != nullptr) 
  {
    timing = new Timing(*(e.timing));
  } 
  else 
  {
    timing = nullptr;
  }
}

Event::~Event() noexcept
{
if (title) delete title;
delete timing;
}

void Event::setCode(int c)
  {
    code = c;
  }
void Event::setTitle(const char* t) 
  {
    if (title) delete title;
    title = new char[strlen(t)+1];
    strncpy(title, t, 19);
  }
void Event::setTiming(const Timing& t) {
    if (timing) delete timing;
    timing = new Timing(t);
    
}
int Event::getCode() const 
  {
    return code;
  }
const char* Event:: getTitle() const 
  {
    return title;
  }
Timing Event::getTiming() const {
  if (timing == nullptr) {
      // Si aucun timing n'est spécifié, on lance une exception
      throw planning::TimingException("Aucun timing spécifié pour cet événement", planning::TimingException::NO_TIMING);
    }
    return *timing;
}

std::ostream& operator<<(std::ostream& os, const Event& t) {
    os << "<Event>\n";
    os << "<code>\n" << t.getCode() << "\n</code>\n";
    os << "<title>\n" << t.getTitle() << "\n</title>\n";
    if (t.timing != nullptr) {
        os << "<timing>\n";
        os << *t.timing;
        os << "</timing>\n";
    }
    os << "</Event>\n";
    return os;
}

istream& operator>>(istream& is, Event& t) {
    string line;
    int code = 0;
    //char* title;

    getline(is, line); // <Event>
    getline(is, line); // <code>
    getline(is, line); // 
    istringstream iss_code(line);
    if (!(iss_code >> code)) {
        is.setstate(ios::failbit);
        return is;
    }
    getline(is, line); // </code>
    getline(is, line); // <title>
    getline(is, line); // 
    t.setTitle(line.c_str()); // Définition du titre
    /*istringstream iss_title(line);
    if (!(iss_title >> title)) {
        is.setstate(ios::failbit);
        return is;
    }*/
    getline(is, line); // </title>
    getline(is, line); // <timing> / </Event>
    if (line == "<timing>") {
        t.timing = new Timing();
        is >> *(t.timing); // Lecture du Timing
        getline(is, line); // </timing>
    } else {
        t.timing = nullptr; // Si pas de <timing>, laisser le pointeur à null
    }
    getline(is, line); // </Event>

    t.setCode(code);
    //t.setTitle(title);
    return is;
}

void Event::display() const 
  {
    //cout << "Display class" << endl;
    //cout << "code=" << code << "title=" << title << endl;
    cout << code << ", " << title << endl;
    if (timing) {
        cout << ", Timing: ";
        timing->display();
    } else {
        cout << ", Timing: Not";
    }
  }

string Event::toString() const {
    return "Event[Code=" + to_string(getCode()) + ", Title=" + string(getTitle()) + (timing ? ", Timing=" + timing->toString() : ", Timing=Not Specified") + "]";
}
}