
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <vector>

#include "Config.hpp"

#include "../include/ExceotionError.hpp"

#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

// *  текстовый формат называется CPPON -> C++ Object Notation

static const string filename_release = "db_students.txt";

[[nodiscard]] wstring read_file_test(const string& filename)
{
    ifstream file(filename, ios::binary);

    if (!file.is_open())
    {
        puts("ERROR: NOT OPEN FILE");
        exit(EXIT_FAILURE);
    }

    const long size = file.seekg(0, ios::end).tellg();
    file.seekg(0);

    string te;
    te.resize(size);
    file.read(&te[0], size);

    file.close();
    return ConvertString(te);
}

struct Student
{
    string name;
    string surname;
    wchar_t gender;
    unsigned short age;
    unsigned curse;

    friend bool operator>(Student fr, Student snd)
    {
        return fr.name > snd.name;
    }
};

static string FILENAME;
vector<Student> UploadingData(const string& filename)
{
    vector<Student> students;

    Lexer l(read_file_test(filename));
    Parser parser(l.test_func());

    const wstring name = L"Студент";
    for (int i = 0; i < parser.getSize(); i++)
    {
        wstring nameStructe = name + to_wstring(i);
        students[i].name = ConvertWstring(parser.get_test_func_structe(nameStructe).getVal<wstring>(L"имя"));
        students[i].surname = ConvertWstring(parser.get_test_func_structe(nameStructe).getVal<wstring>(L"фамилия"));
        students[i].gender = parser.get_test_func_structe(nameStructe).getVal<wchar_t>(L"пол");
        students[i].age = parser.get_test_func_structe(nameStructe).getVal<int>(L"возраст");
        students[i].curse = parser.get_test_func_structe(nameStructe).getVal<int>(L"курс");
    }

    return students;
}

void printDataFile(const string& filename)
{
    Lexer l(read_file_test(filename));
    Parser parser(l.test_func());

    const wstring name = L"Студент";
    cout << "\nДанные из файла:\n";
    for (int i = 0; i < parser.getSize(); i++)
    {
        wstring nameStructe = name + to_wstring(i);
        cout << "Структура - " << ConvertWstring(nameStructe)
             << "\n   имя - " << ConvertWstring(parser.get_test_func_structe(nameStructe).getVal<wstring>(L"имя"))
             << "\n   фамилия - " << ConvertWstring(parser.get_test_func_structe(nameStructe).getVal<wstring>(L"фамилия"))
             << "\n   пол - " << ConvertWstring(wstring(1, parser.get_test_func_structe(nameStructe).getVal<wchar_t>(L"пол")))
             << "\n   возраст - " << parser.get_test_func_structe(nameStructe).getVal<int>(L"возраст")
             << "\n   курс - " << parser.get_test_func_structe(nameStructe).getVal<int>(L"курс") << '\n';
    }
    cout << '\n';
}

template<typename T>
[[nodiscard]] T test_te(const string& text)
{
    cout << text << ' ';

    T io;
    cin >> io;

    return io;
}

template<typename T>
void Write_file(const string& filename, const T& data)
{
    ofstream file(filename);

    if (!file.is_open())
        cout << "NOT OPEN FILE!!!";

    file << data;
    file.close();
}

template<typename T>
const T& test_func__(const T& data, const function<bool(const T&)>& func)
{
    return func(data) ? data : throw Error("ERROR!!! " + to_string(data));
}

void inputDataInFile(const string& filename)
{
    try
    {
        auto test_func = [](unsigned short data) -> bool
        {
            return data >= 16;
        };
        auto test_func_ = [](unsigned data) -> bool
        {
            return data > 0 && data <= 5;
        };

        wstring text = read_file_test(filename);

        unsigned short int size_input;
        cout << "\nСколько данных по студенту ввести: ";
        cin >> size_input;

        unsigned si = stoi(ConvertWstring(wstring(1, text[text.rfind(L"Студент") + 7])));

        for (int i = 1; i < size_input + 1; i++)
        {
            cout << "Структура - " << i << '\n';
            
            text += L"Студент" + to_wstring( si + i) + L": структура (\n"
                + L"\tфамилия: строка = \"" + ConvertString(test_te<string>("Имя:")) + L"\",\n"
                + L"\tимя: строка = \"" + ConvertString(test_te<string>("Фамилия:")) + L"\",\n"
                + L"\tпол: символ = \'" + ConvertString(test_te<string>("Пол:")) + L"\',\n"
                + L"\tвозраст: число = " + to_wstring(test_func__<unsigned short>(test_te<unsigned short>("Возраст:"), test_func)) + L",\n"
                + L"\tкурс: число = " + to_wstring(test_func__<unsigned>(test_te<unsigned>("Курс:"), test_func_)) + L",\n"
                + L");\n";
                
            cout << '\n';
        }

        Write_file(filename_release, ConvertWstring(text));
    }
    catch (const exception& ex)
    {
        cout << ex.what() << '\n';
    }
}

void sort_surname(const string& filename)
{
    vector<Student> students = UploadingData(filename);

    bool swapped;
    for (int i = 0; i < students.size() - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < students.size() - i - 1; j++)
        {
            if (students[j] > students[j + 1])
            {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

}

int main()
{
    setlocale(LC_ALL, "");

    auto tes = []() -> unsigned short
    {
        unsigned short ch;
        cout << "Выберете номер действия:\n"
            << "1 - загрузить все данные из файла на экран;\n"
            << "2 - ввести новые данные в файл;\n"
            << "3 - добавить данных в конец файла;\n"
            << "4 - сортировка базы данных по алфавиту (по фамилии);\n"
            << "5 - сортировка базы данных по возрасту;\n"
            << "6 - определить курс, на котором наибольший процент мужчин;\n"
            << "7 - вывод: список студентов пола X и курса Y;\n"
            << "0 - выход из программы.\n";
        cout << ": ";
        cin >> ch;
        return ch;
    };

    bool te = true;    
    do {
        switch (tes()) {
            case 1:
                printDataFile(filename_release);
                break;
            case 2:
            case 3:
                inputDataInFile(filename_release);
                break;
            case 4:
                sort_surname(filename_release);
                break;
            case 5:
            case 6:
            case 7:
                continue;
            case 0:
                te = false;
                break;
            default:
                cout << "Not num\n";
        }
    } while(te);

    return 0;
}

