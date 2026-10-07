#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
struct employee {
    int num;
    char name[10];
    double hours;
};
bool run_process(const string& cmd_line) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char* mutable_cmd = new char[cmd_line.length() + 1];
    strcpy_s(mutable_cmd, cmd_line.length() + 1, cmd_line.c_str());

    if (!CreateProcessA(
        NULL,
        mutable_cmd,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        delete[] mutable_cmd;
        return false;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    delete[] mutable_cmd;
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string bin_file;
    int records_count;
    cout << "Введите имя бинарного файла: ";
    cin >> bin_file;
    cout << "Введите число сотрудников: ";
    cin >> records_count;
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string exe_path(buffer);
    string current_dir = exe_path.substr(0, exe_path.find_last_of("\\/") + 1);
    string creator_cmd = "\"" + current_dir + "Creator.exe\" " + bin_file + " " + to_string(records_count);

    if (!run_process(creator_cmd)) {
        cout << "Ошибка. Creator.exe не запустился" << endl;
        return 1;
    }
    ifstream bin_in(bin_file, ios::binary);
    if (bin_in) {
        cout << "\n Содержимое бинарного файла: \n";
        employee emp;
        while (bin_in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
            cout << "ID: " << emp.num << ", Имя: " << emp.name << ", Часы: " << emp.hours << "\n";
        }
        bin_in.close();
    }
    string report_file;
    double hourly_rate;
    cout << "\nВведите название файла отчета: ";
    cin >> report_file;
    cout << "Введите оплату за час работы: ";
    cin >> hourly_rate;
    string reporter_cmd = "\"" + current_dir + "Reporter.exe\" " + bin_file + " " + report_file + " " + to_string(hourly_rate);

    if (!run_process(reporter_cmd)) {
        cout << "Ошибка. Reporter.exe не запустился" << endl;
        return 1;
    }
    ifstream report_in(report_file);
    if (report_in) {
        cout << "\nСодержимое файла - отчета: \n";
        string line;
        while (getline(report_in, line)) {
            cout << line << "\n";
        }
        report_in.close();
    }
    return 0;
}