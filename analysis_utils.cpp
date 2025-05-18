#include "analysis_utils.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
int toInt(const string& s) {
    return stoi(s);
}

float toFloat(const string& s) {
    return stof(s);
}

void printInfo(const Table& table) {
    cout << "Filas: " << table.size() - 1 << ", Columnas: " << table[0].size() << "\n";
    cout << "Columnas: ";
    for (const auto& name : table[0]) cout << name << " | ";
    cout << "\n";
}

void printHead(const Table& table, int n) {
    for (int i = 0; i <= n && i < table.size(); ++i) {
        for (const auto& cell : table[i]) std::cout << cell << "\t";
        cout << "\n";
    }
}

void printDescribe(const Table& table) {
    int cols = table[0].size();
    int rows = table.size() - 1;
    for (int j = 1; j < cols; ++j) {
        float sum = 0, sum_sq = 0, min = toFloat(table[1][j]), max = min;
        for (int i = 1; i < table.size(); ++i) {
            float val = toFloat(table[i][j]);
            sum += val;
            sum_sq += val * val;
            if (val < min) min = val;
            if (val > max) max = val;
        }
        float mean = sum / rows;
        float stddev = sqrt((sum_sq / rows) - (mean * mean));
        cout << table[0][j] << ": Media=" << mean << ", StdDev=" << stddev
                  << ", Min=" << min << ", Max=" << max << "\n";
    }
}

void printCorrelation(const Table& table) {
    int cols = table[0].size();
    int rows = table.size() - 1;
    cout << fixed << setprecision(2);
    for (int a = 1; a < cols; ++a) {
        for (int b = 1; b < cols; ++b) {
            float sumA = 0, sumB = 0, sumAB = 0, sumA2 = 0, sumB2 = 0;
            for (int i = 1; i < table.size(); ++i) {
                float x = toFloat(table[i][a]);
                float y = toFloat(table[i][b]);
                sumA += x; sumB += y; sumAB += x*y; sumA2 += x*x; sumB2 += y*y;
            }
            float num = sumAB - (sumA * sumB) / rows;
            float den = std::sqrt((sumA2 - (sumA * sumA) / rows) * (sumB2 - (sumB * sumB) / rows));
            float corr = (den != 0) ? num / den : 0;
            cout << corr << "\t";
        }
        cout << "\n";
    }
}

void saveAnalysisToTxt(const Table& table, const string& filename) {
    ofstream file(filename);

    // Información general
    file << "Filas: " << table.size() - 1 << ", Columnas: " << table[0].size() << "\n";
    file << "Columnas: ";
    for (const auto& name : table[0]) file << name << " | ";
    file << "\n\n";

    // Estadísticas descriptivas
    file << "== Estadísticas descriptivas ==\n";
    for (int j = 1; j < table[0].size(); ++j) {
        float sum = 0, sum_sq = 0, min = toFloat(table[1][j]), max = min;
        for (size_t i = 1; i < table.size(); ++i) {
            float val = toFloat(table[i][j]);
            sum += val;
            sum_sq += val * val;
            if (val < min) min = val;
            if (val > max) max = val;
        }
        float mean = sum / (table.size() - 1);
        float stddev = sqrt((sum_sq / (table.size() - 1)) - (mean * mean));
        file << table[0][j] << ": Media=" << mean
             << ", StdDev=" << stddev
             << ", Min=" << min
             << ", Max=" << max << "\n";
    }

    // Matriz de correlación de Pearson
    file << "\n== Matriz de correlación de Pearson ==\n";
    int cols = table[0].size();
    int rows = table.size() - 1;

    for (int a = 1; a < cols; ++a) {
        for (int b = 1; b < cols; ++b) {
            float sumA = 0, sumB = 0, sumAB = 0, sumA2 = 0, sumB2 = 0;
            for (int i = 1; i < table.size(); ++i) {
                float x = toFloat(table[i][a]);
                float y = toFloat(table[i][b]);
                sumA += x; sumB += y; sumAB += x*y; sumA2 += x*x; sumB2 += y*y;
            }
            float num = sumAB - (sumA * sumB) / rows;
            float den = sqrt((sumA2 - (sumA * sumA) / rows) * (sumB2 - (sumB * sumB) / rows));
            float corr = (den != 0) ? num / den : 0;
            file << corr << "\t";
        }
        file << "\n";
    }

    file.close();
}

