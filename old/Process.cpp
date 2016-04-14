#include <iostream>
#include "Process.h"

using namespace std;

Process::Process(const std::string &name) : _name(name) { }

bool Process::resume() const {
    cout << "resuming " << _name << endl;
    return true;
}

bool Process::suspend() const {
    cout << "suspending " << _name << endl;
    return true;
}
