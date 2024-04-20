

#include <functional>
#include <map>
#include <utility>

#include "Config.hpp"

#include "../include/WorkWithFile.hpp"
#include "../include/ExceotionError.hpp"

#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

// *  текстовый формат называется CPPON -> C++ Object Notation

static const string filename_release = "db_students.txt";

struct Student
{
    string name;
    string surname;
    wchar_t gender;
    unsigned short age;
    unsigned curse;
};

[[nodiscard]] string CreateStudentInString(const map<int, Student>& students)
{
    wstring text;
    for (auto [i, student] : students)
    {
        text += L"Студент" + to_wstring(i) + L": структура (\n"
            + L"\tфамилия: строка = \"" + ConvertString(student.surname) + L"\",\n"
            + L"\tимя: строка = \"" + ConvertString(student.name) + L"\",\n"
            + L"\tпол: символ = \'" + student.gender + L"\',\n"
            + L"\tвозраст: число = " + to_wstring(student.age) + L",\n"
            + L"\tкурс: число = " + to_wstring(student.curse) + L",\n"
            + L");\n";
    }
    return ConvertWstring(text);
}

[[nodiscard]] map<int, Student> UploadingData(const string& filename, const wstring& text)
{
    Lexer l(ReadFile(filename));
    Parser parser(l.test_func());

    unsigned si = stoi(ConvertWstring(wstring(1, text[text.find(L"Студент") + 7])));

    map<int, Student> students;
    const wstring name = L"Студент";
    for (int i = 0; i < parser.getSize(); i++)
    {
        wstring nameStructe = name + to_wstring(i + si);
        students[i + si].name = ConvertWstring(parser.getStructureByKey(nameStructe).getVal<wstring>(L"имя"));
        students[i + si].surname = ConvertWstring(parser.getStructureByKey(nameStructe).getVal<wstring>(L"фамилия"));
        students[i + si].gender = parser.getStructureByKey(nameStructe).getVal<wchar_t>(L"пол");
        students[i + si].age = parser.getStructureByKey(nameStructe).getVal<int>(L"возраст");
        students[i + si].curse = parser.getStructureByKey(nameStructe).getVal<int>(L"курс");
    }

    return students;
}

void printStudent(const map<int, Student>& students)
{
    cout << "\nВывод данныч:\n";
    for (auto [i, student] : students)
    {
        cout << "Структура - Студент" << i
             << "\n   имя - " << student.name
             << "\n   фамилия - " << student.surname
             << "\n   пол - " << ConvertWstring(wstring(1, student.gender))
             << "\n   возраст - " << student.age
             << "\n   курс - " << student.curse
             << "\n";
    }

    cout << '\n';
}

void printDataFile(const string& filename, const wstring& text)
{
    printStudent(UploadingData(filename, text));
}


template<typename T>
[[nodiscard]] T Input(const string& text)
{
    cout << text << ' ';

    T io;
    cin >> io;

    return io;
}

template<typename T>
[[nodiscard]] const T& CheckOncondition(const T& data, 
    const function<bool(const T&)>& func)
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

        wstring text = ReadFile(filename);

        unsigned short int size_input;
        cout << "\nСколько данных по студенту ввести: ";
        cin >> size_input;

        unsigned si = stoi(ConvertWstring(wstring(1, text[text.rfind(L"Студент") + 7])));

        for (int i = 1; i < size_input + 1; i++)
        {
            cout << "Структура - " << i << '\n';
            
            text += L"Студент" + to_wstring( si + i) + L": структура (\n"
                + L"\tфамилия: строка = \"" + ConvertString(Input<string>("Имя:")) + L"\",\n"
                + L"\tимя: строка = \"" + ConvertString(Input<string>("Фамилия:")) + L"\",\n"
                + L"\tпол: символ = \'" + ConvertString(Input<string>("Пол:")) + L"\',\n"
                + L"\tвозраст: число = " + to_wstring(CheckOncondition<unsigned short>(Input<unsigned short>("Возраст:"), test_func)) + L",\n"
                + L"\tкурс: число = " + to_wstring(CheckOncondition<unsigned>(Input<unsigned>("Курс:"), test_func_)) + L",\n"
                + L");\n";
                
            cout << '\n';
        }

        WriteFile(filename_release, ConvertWstring(text));
    }
    catch (const exception& ex)
    {
        cout << ex.what() << '\n';
    }
}

void sort(const string& filename,
    const function<bool(Student fr, Student scd)>& func,
    map<int, Student>& students)
{
    bool swapped;
    for (int i = 0; i < students.size() - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < students.size() - i - 1; j++)
        {
            if (func(students[j], students[j + 1]))
            {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    WriteFile(filename, CreateStudentInString(students));
}

[[nodiscard]] pair<int, int> findCurseWithLargestCountMan(map<int, Student>&& students)
{
    int max = 0, ind = 0;
    for (int i = 1; i < 6; i++)
    {
        int count = 0;
        for (auto [j, student] : students)
        {
            if (i  == student.curse && (student.gender == L'м' || student.gender == L'М'))
            {   
                count++;
            }
        }

        if (count > max)
        {
            max = count;
            ind = i;
        }
    }

    return make_pair(max, ind);
}

[[nodiscard]] map<int, Student> printGenderAndCurse(const map<int, Student>& students)
{
    string gender = Input<string>("Введите пол студента: ");
    int curse = Input<int>("Введите курс студента: ");

    map<int, Student> printStudent;
    for (auto& [i, student] : students)
        if (student.gender == ConvertString(gender)[0] && student.curse == curse)
            printStudent[i] = student;
    return printStudent;
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

    const wstring text = ReadFile(filename_release);
    map<int, Student> students = UploadingData(filename_release, text);

    bool te = true;    
    do {
        switch (tes()) {
            case 1:
                printStudent(students);
                break;
            case 2:
            case 3:
                inputDataInFile(filename_release);
                break;
            case 4:
                sort(filename_release, [](Student fr, Student scd)
                {
                    return fr.surname > scd.surname;
                }, students);
                printStudent(students);
                break;
            case 5:
                sort(filename_release, [](Student fr, Student scd)
                {
                    return fr.age > scd.age;
                }, students);
                printStudent(students);
                break;
            case 6:
            {
                pair te = findCurseWithLargestCountMan(std::move(students));
                cout << "Количество мужчин - " << te.first 
                     << "; курс - " << te.second << '\n';
                break;
            }
            case 7:
                printStudent(printGenderAndCurse(students));
                break;
            case 0:
                te = false;
                break;
            default:
                cout << "Not num\n";
        }
    } while(te);

    return 0;
}

