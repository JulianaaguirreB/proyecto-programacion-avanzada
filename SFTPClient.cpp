#include "SFTPClient.h"
#include <iostream>

bool downloadCSVFromSFTP(const std::string& remotePath, const std::string& localPath) {
    // Este es un mock. Aquí iría el código real de conexión SFTP.
    std::cout << "[Mock] Descargando " << remotePath << " a " << localPath << std::endl;
    return true;
}
