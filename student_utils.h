#pragma once
#include "csv_utils.h"
#include <vector>
#include <string>
using namespace std;
struct Student {
    int serialNo;
    int greScore;
    int toeflScore;
    int universityRating;
    float sop;
    float lor;
    float cgpa;
    int research;
    float chanceOfAdmit;
};

vector<Student> convertTableToStudents(const Table& table);
void writeStudentsBinary(const vector<Student>& students, const string& filename);
void readStudentsBinary(const std::string& filename, int headCount, int tailCount);

