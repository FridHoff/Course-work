// Course work.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h> // For 
#include <conio.h> // For _getch()
using namespace std;  

int main()
{
    cout << "Choose option!\n";
    int menu=NULL;
    computer computer;
    
    while (menu != 54)
    {              
        cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
        cout << "1.Computer list\n";
        cout << "2.Add computer\n";
        cout << "3.\n";
        cout << "4.\n";
        cout << "5.\n";
        cout << "6. Exit\n";
        menu = _getch();
        switch (menu)
        {
        case 49: // 1.
            cout << "\033[2J\033[1;1H"; 
            cout << "Computer list\n";
            
            break;
        case 50: // 2.                        
                cout << "\033[2J\033[1;1H"; 
                cout << "Please enter the following data:\n";
                cout << "Brand";
                cin >> computer.brand;
                cout << "\033[2J\033[1;1H";
                cout << "Please enter the following data:\n";
                cout << "Price";
                cin >> computer.price;
                cout << "\033[2J\033[1;1H"; 
                cout << "Please enter the following data:\n";
                cout << "Processor\n";
                cin >> computer.proc;
                cout << "\033[2J\033[1;1H"; 
                cout << "Please enter the following data:\n";
                cout << "Amount of RAM\n";
                cin >> computer.ram;
                cout << "\033[2J\033[1;1H"; 
                cout << "Please enter the following data:\n";
                cout << "Amount of memory\n";
                cin >> computer.memory;
                cout << "\033[2J\033[1;1H";
                cout << "Please enter the following data:\n";
                cout << "Count of memory storages\n";
                cin >> computer.memory;
            break;
        case 51:
            break;
        case 52:
            break;
        case 53:
            break;
        case 54:
            break;
        }
    }
    
        


}

struct computer
{
    string brand;
    float price;
    string proc;
    unsigned int ram;
    unsigned int memory;
    unsigned int memory_count;
};

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
