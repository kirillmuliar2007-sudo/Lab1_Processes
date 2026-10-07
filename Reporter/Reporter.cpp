#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    string bin_filename = argv[1];
    string report_filename = argv[2];
    double hourly_rate = stod(argv[3]);

    ifstream in(bin_filename, ios::binary);
    if (!in) {
        cout << "Ошибка Reporter. Не удалось открыть бинарный файл" << endl;
        return 1;
    }
    ofstream out(report_filename);
    if (!out) {
        cout << "Ошибка Reporter. Не удалось открыть файл - отчет" << endl;
        return 1;
    }
    out << "Отчет по файлу \"" << bin_filename << "\"\n";
    out << "Номер сотрудника, имя сотрудника, часы, зарплата.\n";
    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * hourly_rate;
        out << emp.num << ", "
            << emp.name << ", "
            << emp.hours << ", "
            << fixed << setprecision(2) << salary << "\n";
    }
    in.close();
    out.close();
    return 0;
}