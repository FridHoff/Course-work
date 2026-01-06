#include <iostream>
#include <iomanip>
#include <stdlib.h> // For malloc()
#include <conio.h> // For _getch()
#include <stdio.h> 
#include <fstream> // For files
#include <string>

using namespace std;

// Структура для хранения записи компьютера
struct Computer
{
	char brand[20];
	char proc[25];
	int ram;
	int memory;
	int memory_count;
	float price;
	bool tryToInput(char* buffer, int maxLength) 
	{
		string input = "";
		char ch;
		while (true) 
		{
			ch = _getch(); // Читаем символ без эха в консоль

			if (ch == 27) return false; // Код Esc

			if (ch == 13) 
			{ // Код Enter
				cout << endl;
				break;
			}

			if (ch == 8) 
			{ // Backspace
				if (!input.empty()) 
				{
					input.pop_back();
					cout << "\b \b"; // Удаляем символ из консоли
				}
			}
			else if (input.length() < maxLength - 1) 
			{
				input += ch;
				cout << ch; // Выводим символ
			}
		}
		strcpy_s(buffer, maxLength, input.c_str());
		return true;
	}

	// Обертка для числового ввода
	bool tryToInputInt(int& value) 
	{
		char buf[20];
		if (!tryToInput(buf, 20)) return false;
		try {
			value = stoi(buf);
		}
		catch (...) { value = 0; }
		return true;
	}

	bool CompInput() 
	{
		cout << "\033[2J\033[1;1H"; // Очистка
		cout << "Press ESC to cancel at any time.\n\n";

		cout << "Brand: ";
		if (!tryToInput(this->brand, 20)) return false;

		cout << "Processor: ";
		if (!tryToInput(this->proc, 25)) return false;

		cout << "RAM: ";
		if (!tryToInputInt(this->ram)) return false;

		return true; // Успешно заполнено
	}
};

//Элемент списка
struct Node
{
	Computer data;
	// Переменные для хранения указателей на след. и пред. записи в списке
	Node* prev, * next;
};


