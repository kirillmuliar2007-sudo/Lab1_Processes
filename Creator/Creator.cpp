#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string filename = argv[1];
    int records_count = stoi(argv[2]);
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Ошибка. Не удалось открыть файл Creator" << filename << endl;
        return 1;
    }
    for (int i = 0; i < records_count; ++i) {
        employee emp;
        cout << " Сотрудник " << (i + 1) << " \n";
        cout << "Введите ID: ";
        cin >> emp.num;
        cout << "Введите имя (до 9 символов): ";
        cin >> emp.name;
        cout << "Введите отработанные часы: ";
        cin >> emp.hours;
        out.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }
    out.close();
    return 0;
}