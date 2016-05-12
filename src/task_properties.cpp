#include "task_properties.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

namespace pt = boost::property_tree;

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

bool TaskProperties::load(string filename) {
    if (!boost::filesystem::exists(filename)) {
        cerr << "File " << filename << " doesn't exist !" << endl;
        return false;
    }
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
    return true;
}

void TaskProperties::load_buffer(const string &buffer) {
    cout << buffer << endl;
    // write the task to a temporary file in order to load the task
    string tmp_file = boost::filesystem::unique_path().native() + ".xml";
    ofstream outf(tmp_file);
    if (!outf) {
        cerr << "Temp file " << tmp_file << " cannot can not be opened for writing." << endl;
        exit(1);
    }
    outf << buffer;
    outf.flush();
    load(tmp_file);
    // delete the tmp file after load
    unlink(tmp_file.c_str());
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

    string task_path, task_id;
    task_id = generateID();
    task_path = task_id + ".xml";
    // Write property tree to XML file
    pt::write_xml(task_path, tree, std::locale(), pt::xml_writer_make_settings<string>(' ', 4));

    cout << task_id << " successfully created" << endl;
    return task_path;
}

string TaskProperties::generateID() {
    // static duration via static keyword. This line is only executed once.
    static int s_itemID = 1;
    // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
    string task_number = to_string(s_itemID++);
    // generate unique id for multi-threading
    string unique_id = boost::filesystem::unique_path().native();
    return "task" + task_number + "_" + unique_id;
}

void TaskProperties::print() const {
    cout << "proc\t= " << m_proc << '\n'
    << "profile\t= " << m_profile << '\n'
    << "in\t= " << m_in << '\n'
    << "out\t= " << m_out << '\n'
    << "disk\t= " << m_disk << '\n'
    << "power\t= " << m_power << '\n'
    << "cputime\t= " << m_cputime << endl;
}





















