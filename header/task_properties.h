#ifndef AWESOMESCHEDULER_TASKPROPERTIES_H
#define AWESOMESCHEDULER_TASKPROPERTIES_H

#include <string>
#include <iostream>
#include <set>

using namespace std;

class TaskProperties {
private:
    string m_proc;  // procedure name
    int m_profile;  // 1 = maths, 2 = disk, 3 = transactional
    string m_in;    // data coming from end-user
    string m_out;   // data sent back to end-user
    int m_disk;     // disk space
    int m_power;    // speed/power
    int m_cputime;  // total cpu used

public:
    TaskProperties() { }

    TaskProperties(const string &m_proc, int m_profile, const string &m_in, const string &m_out, int m_disk,
                   int m_power, int m_cputime);

    void load(const string &filename);

    void save(const string &filename);

    const string &getProcedureName() const { return m_proc; }

    void setProcedureName(const string &proc) { m_proc = proc; }

    int getProfile() const { return m_profile; }

    void setProfile(int profile) { m_profile = profile; }

    const string &getIn() const { return m_in; }

    void setIn(const string &in) { m_in = in; }

    const string &getOut() const { return m_out; }

    void setOut(const string &out) { m_out = out; }

    int getDisk() const { return m_disk; }

    void setDisk(int disk) { m_disk = disk; }

    int getPower() const { return m_power; }

    void setPower(int power) { m_power = power; }

    int getCpuTime() const { return m_cputime; }

    void setCpuTime(int cputime) { m_cputime = cputime; }

    friend std::ostream &operator<<(std::ostream &os, const TaskProperties &t);

};


#endif //AWESOMESCHEDULER_TASKPROPERTIES_H
