#pragma once
#include "csv_utils.h"

void printInfo(const Table& table);
void printHead(const Table& table, int n);
void printDescribe(const Table& table);
void printCorrelation(const Table& table);
void saveAnalysisToTxt(const Table& table, const std::string& filename);
