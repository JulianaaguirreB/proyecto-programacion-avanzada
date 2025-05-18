#include <iostream>
#include <vector>
#include <chrono>
#include "csv_utils.h"
#include "analysis_utils.h"
#include "student_utils.h"
#include "EnvLoader.h"
#include "SFTPClient.h"

using namespace std;
using namespace std::chrono;

int main() {
    loadEnv();

    string remotePath = "/remote/Admission_Predict.csv";
    string localPath = "Admission_Predict.csv";
    if (!downloadCSVFromSFTP(remotePath, localPath)) {
        cerr << "Error al descargar el archivo CSV desde el servidor SFTP." << endl;
        return 1;
    }

    auto t1 = high_resolution_clock::now();
    Table table = readCSV(localPath);
    auto t2 = high_resolution_clock::now();
    cout << "Tiempo de lectura del CSV: " << duration_cast<milliseconds>(t2 - t1).count() << " ms\n";
    cin.ignore(); cin.get();

    int option;
    do {
        cout << "\n--- MENÚ DE ANÁLISIS ---\n";
        cout << "1. Información general\n";
        cout << "2. Ver primeras N filas\n";
        cout << "3. Estadísticas descriptivas\n";
        cout << "4. Matriz de correlación\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> option;

        switch (option) {
            case 1:
                printInfo(table);
                break;
            case 2: {
                int n;
                cout << "¿Cuántas filas desea ver?: ";
                cin >> n;
                printHead(table, n);
                break;
            }
            case 3:
                printDescribe(table);
                break;
            case 4:
                printCorrelation(table);
                break;
            case 0:
                cout << "Saliendo del menú...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
        cin.ignore(); cin.get();
    } while (option != 0);

    auto t3 = high_resolution_clock::now();
    saveAnalysisToTxt(table, "data/transformacion_resultados.txt");
    auto t4 = high_resolution_clock::now();
    cout << "Tiempo de guardado del análisis: " << duration_cast<milliseconds>(t4 - t3).count() << " ms\n";
    cin.ignore(); cin.get();

    auto t5 = high_resolution_clock::now();
    vector<Student> students = convertTableToStudents(table);
    writeStudentsBinary(students, "data/Admission_Predict_new.bin");
    auto t6 = high_resolution_clock::now();
    cout << "Tiempo de escritura binaria: " << duration_cast<milliseconds>(t6 - t5).count() << " ms\n";
    cin.ignore(); cin.get();

    readStudentsBinary("data/Admission_Predict_new.bin", 3, 3);
    return 0;
}

