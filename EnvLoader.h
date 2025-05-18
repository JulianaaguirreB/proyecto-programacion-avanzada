#pragma once
#include <string>

void loadEnv(); // Carga variables de entorno desde .env (mock)
std::string getEnvVar(const std::string& var);
