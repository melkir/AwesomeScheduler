#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
private:
    std::string _name;

public:
    Process(const std::string &name);

    bool resume() const;

    bool suspend() const;
};

#endif