// Класс для реализации динамического двусвязного списка
class List                
{
public:
	// Переменная для хранения кол-ва записей в списке
	int count = 0;
	// Начало и конец списка
	Node* head, * tail; 
public:
	// Конструктор класса без параметров
	List()
	{
		head = NULL; // Первого элемента пока нет
		tail = NULL; // Последнего тоже(
	}
	//Добавление элемента в начало списка
	Node* push_front(Computer comp) 
	{
		// Выделяем память под новый элемент и записываем указатель на эту память
		Node* item = (Node*)(malloc(sizeof(Node)));
		// Передаём данные в новую запись
		item->prev = item->next = NULL;
		// Копирование вместо оператора =, так как он некорректно передаёт текствовые данные
		item->data = comp;
		/*strcpy(item->brand, comp.brand);
		strcpy(item->proc, comp.proc);
		item->ram = comp.ram;
		item->memory = comp.memory;
		item->memory_count = comp.memory_count;
		item->price = comp.price;*/
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
	Node* push_back(Computer comp) 
	{
		// Выделяем память под новый элемент и записываем указатель на эту память
		Node* item = (Node*)(malloc(sizeof(Node)));
		// Передаём данные в новую запись
		item->prev = item->next = NULL;
		// Копирование вместо оператора =, так как он некорректно передаёт текствовые данные
		item->data = comp;
		/*strcpy(item->brand, comp.brand);     
		strcpy(item->proc, comp.proc);
		item->ram = comp.ram;
		item->memory = comp.memory;
		item->memory_count = comp.memory_count;
		item->price = comp.price;*/
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
		// Создаём указатель на второй элемент
		Node* ptr = head->next;
		// Если такой имеется
		if (ptr != NULL)
			// То убираем из него указатель на предыдущий элемент
			ptr->prev = NULL;
		else
			tail = NULL;
		// Очищаем текущий первый элемент
		free(head);
		// Записываем на его место "второй"
		head = ptr;
		// Уменьшаем общее кол-во элементов списка
		count--;
	}
	//Удаление последнего элемента списка
	void pop_back()
	{
		if (tail == NULL) return;
		// Создаём указатель на предпоследний элемент
		Node* ptr = tail->prev;
		// Если такой имеется
		if (ptr != NULL)
			// То убираем из него указатель на следующий элемент
			ptr->next = NULL;
		else
			head = NULL;
		// Очищаем текущий крайний элемент
		free(tail);
		// Записываем на его "предпоследний" второй
		tail = ptr;
		// Уменьшаем общее кол-во элементов списка
		count--;
	}
	//Удаление элемента по индексу
	void erase(int index)
	{
		// Получаем указатель на удаляемый элемент
		Node* ptr = getAt(index);
		// Выходим если такого нет
		if (ptr == NULL)
			return;
		// Если это первый элемент, то удаляем спереди
		if (ptr->prev == NULL) 
		{
			pop_front();
			return;
		}
		// Если последний, то сзади
		if (ptr->next == NULL) 
		{
			pop_back();
			return;
		}
		// Создаём указатели на смежные к удалённому элементы
		Node* left = ptr->prev;
		Node* right = ptr->next;
		left->next = right;
		right->prev = left;
		// Освобождаем память элемента (удаляем)
		free(ptr);		
		this->count--;
	}
	//Очистка списка
	void ClearList()
	{
		while (head != NULL)
			pop_front();
		count = 0;
	}
	//Вывод списка на экран	
	void Show(/*int flag = 2*/)
	{
		// Переменная для нумерации элементов
		int i = 1;
		// Очистка консоли
		cout << "\033[2J\033[1;1H";
		// Указание ширины выводимых данных
		cout.width(4);
		// Заполнение пустого места пробелами
		cout.fill(' ');
		cout << "N";
		cout.width(20);
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
		cout.width(15);
		cout.fill(' ');
		cout << "Memory count";
		cout.width(15);
		cout.fill(' ');
		cout << "Price" << "\n";
		// Поэлементно проходимся по списку
		for (Node* ptr = this->head; ptr != NULL; ptr = ptr->next)
		{
			cout.width(4);
			cout.fill(' ');
			cout << i << ')';
			cout.width(20);
			cout.fill(' ');
			cout << ptr->data.brand;
			cout.width(25);
			cout.fill(' ');
			cout << ptr->data.proc;
			cout.width(7);
			cout.fill(' ');
			cout << ptr->data.ram<< " Gb";
			cout.width(12);
			cout.fill(' ');
			cout << ptr->data.memory<<" Gb";
			cout.width(15);
			cout.fill(' ');
			cout << ptr->data.memory_count;
			cout.width(15);
			cout.fill(' ');
			cout << fixed << setprecision(2) << ptr->data.price << "\n";
			i++;
		}
	}
	// Получение элемента списка по индексу
	Node* getAt(int index)
	{
		// Создаём указатель для искомого элемента
		Node* ptr;
		// Переменная для хранения индекса массива относительно итераций цикла
		int i = 0;
		// Если искомый элемент во второй половине списка то поиск начнётся с конца, на случай большого кол-ва записей
		if (index > this->count / 2)
		{
			// Начинаем с конца
			i = this->count - 1;
			ptr = tail;
			// Пока не нашли
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
			// Начинаем с начала
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
	// Получение элемента списка по индексу через оператор []
	Node* operator [] (int index) {
		return getAt(index);
	}
	// Добавление элемента по индексу
	Node* insert(int index, Computer comp)
	{
		// Записываем элемент, находящийся на месте нового 
		Node* right = getAt(index);
		// Если такого нет, 
		if (right == NULL)
			// то всавляем в конец списка
			return push_back(comp);
		// Записываем элемент перед текущим
		Node* left = right->prev;
		// Если такого нет, 
		if (left == NULL)
			// то вставляем в начало списка
			return push_front(comp);
		// Выделяем память под новый элемент и записываем указатель на эту память
		Node* ptr = (Node*)malloc(sizeof(Node));	
		// Передаём данные в новую запись
			/*strcpy(ptr->brand, data.brand);
			strcpy(ptr->proc, data.proc);
			ptr->ram = data.ram;
			ptr->memory = data.memory;
			ptr->memory_count = data.memory_count;
			ptr->price = data.price;*/
		ptr->data = comp;
			// Меняем местами указатели
		ptr->prev = left;
		ptr->next = right;
		left->next = ptr;
		right->prev = ptr;
		// Возвращаем новый элемент
		return ptr;
	}
	// Функция для рокировки элементов
	void swap(Node* first, Node* second)
	{
		// Выделяем память под временный элемент и записываем указатель на эту память		
		Computer temp = Computer(first->data);
		// Передаём в него данные
		/*strcpy(temp->brand, first->brand);
		strcpy(temp->proc, first->proc);
		temp->ram = first->ram;
		temp->memory = first->memory;
		temp->memory_count = first->memory_count;
		temp->price = first->price;*/		
		first->data = second->data;
		second->data = temp;
		/*strcpy(first->brand, second->brand);
		strcpy(first->proc, second->proc);
		first->ram = second->ram;
		first->memory = second->memory;
		first->memory_count = second->memory_count;
		first->price = second->price;

		strcpy(second->brand, temp->brand);
		strcpy(second->proc, temp->proc);
		second->ram = temp->ram;
		second->memory = temp->memory;
		second->memory_count = temp->memory_count;
		second->price = temp->price;*/
		// Освобождаем ранее выделенную память
		//free(temp);
	}
	// Функция получения суммы цены всех компьютеров в списке
	float GetSumm()
	{
		// Переменная для записи суммы
		float sum=0;
		// Поэлементно проходим список
		for (Node* ptr = this->head; ptr != NULL; ptr = ptr->next)		
			// Добавляем цену текущего пк к сумме
			sum += ptr->data.price;		
		// Возвращаем сумму
		return sum;
	}
};
//Поиск по текстовым полям
List search(List& list, string s)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Сравниваем результаты выполнения функции поиска из библиотеки для работы со строками
		if (((((string)(ptr->data.brand))).find(s) != string::npos) || ((string)(ptr->data.proc)).find(s) != string::npos)
		{
			result.push_back(list.getAt(i)->data);
		}
		i++;
	}
	return result;
}
// Поиск по численным полям
List search(List& list, float input)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Сравниваем данные текущего элемента с введёнными
		if ((ptr->data.ram) == input || ptr->data.memory == input || ptr->data.memory_count == input || ptr->data.price==input)
		{
			result.push_back(list.getAt(i)->data);
		}
		i++;
	}
	return result;
}
// Фильтр по числовым полям
List filter(List& list, bool(*func)(Computer, Computer), float item)
{
	// Инициализируем список для вывода результатов поиска
	List result;
	int i = 0;
	Computer temp;
	temp.memory = item;
	temp.memory_count = item;
	temp.ram = item;
	temp.price = item;
	// Поэлементно проходим список
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Для сравнения с искомыми данными используем функции сравнения определённых полей
		if (func(ptr->data, temp))
		{
			result.push_back(list.getAt(i)->data);
		}
		i++;
	}
	//free(temp);
	return result;
}

