#include "task_properties.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

namespace pt = boost::property_tree;

TaskProperties::TaskProperties(const string &m_proc, int m_profile, const string &m_in, const string &m_out, int m_disk,
                               int m_power, int m_cputime) :
        m_proc(m_proc), m_profile(m_profile), m_in(m_in), m_out(m_out), m_disk(m_disk), m_power(m_power),
        m_cputime(m_cputime) { }

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
    cout << "Task successfully created";
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
    // Create an empty property tree object.
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

    return tempstr;
}

std::ostream &operator<<(std::ostream &os, const TaskProperties &t) {
    return os << "proc\t= " << t.m_proc << '\n'
           << "profile\t= " << t.m_profile << '\n'
           << "in\t= " << t.m_in << '\n'
           << "out\t= " << t.m_out << '\n'
           << "disk\t= " << t.m_disk << '\n'
           << "power\t= " << t.m_power << '\n'
           << "cputime\t= " << t.m_cputime;
}

/*
int main() {
    try {
        TaskProperties t_prop;
        string path;
        cout << "Enter the path to the xml file : ";
        cin >> path;
        t_prop.load(path);
        cout << t_prop << endl;
        path = path.substr(0, path.size() - 4); // remove the xml extension
        t_prop.save(path + "_copy.xml"); // and add _copy.xml at the end
        cout << "Success" << endl;
    }
    catch (std::exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
*/



