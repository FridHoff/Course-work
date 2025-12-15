// Course work.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h> // For malloc()
#include <conio.h> // For _getch()
#include <stdio.h> // For files
#include <fstream>
#include <string>
using namespace std;

struct Computer
{
	char brand[15];
	char proc[25];
	int ram;
	int memory;
	int memory_count;
	float price;
	Computer* prev, * next;
	/*Computer* operator=(Computer* comp)
	{
		strcpy(comp->brand, this->brand);
		strcpy(comp->proc, this->proc);
		this->ram = comp->ram;
		this->memory = comp->memory;
		this->memory_count = comp->memory_count;
		this->price = comp->price;
		return this;
	}*/
	//Запускает процесс ввода нового ПК
	void CompInput()
	{
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Price\n";
			if (cin >> this->price)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Brand\n";
			if (cin.getline(this->brand, 15))
			{
				break;
			}
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
			}
		}
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Amount of RAM\n";
			if (cin >> this->ram)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Processor\n";
			if (cin.getline(this->proc, 25))
			{
				break;
			}
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
			}
		}
		cin.clear();
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Amount of memory\n";
			if (cin >> this->memory)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Please enter the following data:\n";
			cout << "Count of memory storages\n";
			if (cin >> this->memory_count)
				break;
			else
			{
				cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
				_getch();
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
};


// Динамический список
class List                 // список
{
public:
	int count = 0;			
	Computer* head, * tail; //начало и конец списка
public:
	//конструктор класса без параметров
	List() 
	{
		head = NULL; //первого элемента пока нет
		tail = NULL;
	}
	//Добавление элемента в начало списка
	Computer* push_front(Computer comp) {
		Computer* item = (Computer*)(malloc(sizeof(Computer)));
		item->prev = item->next = NULL;				//задаем узлу данные	
		strcpy(item->brand, comp.brand);     	
		strcpy(item->proc, comp.proc);
		item->ram = comp.ram;
		item->memory = comp.memory;
		item->memory_count = comp.memory_count;
		item->price = comp.price;
		item->next = head;
		if (head != NULL)
			head->prev = item;
		if (tail == NULL)
			tail = item;
		head = item;
		count++;
		return item;
	}
	//Добавление элемента в конец списка
	Computer* push_back(Computer comp) {
		Computer* item = (Computer*)(malloc(sizeof(Computer)));
		item->prev = item->next = NULL;
		strcpy(item->brand, comp.brand);     //задаем узлу данные		
		strcpy(item->proc, comp.proc);
		item->ram = comp.ram;
		item->memory = comp.memory;
		item->memory_count = comp.memory_count;
		item->price = comp.price;
		item->prev = tail;
		if (tail != NULL)
			tail->next = item;
		if (head == NULL)
			head = item;
		tail = item;
		count++;
		return item;
	}
	//Удаление первого элемента списка
	void pop_front() 
	{
		if (head == NULL) return;

		Computer* ptr = head->next;
		if (ptr != NULL)
			ptr->prev = NULL;
		else
			tail = NULL;

		free(head);
		head = ptr;
		count--;
	}
	//Удаление последнего элемента списка
	void pop_back() 
	{
		if (tail == NULL) return;

		Computer* ptr = tail->prev;
		if (ptr != NULL)
			ptr->next = NULL;
		else
			head = NULL;

		free(tail);
		tail = ptr;
		count--;
	}
	//Удаление элемента по индексу
	void erase(int index) 
	{
		Computer* ptr = getAt(index);
		if (ptr == NULL)
			return;

		if (ptr->prev == NULL) {
			pop_front();
			return;
		}

		if (ptr->next == NULL) {
			pop_back();
			return;
		}

		Computer* left = ptr->prev;
		Computer* right = ptr->next;
		left->next = right;
		right->prev = left;

		free(ptr);
	}
	//Очистка списка
	void ClearList()
	{
		while (head != NULL)
			pop_front();
		count = 0;
	}
	//Вывод списка на экран	
	void Show()
	{
		int i = 1;
		cout << "\033[2J\033[1;1H";
		cout.width(4);
		cout.fill(' ');
		cout << "N";
		cout.width(15);
		cout.fill(' ');
		cout << "Manufacturer";
		cout.width(25);
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
		for (Computer* ptr = this->head; ptr != NULL; ptr = ptr->next)
		{
			cout.width(4);
			cout.fill(' ');
			cout << i << ')';
			cout.width(15);
			cout.fill(' ');
			cout << ptr->brand;
			cout.width(25);
			cout.fill(' ');
			cout << ptr->proc;
			cout.width(10);
			cout.fill(' ');
			cout << ptr->ram;
			cout.width(15);
			cout.fill(' ');
			cout << ptr->memory;
			cout.width(20);
			cout.fill(' ');
			cout << ptr->memory_count;
			cout.width(15);
			cout.fill(' ');
			cout << ptr->price << "\n";
			i++;
		}
	}
	//Получение элемента списка по индексу
	Computer* getAt(int index) 
	{		
		Computer* ptr;
		int i = 0;
		if (index > this->count / 2)
		{
			i = this->count - 1;
			ptr = tail;
		while (i != index) 
		{
			if (ptr == NULL)
				return ptr;
			ptr = ptr->prev;
			i--;
		}
		}
		else
		{
			ptr = head;
			while (i != index)
			{
				if (ptr == NULL)
					return ptr;
				ptr = ptr->next;
				i++;
			}
		}
		return ptr;
	}
	//Получение элемента списка по индексу через оператор []
	Computer* operator [] (int index) {
		return getAt(index);
	}
};

