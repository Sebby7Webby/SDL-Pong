#ifndef LOG_H
#define LOG_H

#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Log {
public:
    Log(std::string _dir, bool erase);
    ~Log();
    
    void logNote(std::string txt);
    std::string getTime();
private:
    ofstream dir;
    clock_t firstClock;
};

#endif