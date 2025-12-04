// Course work.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h> // For 
#include <conio.h> // For _getch()
#include <stdio.h> // For files
#include <fstream>
using namespace std;

struct Computer
{
	string brand;
	string proc;
	int ram;
	int memory;
	int memory_count;
	float price;
};
enum class Option { Write, Delete };
// ФУНКЦИЯ ЗАПИСИ СТРУКТУРЫ В ФАЙЛ
void _writeStruct(Computer computer, Option option)
{
	FILE* f; // переменная для работы с файлом
	switch (option)
	{
	case Option::Write:
	{
		//E:\\data.bin
		f = fopen("data.bin", "ab+"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, 
		// то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать				
		fwrite(&computer, sizeof(Computer), 1, f); // записываем в файл f р		
		fclose(f); // закрываем файл
		cout << "\033[2J\033[1;1H";
		cout << "\nNew computer sucсessfully added!\n\nPress any key to continue...";
		_getch(); // ожидаем нажатия пользователем клавиши
	}
	case Option::Delete:
	{
		f = fopen("dataNew.bin", "ab+");
		fwrite(&computer, sizeof(Computer), 1, f); // записываем в файл f р		
		fclose(f); // закрываем файл		
	}
	}
}
// ФУНКЦИЯ ЧТЕНИЯ ИЗ ФАЙЛА
void _readStruct()
{
	struct Computer* computer = (struct Computer*)malloc(sizeof(Computer));
	FILE* file; // переменная для работы с файлом
	long i = 0, fEnd;    // переменная для обозначения конца файла
	//E:\\data.bin
	if (file = fopen("data.bin", "rb"))                                   // открываем бинарный файл для чтения 							
	{
		fseek(file, 0, SEEK_END); // перемещаем курсор в конец файла.
		fEnd = ftell(file);					// функция выдаст конечное положнние курсора относительно начала файла в байтах.				
		while (i < fEnd)
		{
			fseek(file, i, SEEK_SET); // перемещаемся от начала (SEEK_SET) файла на ... длинн структуры
			fread(computer, sizeof(Computer), 1, file); // считываем из файла f ровно 1 структуру размера Computer			
			// вывод на консоль загруженной структуры
			cout.width(4);
			cout.fill(' ');
			cout << i / sizeof(Computer)+1<<')';
			cout.width(15);
			cout.fill(' ');
			cout << computer->brand;
			cout.width(15);
			cout.fill(' ');
			cout << computer->proc;
			cout.width(10);
			cout.fill(' ');
			cout << computer->ram;
			cout.width(15);
			cout.fill(' ');
			cout << computer->memory;
			cout.width(20);
			cout.fill(' ');
			cout << computer->memory_count;
			cout.width(15);
			cout.fill(' ');
			cout << computer->price << "\n";
			i += sizeof(Computer);
		}
		fclose(file); // закрываем файл
		free(computer);
	}
	else
		throw 404;
}
// ФУНКЦИЯ УДАЛЕНИЯ ПК ИЗ ФАЙЛА
void _delStruct(int number)
{
	struct Computer* computer = (struct Computer*)malloc(sizeof(Computer));
	FILE* file; // переменная для работы с файлом
	long i = 0, fEnd;    // переменная для обозначения конца файла
	//E:\\data.bin	
	file = fopen("data.bin", "rb");
	fseek(file, 0, SEEK_END); // перемещаем курсор в конец файла.
	fEnd = ftell(file);					// функция выдаст конечное положнние курсора относительно начала файла в байтах.				
	fclose(file); // закрываем файл
	while (i < fEnd)
	{
		if (i == number * sizeof(Computer))
		{
			i += sizeof(Computer);
			continue;
		}
		file = fopen("data.bin", "rb");
		fseek(file, i, SEEK_SET); // перемещаемся от начала (SEEK_SET) файла на ... длинн структуры
		fread(computer, sizeof(Computer), 1, file); // считываем из файла f ровно 1 структуру размера Computer			
		// вывод на консоль загруженной структуры
	fclose(file); // закрываем файл
		_writeStruct(*computer, Option::Delete);
		i += sizeof(Computer);
	}
	free(computer);
	remove("data.bin");
	rename("dataNew.bin", "data.bin");
}

int main()
{
	cout << "Choose option!\n";
	int menu;
	menu = NULL;
	Computer computer;
	while (menu != 54)
	{
		cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
		cout << "1.Computer list\n";
		cout << "2.Add computer\n";
		cout << "3.Delete computer\n";
		cout << "4.\n";
		cout << "5.\n";
		cout << "6. Exit\n";
		menu = _getch();
		switch (menu)
		{
		case 49: // 1.
			menu = NULL;
			cout << "\033[2J\033[1;1H";
			cout.width(4);
			cout.fill(' ');
			cout << "N";
			cout.width(15);
			cout.fill(' ');
			cout << "Manufacturer";
			cout.width(15);
			cout.fill(' ');
			cout << "Processor";
			cout.width(10);
			cout.fill(' ');
			cout << "RAM";
			cout.width(15);
			cout.fill(' ');
			cout << "Memory";
			cout.width(20);
			cout.fill(' ');
			cout << "Memory count";
			cout.width(15);
			cout.fill(' ');
			cout << "Price" << "\n";
			try
			{
				_readStruct();
			}
			catch (int code)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Error 404\n\nComputers not found\n\n";
			}
			cout << "Press any button to exit...";
			_getch();
			break;
		case 50: // 2.      		
			menu = NULL;
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Brand\n";
			cin >> computer.brand;
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Please enter the following data:\n";
				cout << "Price\n";
				if (cin >> computer.price)
					break;
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Processor\n";
			cin >> computer.proc;
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Please enter the following data:\n";
				cout << "Amount of RAM\n";
				if (cin >> computer.ram)
					break;
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Please enter the following data:\n";
				cout << "Amount of memory\n";
				if (cin >> computer.memory)
					break;
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Please enter the following data:\n";
				cout << "Count of memory storages\n";
				if (cin >> computer.memory_count)
					break;
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			_writeStruct(computer, Option::Write);
			break;
		case 51:
			menu = NULL;
			cout << "\033[2J\033[1;1H";
			
			cout.width(4);
			cout.fill(' ');
			cout << "N";
			cout.width(15);
			cout.fill(' ');
			cout << "Manufacturer";
			cout.width(15);
			cout.fill(' ');
			cout << "Processor";
			cout.width(10);
			cout.fill(' ');
			cout << "RAM";
			cout.width(15);
			cout.fill(' ');
			cout << "Memory";
			cout.width(20);
			cout.fill(' ');
			cout << "Memory count";
			cout.width(15);
			cout.fill(' ');
			cout << "Price" << "\n";
			try
			{
				_readStruct();
			}
			catch (int code)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Error 404\n\nComputers not found\n\n";
				cout << "Press any button to exit...";
				_getch();
				break;
			}
			cout << "Enter whitch computer you want to destroy:\n";
			cin >> menu;
			_delStruct(menu-1);
			menu = NULL;
			cout << "Press any button to exit...";
			_getch();
			break;
		case 52:
			menu = NULL;
			break;
		case 53:
			menu = NULL;
			break;
		case 54:
			//delete &computer;
			//exit
			break;
		}
	}
}







// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