//Перечисление для функции записи
enum class Option { Write, Delete, Edit };
//Чтение структуры из файла
void _readStruct(List& list)
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
			list.push_back(*computer);
			i += sizeof(Computer);
		}
		fclose(file); // закрываем файл
		free(computer);
	}
	else
		throw 404;
}
//Запись структуры в файл
void _writeStruct(Computer computer, Option option, int i = NULL, List list = List())
{
	FILE* f; // переменная для работы с файлом
	switch (option)
	{
	case Option::Write:

		//E:\\data.bin
		f = fopen("data.bin", "ab+"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, 
		fseek(f, 0, SEEK_END);// то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать				
		fwrite(&computer, sizeof(Computer), 1, f); // записываем в файл f р		
		fclose(f); // закрываем файл
		cout << "\033[2J\033[1;1H";
		cout << "\nNew computer sucсessfully added!\n\nPress any key to continue...";
		_getch(); // ожидаем нажатия пользователем клавиши
		break;
	case Option::Delete:
		f = fopen("data.bin", "wb");
		for (Computer* ptr = list.head; ptr != NULL; ptr = ptr->next)
		{
			fwrite(ptr, sizeof(Computer), 1, f); // записываем в файл f р		
		}
		fclose(f); // закрываем файл		
		break;
	case Option::Edit:
		f = fopen("data.bin", "r+");  // r+ для изменения файла
		fseek(f, i * sizeof(Computer), SEEK_SET);
		fwrite(&computer, sizeof(Computer), 1, f); // записываем в файл f р		
		fclose(f); // закрываем файл		
		break;
	}
}

int partition(List list, int first, int last)
{
	// Selecting last element as the pivot
	float pivot = list[last]->price;

	// Index of elemment just before the last element
	// It is used for swapping
	int i = (first - 1);

	for (int j = first; j <= last - 1; j++) {

		// If current element is smaller than or
		// equal to pivot
		if (list[j]->price <= pivot) {
			i++;		
			Computer* temp = list[i];
			list[i]->prev=list[j]->prev;
			list[i]->next = list[j]->next;
			list[j]->prev = temp->prev;
			list[j]->next= temp->next;	
			swap(vec[i], vec[j]);
		}
	}

	// Put pivot to its position
	swap(vec[i + 1], vec[high]);

	// Return the point of partition
	return (i + 1);
}
int main()
{
	List list;
	int menu, i;
	menu = NULL;
	Computer computer;
	try
	{
		_readStruct(list);
	}
	catch (int code)
	{
		while (true)
		{
			cout << "\033[2J\033[1;1H";
			cout << "Error 404\n\nComputers not found\n\n";
			cout << "1.Add computer\n";
			cout << "2.Exit\n";
			menu = _getch();
			if (menu == 50)
			{
				exit(0);
			}
			else if (menu == 49)
			{
				menu = 50;
				break;
			}
		}
	}
	while (menu != 54 && menu != 27)
	{
		if (list.count == 0)
		{
			while (true)
			{
				cout << "\033[2J\033[1;1H";
				cout << "Error 404\n\nComputers not found\n\n";
				cout << "1.Add computer\n";
				cout << "2.Exit\n";
				menu = _getch();
				if (menu == 50)
				{
					exit(0);
				}
				else if (menu == 49)
				{
					menu = 50;
					break;
				}
			}
		}
		if (menu != 50)
		{
			cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
			cout << "Choose option!\n\n";
			cout << "1.Computer list\n";
			cout << "2.Add computer\n";
			cout << "3.Edit computer\n";
			cout << "4.Delete computer\n";
			cout << "5.Delete all computers\n";
			cout << "6. Exit\n";
			menu = _getch();
		}
		switch (menu)
		{
		case 49:																	// SHOW LIST
			menu = NULL;
			list.Show();
			cout << "Press any button to exit...";
			_getch();
			break;
		case 50:																	// ADD
			menu = NULL;
			computer.CompInput();
			_writeStruct(computer, Option::Write);
			list.ClearList();
			_readStruct(list);
			break;
		case 51:																	// EDIT
			menu = NULL;
			while (true)
			{
				list.Show();
				cout << "Enter which computer you want to edit:\n";
				if (cin >> menu && menu <= list.count && menu > 0)
					break;
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			computer.CompInput();
			_writeStruct(computer, Option::Edit, menu - 1);
			list.ClearList();
			_readStruct(list);
			menu = NULL;
			cout << "Press any button to exit...";
			_getch();
			break;
		case 52:																	// DELETE
			menu = NULL;
			while (true)
			{
				list.Show();
				cout << "Enter which computer you want to destroy:\n";
				if ((cin >> menu && menu <= list.count && menu > 0))
				{
					break;				
				}
				else
				{
					cout << "\033[2J\033[1;1H" << "Incorrect data! Try again...";
					_getch();
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				}
			}
			if (menu != 27)
			{
			computer = Computer();
			list.erase(menu-1);
			_writeStruct(computer, Option::Delete, menu - 1, list);
			list.ClearList();
			_readStruct(list);
			menu = NULL;
			cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
			cout << "Delete was sucсessfull!\n\n";
			cout << "Press any button to exit...";
			_getch();
			}
			break;
		case 53:
			menu = NULL;
			cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
			cout << "Are you sure about this?\n\n";
			cout << "1.Yes\n";
			cout << "2.No\n\n";
			if (_getch() == 49)
			{
				remove("data.bin");
				cout << "\033[2J\033[1;1H"; // Console clear and start from top left of window
				cout << "Computers was viped\n\n";
				cout << "Press any button to exit...";
				_getch();
				list.ClearList();
			}
			break;
		case 54:
			exit(0);
			break;
		case 27:
			exit(0);
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
