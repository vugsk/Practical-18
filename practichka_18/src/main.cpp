
#include <iostream>

// #include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

// текстовый формат называется CPPON -> C++ Object Notation

// Parser.hpp
//      написать парсер который будет из вектора делать чуда
//
// Exception.hpp
//      написать оброботчик ошибок
//
// после проделанной работы можно приступать к работе над заданием
//
// WorkFile.hpp
//      переделать на использование wstring
//
// переписать, то что осталось и продолжить идти по под задачам
//
// предположительно мне нужно часов 24-48 в днях где-то 3-10 дней

struct Node
{
    int data = 0;
    char pos = 0;
    unique_ptr<Node> next;
    unique_ptr<Node> left;
};

unique_ptr<Node> CreateNode(const int data, const char ch = 'C')
{
    return make_unique<Node>(data, ch, nullptr, nullptr);
}

void AddNode(const unique_ptr<Node>& root, const int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
    {
        if (root->next == nullptr)
        {
            root->next = CreateNode(data, 'N');
        }
        else
        {
            AddNode(root->next, data);
        }
    }
    else if (data > root->data)
    {
        if (root->left == nullptr)
        {
            root->left = CreateNode(data, 'L');
        }
        else
        {
            AddNode(root->left, data);
        }
    }
}

void PrintNodes(const unique_ptr<Node>& root)
{
    if (root == nullptr)
        return;

    wcout << "Data: " << root->data << ' ' << root->pos << '\n';

    if (root->next != nullptr)
        PrintNodes(root->next);

    if (root->left != nullptr)
        PrintNodes(root->left);

}



int main()
{
    setlocale(LC_CTYPE, "");

    const wstring filename = L"номер: число = 90;\nбуква: символ = \'ш\';"
            + wstring(L"\nтекст: строка = \"какой-то текст\";\n");

    std::wcout << L"Код:\n" << filename << '\n';

    const unique_ptr<Node> root = CreateNode(90);
    AddNode(root, 97);
    AddNode(root, 78);
    AddNode(root, 790);
    PrintNodes(root);
    // Lexer l(filename);
    // wcout << "Обработка лексера:\n";
    // for (const auto& i : l.lexicalCodeAnalysis())
    //     std::wcout << i->getToken() << ' ' << i->getValue() << '\n';
    //
    // wcout << "\nРабота парсера\n";



    return 0;
}

