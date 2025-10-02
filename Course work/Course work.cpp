// Course work.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h> // For 
#include <conio.h> // For _getch()
#include <stdio.h> // For files
using namespace std;

struct Computer
{
	string brand;
	float price;
	string proc;
	unsigned int ram;
	unsigned int memory;
	unsigned int memory_count;


	Computer() = default;
};

int writeStruct(struct Computer* p)
{
	FILE* fp;
	char* c;
	int size = sizeof(struct Computer); // количество записываемых байтов

	fp = fopen("data.txt", "wb"); //открываем файл для бинарной записи
	if (!fp)    // если не удалось открыть файл
	{
		printf("Error occured while opening file \n");
		return 1;
	}
	// устанавливаем указатель на начало структуры
	c = (char*)p;
	// посимвольно записываем в файл структуру
	for (int i = 0; i < size; i++)
	{
		putc(*c++, fp);
	}
	fclose(fp);
	return 0;
}
int read()
{
	FILE* fp;
	char* c;
	int i; // для считывания одного символа
	// количество считываемых байтов
	int size = sizeof(struct Computer);
	// выделяем память для считываемой структуры
	struct Computer* ptr = (struct Computer*)malloc(size);
	fp = fopen("data.txt", "rb");     // открываем файл для бинарного чтения
	if (!fp)
	{
		printf("Error occured while opening file \n");
		return 1;
	}

	// устанавливаем указатель на начало блока выделенной памяти
	c = (char*)ptr;
	// считываем посимвольно из файла
	while ((i = getc(fp)) != EOF)
	{
		*c = i;
		c++;
	}

	fclose(fp);
	// вывод на консоль загруженной структуры
	printf("%-20s %5d \n", ptr->name, ptr->age);
	free(ptr);
	return 0;
}

int main()
{
	cout << "Choose option!\n";
	int menu = NULL;
	Computer computer;
	FILE* fp = fopen("data.txt", "w");
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
			//if (fp)
			//{
			//	// посимвольно записываем в файл
			//	for (int i = 0; i < computer.brand.length(); i++)
			//	{
			//		putc(computer.brand[i], fp);
			//	}
			//	fclose(fp);
			//}
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Brand\n";
			cin >> computer.brand;			
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Price\n";
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
			save(&computer);
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



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