//Чтение структуры из файла
void _readStruct(List& list)
{
	Node* computer = (Node*)malloc(sizeof(Node));
	// Переменная для работы с файлом
	FILE* file; 
	// Переменная для обозначения конца файла
	long i = 0, fEnd;    	
	// Открываем бинарный файл для чтения 							
	if (file = fopen("data.bin", "rb"))                                   
	{
		// Перемещаем курсор в конец файла.
		fseek(file, 0, SEEK_END); 
		// Функция выдаст конечное положнние курсора относительно начала файла в байтах.				
		fEnd = ftell(file);					
		while (i < fEnd)
		{
			// Перемещаемся от начала (SEEK_SET) файла на i длинн структуры
			fseek(file, i, SEEK_SET); 
			// Считываем из файла 1 структуру размера Computer			
			fread(computer, sizeof(Computer), 1, file); 
			// Добавляем в список прочитанную структуру
			list.push_back(computer->data);
			i += sizeof(Computer);
		}
		// Закрываем файл
		fclose(file); 
		free(computer);
	}
}
//Чтение структуры из текстового файла
//Запись структуры в файл
void _writeStruct(List list)
{
	// Переменная для работы с файлом
	FILE* f; 
	f = fopen("data.bin", "wb");
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
	{
		// Записываем в файл		
		fwrite(ptr, sizeof(Computer), 1, f); 
	}
	// Закрываем файл						
	fclose(f); 
}
// Сравнение определённых полей структуры для сортровки по возрастанию
bool AscByBrand(Computer a, Computer b)
{
	if (strcmp(a.brand, b.brand) <= 0)
		return true;
	else
		return false;
}
bool AscByProc(Computer a, Computer b)
{
	if (strcmp(a.proc, b.proc) <= 0)
		return true;
	else
		return false;
}
bool AscByRam(Computer a, Computer b)
{
	return a.ram <= b.ram;
}
bool AscByMemory(Computer a, Computer b)
{
	return a.memory <= b.memory;
}
bool AscByMemory_count(Computer a, Computer b)
{
	return a.memory_count <= b.memory_count;
}
bool AscByPrice(Computer a, Computer b)
{
	return a.price <= b.price;
}
// Сравнение определённых полей структуры для сортровки по убыванию
bool DescByBrand(Computer a, Computer b)
{
	if (strcmp(a.brand, b.brand) >= 0)
		return true;
	else
		return false;
}
bool DescByProc(Computer a, Computer b)
{
	if (strcmp(a.proc, b.proc) >= 0)
		return true;
	else
		return false;
}
bool DescByRam(Computer a, Computer b)
{
	return a.ram >= b.ram;
}
bool DescByMemory(Computer a, Computer b)
{
	return a.memory >= b.memory;
}
bool DescByMemory_count(Computer a, Computer b)
{
	return a.memory_count >= b.memory_count;
}
bool DescByPrice(Computer a, Computer b)
{
	return a.price >= b.price;
}
// Функция сортировки элементов до обозначенного
int partition(List list, int first, int last, bool(*func)(Computer, Computer))
{
	// Выбираем крайнюю запись в качестве опорной точки
	Node* pivot = list[last];

	// Переменная для наибольшего элемента
	int i = (first - 1);

	// Проходим записи списка
	// Сравнимаем при помощи функций с крайней записью
	for (int j = first; j < last; j++)
	{
		if (func(list[j]->data, pivot->data))
		{

			// Если найден элемент меньше
			// То меняем его с наибольшим, записанным в i
			i++;

			// Меняем записи по индексам i и j местами
			list.swap(list[i], list[j]);
		}
	}

	// Меняем точку опоры с наибольшим элементом в i
	list.swap(list[i + 1], list[last]);

	// Возвращаем точку раздела
	return (i + 1);
}
// Функция сортировки
void quickSort(List& list, int first, int last, bool(*func)(Computer, Computer))
{
	// Проверка на заполненность списка
	if (first < last)
	{
		// pi это точка разделения списка		
		int pi = partition(list, first, last, func);

		// Отдельно сортируем элементы до и после
		// разделителя pi
		quickSort(list, first, pi - 1, func);
		quickSort(list, pi + 1, last, func);
	}
}



