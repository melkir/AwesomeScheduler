#include "task_properties.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

namespace pt = boost::property_tree;

TaskProperties::TaskProperties(const string &proc, int profile, const string &in, const string &out, int disk,
                               int power, int cputime) :
        m_proc(proc), m_profile(profile), m_in(in), m_out(out), m_disk(disk), m_power(power),
        m_cputime(cputime) { }

void TaskProperties::init() {
    cout << "proc=";
    cin >> m_proc;
    cout << "profile=";
    cin >> m_profile;
    cout << "in=";
    cin >> m_in;
    cout << "out=";
    cin >> m_out;
    cout << "disk=";
    cin >> m_disk;
    cout << "power=";
    cin >> m_power;
    cout << "cputime=";
    cin >> m_cputime;
}

void TaskProperties::load(const string &filename) {
    // Create empty property tree object
    pt::ptree tree;

    // Parse the XML into the property tree.
    pt::read_xml(filename, tree);
    m_proc = tree.get<string>("task.proc");
    m_profile = tree.get<int>("task.profile");
    m_in = tree.get<string>("task.in");
    m_out = tree.get<string>("task.out");
    m_disk = tree.get<int>("task.disk");
    m_power = tree.get<int>("task.power");
    m_cputime = tree.get<int>("task.cputime");
}

string TaskProperties::save() {
    // Create empty property tree object
    pt::ptree tree;

    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "task" node is automatically
    // created if it doesn't exist.
    tree.put("task.proc", m_proc);
    tree.put("task.profile", m_profile);
    tree.put("task.in", m_in);
    tree.put("task.out", m_out);
    tree.put("task.disk", m_disk);
    tree.put("task.power", m_power);
    tree.put("task.cputime", m_cputime);

    boost::filesystem::path temp = boost::filesystem::unique_path();
    const std::string tempstr = temp.native();

    // Write property tree to XML file with indent
    pt::write_xml(tempstr, tree, std::locale(), pt::xml_writer_make_settings<string>(' ', 4));

    cout << "Task " << tempstr << " successfully created";
    return tempstr;
}

std::ostream &operator<<(std::ostream &os, const TaskProperties &tp) {
    return os << "proc\t= " << tp.m_proc << '\n'
           << "profile\t= " << tp.m_profile << '\n'
           << "in\t= " << tp.m_in << '\n'
           << "out\t= " << tp.m_out << '\n'
           << "disk\t= " << tp.m_disk << '\n'
           << "power\t= " << tp.m_power << '\n'
           << "cputime\t= " << tp.m_cputime;
}



