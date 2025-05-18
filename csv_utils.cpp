#include "csv_utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Table readCSV(const string& filename) {
    Table table;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ',')) {
            // Limpieza de espacios extra adelante y atrás
            cell.erase(cell.begin(), find_if(cell.begin(), cell.end(), [](int ch) { return !isspace(ch); }));
            cell.erase(find_if(cell.rbegin(), cell.rend(), [](int ch) { return !isspace(ch); }).base(), cell.end());
            row.push_back(cell);
        }

        // Limpiar encabezados (solo la primera fila)
        if (table.empty()) {
            for (auto& col : row) {
                for (auto& ch : col) {
                    if (ch == ' ') ch = '_';
                }
            }
        }

        table.push_back(row);
    }

    return table;
}

