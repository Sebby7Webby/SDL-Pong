#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include "log.h"
using namespace std;

Log::Log(std::string _dir, bool erase=false) {
    if (erase) {
        dir = ofstream(_dir);
        firstClock = clock();
        dir.clear();
    } else {
        dir = ofstream(_dir);
        firstClock = clock();
    }
    dir << "Script started: 0.00\n";
    dir << "----------------------------------------------------------------------------------------------------\n";
}

Log::~Log() {
    dir << "----------------------------------------------------------------------------------------------------\n";
    dir << "Script ended: " << getTime() << '\n';
    dir.close();
}

std::string Log::getTime() {
    clock_t time = clock();
    float getTime;
    getTime = (float)(time - firstClock)/(float)CLOCKS_PER_SEC;

    std::stringstream ss;
    ss << getTime;

    return ss.str();
} 

void Log::logNote(std::string txt) {
    dir << getTime() << " | " << txt << '\n';
}