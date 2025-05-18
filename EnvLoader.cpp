#include "EnvLoader.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

void loadEnv() {
    std::ifstream envFile(".env");
    std::string line;

    while (std::getline(envFile, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos) {
            std::string key = line.substr(0, eqPos);
            std::string value = line.substr(eqPos + 1);

            // Elimina espacios alrededor
            key.erase(0, key.find_first_not_of(" \t\r\n"));
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);

#ifdef _WIN32
            std::string assignment = key + "=" + value;
_putenv(assignment.c_str());

#else
            setenv(key.c_str(), value.c_str(), 1);
#endif
        }
    }
}

std::string getEnvVar(const std::string& var) {
    const char* val = std::getenv(var.c_str());
    return val == nullptr ? "" : std::string(val);
}

