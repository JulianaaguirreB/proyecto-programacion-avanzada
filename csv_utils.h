#pragma once
#include <vector>
#include <string>
using namespace std;
using Table = vector<vector<string>>;

Table readCSV(const string& filename);
