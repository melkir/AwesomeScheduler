#ifndef AWESOMESCHEDULER_TASKPROPERTIES_H
#define AWESOMESCHEDULER_TASKPROPERTIES_H

#include <string>
#include <iostream>

using namespace std;

class TaskProperties {
    friend std::ostream &operator<<(std::ostream &out, const TaskProperties &task);
    friend std::istream &operator>>(std::istream &in, TaskProperties &task);

private:
    string m_proc;  // procedure name
    int m_profile;  // 1 = maths, 2 = disk, 3 = transactional
    string m_in;    // data coming from end-user
    string m_out;   // data sent back to end-user
    int m_disk;     // disk space
    int m_power;    // speed/power
    int m_cputime;  // total cpu used

public:
    TaskProperties() = default;

    TaskProperties(const string &proc, int profile, const string &in, const string &out, int disk,
                   int power, int cputime) : m_proc(proc), m_profile(profile), m_in(in), m_out(out), m_disk(disk),
                                             m_power(power), m_cputime(cputime) { }

    void load_buffer(const string &buffer);

    bool load(string filename);

    string save();

    string generateID();

    const int getPriority() const {
        return (m_disk + m_power + m_cputime) / 3;
    }

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

    bool operator<(const TaskProperties &rhs) const {
        return this->getPriority() < rhs.getPriority();
    }
};

#endif //AWESOMESCHEDULER_TASKPROPERTIES_H