int main()
{
	// Инициализируем список
	List list;
	// Инициализируем переменную для переходов по меню
	int menu;
	menu = NULL;
	// Инициализируем переменную для записи компьютеров
	Computer computer;
	// Попытка считать данные с файла
	_readStruct(list);
	// Цикл для меню
	while (menu != 27)
	{
		// Проверка на существование записей в списке
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
			// Выводим главное меню
			cout << "\033[2J\033[1;1H"; // Очистка консоли
			cout << "Choose option!\n\n";
			cout << "1.Computer list\n";
			cout << "2.Add computer\n";
			cout << "3.Edit computer\n";
			cout << "4.Delete computer\n";
			cout << "5.Delete all computers\n";
			cout << "6.Check price for all computers\n\n";
			cout << "Press Esc to save and exit\n";
			// Считываем нажатую клавишу
			menu = _getch();
		}
		switch (menu)
		{
																					// SHOW LIST			
		case 49:
		{

			while (menu != 2)
			{
				menu = NULL;
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				list.Show();
				cout << '\n';
				cout << "Choose option!\n\n";
				cout << "1.Search\n";
				cout << "2.Sort\n";
				cout << "3.Filter\n";
				switch (menu = _getch())
				{
																			// SEARCH
				case 49:												
				{
					menu = NULL;
					cout << "\033[2J\033[1;1H"; // Очистка консоли					
					cout << "Choose option!\n\n";
					cout << "1. Search by name\n";
					cout << "2. Search by stats\n";
					switch (_getch())
					{
														// Поиск по тексту
					case 49:            
					{
						string s;
						// Очистка консоли									
						cout << "\033[2J\033[1;1H";
						cout << "Search for: ";
						cin >> s;
						List result = search(list, s);
						if (result.count != 0)
							result.Show();
						else
						{
							cout << "\033[2J\033[1;1H";
							cout << "Computers not found\n\n";
						}
						_getch();
						result.ClearList();
					}
					break;
														// Поиск по числам
					case 50:		
					{
						List result;
						float s;						
						cout << "\033[2J\033[1;1H"; 
						cout << "Search for: ";
						if(cin >> s)
						result = search(list, s);
						if (result.count != 0)
							result.Show();
						else
						{
							cout << "\033[2J\033[1;1H";
							cout << "Computers not found\n\n";
						}
						_getch();
						result.ClearList();
					}
					break;
					}
					break;
				}
																			// SORT
				case 50:												
				{
					menu = NULL;
					// Флаг для определения в каком порядке сортировать
					int flag = 0;
					while (menu != 1)
					{
						list.Show();
						cout << '\n';
						cout << "Sort by ...\n\n";
						cout << "1.Manufacturer\n";
						cout << "2.Processor\n";
						cout << "3.RAM\n";
						cout << "4.Memory\n";
						cout << "5.Memory count\n";
						cout << "6.Price\n";
						switch (menu = _getch())
						{
									// sort by Manufacturer
						case 49:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByBrand);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByBrand);
								flag = 0;
							}
							break;
						}
									// sort by Processor
						case 50:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByProc);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByProc);
								flag = 0;
							}
							break;
						}
									// sort by RAM
						case 51:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByRam);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByRam);
								flag = 0;
							}
							break;
						}
									// sort by Memory
						case 52:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByMemory);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByMemory);
								flag = 0;
							}
							break;
						}
									// sort by Memmory_count
						case 53:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByMemory_count);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByMemory_count);
								flag = 0;
							}
							break;
						}
									// sort by Price
						case 54:
						{

							menu = NULL;
							if (flag == 0)
							{
								quickSort(list, 0, list.count - 1, AscByPrice);
								flag++;
							}
							else
							{
								quickSort(list, 0, list.count - 1, DescByPrice);
								flag = 0;
							}
							break;
						}
									// Выход в предыдущее меню (27 — Esc)
						case 27:
							menu = 1;
							break;
						}
					}
				break;
				}
																			// FILTER
				case 51:													
				{
					menu = NULL;
					List result;
					result.ClearList();
					result = list;
					while (menu != 1)
					{
						result.Show();
						cout << '\n';
						cout << "Filter by ...\n\n";
						cout << "1.Manufacturer/Processor\n";						
						cout << "2.RAM\n";
						cout << "3.Memory\n";
						cout << "4.Memory count\n";
						cout << "5.Price\n\n";						
						cout << "Summary price for these computers is " << fixed << setprecision(2) << result.GetSumm() << "\n\n";												
						switch (menu = _getch())
						{
									// filter by Text
						case 49:						
						{
							string input;
							result.Show();
							cout << '\n';
							cout << "Computer must include:\n\n";
							cin >> input;
							result = search(result, input);
							if (result.count != 0)
								menu = NULL;
							else
							{
								cout << "\033[2J\033[1;1H";
								cout << "Computers not found\n\n";
								_getch();
								menu = 1;
							}
							break;
						}										
									// filter by Ram
						case 50:
						{
							while (menu != 2)
							{
							float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Ram must be\n\n";
								cout << "1.Lower than:\n";
								cout << "2.Bigger than:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Lower than: ";
									if(cin >> input)
									result = filter(result, AscByRam, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;					
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Bigger than: ";
									if(cin >> input)
									result = filter(result, DescByRam, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;									
									}
								}
								break;
								// Выход в предыдущее меню (27 — Esc)
								case 27:
								{
									menu = 2;
									break;
								}						
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
									// filter by Memory
						case 51:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Memory must be\n\n";
								cout << "1.Lower than:\n";
								cout << "2.Bigger than:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Lower than: ";
									if (cin >> input)
										result = filter(result, AscByMemory, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Bigger than: ";
									if (cin >> input)
										result = filter(result, DescByMemory, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
									// filter by Memory count
						case 52:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Memory count must be\n\n";
								cout << "1.Lower than:\n";
								cout << "2.Bigger than:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Lower than: ";
									if (cin >> input)
										result = filter(result, AscByMemory_count, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Bigger than: ";
									if (cin >> input)
										result = filter(result, DescByMemory_count, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
									// filter by Price
						case 53:
						{
							while (menu != 2)
							{
								float input = NULL;
								result.Show();
								cout << '\n';
								cout << "Price must be\n\n";
								cout << "1. Lower than:\n";
								cout << "2. Bigger than:\n";
								switch (_getch())
								{
								case 49:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Lower than: ";
									if (cin >> input)
										result = filter(result, AscByPrice, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 50:
								{
									result.Show();
									cout << '\n';
									cout << "Ram must be\n\n";
									cout << "Bigger than: ";
									if (cin >> input)
										result = filter(result, DescByPrice, input);
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
									if (result.count != 0)
										menu = NULL;
									else
									{
										cout << "\033[2J\033[1;1H";
										cout << "Computers not found\n\n";
										_getch();
										menu = 1;
									}
								}
								break;
								case 27:
								{
									menu = 2;
									break;
								}
								}
								cin.clear();
								cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
								if (menu == 1)
									break;
							}
						}
						// Выход в предыдущее меню (27 — Esc)
						case 27:
						{
							menu = 1;
							break;
						}
						}
					}
					break;
				}
										// Выход в предыдущее меню (27 — Esc)
				case 27:
				{
					menu = 2;
					break;
				}
				}
			}
			break;
		}
																					// ADD
		case 50:		
		{
			menu = NULL;
			while (menu != 2)
			{
				menu = NULL;
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				cout << '\n';
				cout << "Choose option!\n\n";
				cout << "1.One\n";
				cout << "2.Many\n";
				switch (menu = _getch())
				{
					// Добавление одного пк вручную
				case 49:
				{
					// Вызываем функцию добавления и вручную вводим все данные
					computer.CompInput();
					// Записанный пк добавляем в список
					list.push_back(computer);
					// Возвращаемся в главное меню
					menu = 2;
					break;
				}
					// Добавление всех пк из буфера обмена, но копированные исключительно из текстового файла в проекте
				case 50:
				{
					menu = 1;
					// Запускаем цикл на количество добавляемых пк
					while (menu <= 9)
					{				
						computer.CompInput();
						list.push_back(computer);
						menu++;
					}
					// Очищаем строку ввода от излишков данных
					while (menu != 27)
						menu = _getch();
					// Выходим в гланое меню
					menu = 2;
					break;
				}
					// Выход в предыдущее меню (27 — Esc)
				case 27:
				{

					menu = 2;
					break;
				}
				}
			}
			break;
		}
																					// EDIT
		case 51:																	
		{
			menu = NULL;
			// Цикл для проверки ввода
			while (true)
			{
				list.Show();
				cout << "Enter which computer you want to edit:\n";
				// Проверка на корректность введённых данных
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
			// Вводим новые данные для выбранной записи
			computer.CompInput();
			// Удаляем выбранную запись
			list.erase(menu - 1);
			// Вставляем на её место новую
			list.insert(menu - 1, computer);
			menu = NULL;
			cout << "Press any button to exit...";
			_getch();
			break;
		}
																					// DELETE
		case 52:		
		{
			menu = NULL;
			// Цикл для проверки вводимых значений
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
				list.erase(menu - 1);
				menu = NULL;
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				cout << "Press any button to exit...";
				_getch();
			}
			break;
		}
																					// MEGA DELETE
		case 53:																	
		{
			menu = NULL;
			cout << "\033[2J\033[1;1H"; // Очистка консоли
			cout << "Are you sure about this?\n\n";
			cout << "1.Yes\n";
			cout << "2.No\n\n";
			if (_getch() == 49)
			{
				list.ClearList();
				remove("data.bin");
				cout << "\033[2J\033[1;1H"; // Очистка консоли
				// Изменение цвета текста в консоли для лучше передачи неотвратимости сделанного
				system("color 0C");
				cout << "All computers was deleted\n\n";
				cout << "Press any button to exit...";
				_getch();
				// Возврат к стандартному цвету
				system("color 0F");
			}
			break;
		}
																					// Get All Summ
		case 54:
		{
			cout << "\033[2J\033[1;1H"; // Очистка консоли
			cout << "Summary price for all computers is " << fixed << setprecision(2)<<list.GetSumm()<<"\n\n";
			cout << "Press any button to continue...";			
			_getch();
			break;
		}
													// Выход из приложения (27 — Esc)
		case 27:
		{
			// Сохранение внесённых изменений (запись текущего списка в файл)
			_writeStruct(list);
			// Очистка списка
			list.ClearList();
			exit(0);
			break;
		}
		}
	}
}
