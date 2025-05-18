#include <fstream>
#include <iostream>
#include <vector>
#include "student_utils.h"

using namespace std;

vector<Student> convertTableToStudents(const Table& table) {
    vector<Student> students;
    for (size_t i = 1; i < table.size(); ++i) {
        Student s;
        s.serialNo = stoi(table[i][0]);
        s.greScore = stoi(table[i][1]);
        s.toeflScore = stoi(table[i][2]);
        s.universityRating = stoi(table[i][3]);
        s.sop = stof(table[i][4]);
        s.lor = stof(table[i][5]);
        s.cgpa = stof(table[i][6]);
        s.research = stoi(table[i][7]);
        s.chanceOfAdmit = stof(table[i][8]);
        students.push_back(s);
    }
    return students;
}

void writeStudentsBinary(const vector<Student>& students, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = students.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& s : students) {
        out.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }
}
void readStudentsBinary(const string& filename, int headCount, int tailCount) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "No se pudo abrir el archivo binario." << std::endl;
        return;
    }

    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    vector<Student> students(size);
    for (size_t i = 0; i < size; ++i) {
        in.read(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }

    cout << "\nHEAD (" << headCount << " registros):\n";
    for (int i = 0; i < min(headCount, static_cast<int>(size)); ++i) {
    cout << students[i].serialNo << " "
                  << students[i].greScore << " "
                  << students[i].toeflScore << " "
                  << students[i].universityRating << " "
                  << students[i].sop << " "
                  << students[i].lor << " "
                  << students[i].cgpa << " "
                  << students[i].research << " "
                  << students[i].chanceOfAdmit << "\n";
    }

    cout << "\nTAIL (" << tailCount << " registros):\n";
    for (int i = max(0, static_cast<int>(size) - tailCount); i < static_cast<int>(size); ++i) {
        cout << students[i].serialNo << " "
                  << students[i].greScore << " "
                  << students[i].toeflScore << " "
                  << students[i].universityRating << " "
                  << students[i].sop << " "
                  << students[i].lor << " "
                  << students[i].cgpa << " "
                  << students[i].research << " "
                  << students[i].chanceOfAdmit << "\n";
    }
}

