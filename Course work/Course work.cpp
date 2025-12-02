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

void writeStruct(struct Computer comp)
{
	//FILE* f; // переменная для работы с файлом
	//int i; // счётчик

	//f = fopen("data.dat", "ab+"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать	
	////for (i = 0; i < 10; i++) // запишем в файл в цикле 10 пакетов
	////{
	////	pack.i = pack.i + 1;
	////	pack.d = pack.d + 11;
	//	fwrite(&comp, sizeof(Computer), 1, f); // записываем в файл f ровно 1 comp размера computer
	////}
	//	fclose(f); // закрываем файл

	/*ofstream ofs("data.dat", ios::out | ios::binary);

	if(ofs.is_open()) {
			ofs.write((char *)&comp, sizeof(comp));
	}

	ofs.close();*/
	//FILE* fp;
	//char* c;
	//int size = sizeof(struct Computer); // количество записываемых байтов

	//fp = fopen("data.bin", "wb"); //открываем файл для бинарной записи
	//if (!fp)    // если не удалось открыть файл
	//{
	//	printf("Error occured while opening file \n");
	//	return 1;
	//}
	//// устанавливаем указатель на начало структуры
	//c = (char*)p;
	//// посимвольно записываем в файл структуру
	//for (int i = 0; i < size; i++)
	//{
	//	putc(*c++, fp);
	//}
	//fclose(fp);
	//return 0;
}
void readStruct()
{
	//Computer comp;
	//FILE* f;
	//f = fopen("data.dat", "ab+");
	//fseek(f, 1/*4 * sizeof(int_double),*/, SEEK_SET); // перемещаемся от начала (SEEK_SET) файла f на 4 длинны пакета int_double, то есть к началу 5-го пакету
	//fread(&comp, sizeof(Computer), 1, f); // считываем из файла f ровно 1 comp размера computer
	//printf("%-20s %5d \n", comp.brand, comp.price, comp.proc,comp.ram, comp.memory, comp.memory_count);	
	//getch(); // ожидаем нажатия пользователем клавиши
	//fclose(f); // закрываем файл

	/*struct Computer comp;
	ifstream ifs("out_course.dat", ios::in | ios::binary);

	if (ifs.is_open()) {
		ifs.read((char*)&comp, sizeof(comp));
	}*/







	//FILE* fp;
	//char* c;
	//int i; // для считывания одного символа
	//// количество считываемых байтов
	//int size = sizeof(struct Computer);
	//// выделяем память для считываемой структуры
	//struct Computer* ptr = (struct Computer*)malloc(size);
	//fp = fopen("data.bin", "rb");     // открываем файл для бинарного чтения
	//if (!fp)
	//{
	//	printf("Error occured while opening file \n");
	//	return 1;
	//}

	//// устанавливаем указатель на начало блока выделенной памяти
	//c = (char*)ptr;
	//// считываем посимвольно из файла
	//while ((i = getc(fp)) != EOF)
	//{
	//	*c = i;
	//	c++;
	//}

	//fclose(fp);
	//// вывод на консоль загруженной структуры
	//printf("%-20s %5d \n", ptr->brand, ptr->price, ptr->proc,ptr->ram, ptr->memory, ptr->memory_count);
	//free(ptr);
	//return 0;




	//работает, но с непонятной ошибкой
	// 
	//FILE* f_read; // переменная для работы с файлом
	////"E:\\alc.dat", "ab+
	//f_read = fopen("E:\\alc.dat", "ab+");                                   // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, 
	//// а если файл есть, то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать						
	//fseek(f_read, 0, SEEK_SET); // перемещаемся от начала (SEEK_SET) файла f на 4 длинны структуры, то есть к началу 5-й структуры
	//fread(&computer, sizeof(Computer), 1, f_read); // считываем из файла f ровно 1 структуру размера Computer			
	//fclose(f_read); // закрываем файл
}

int main()
{
	cout << "Choose option!\n";
	int menu, flag;
	menu = NULL;
	flag = 1;
	Computer computer;
	//FILE* fp = fopen("data.txt", "w");
			int size = sizeof(struct Computer);
			struct Computer* ptr = (struct Computer*)malloc(size);
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
			menu = NULL;
			cout << "\033[2J\033[1;1H";
			//cout << "Computer list\n";
			FILE* fp;
			char* c;
			int i; // для считывания одного символа
			// количество считываемых байтов
			// выделяем память для считываемой структуры
			fp = fopen("E:\\data.bin", "rb");     // открываем файл для бинарного чтения
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
			//printf("%-20s %5d \n", ptr->brand, ptr->price, ptr->proc, ptr->ram, ptr->memory, ptr->memory_count);
			cout << setw(15) << cout.fill('*') << "Manufacturer"
				<< setw(15) << cout.fill('*') << "\t" << "Processor"
				<< setw(15) << cout.fill('*') << "\t" << "RAM"
				<< setw(15) << cout.fill('*') << "\t" << "Memory"
				<< setw(15) << cout.fill('*') << "\t" << "Memory count"
				<< setw(15) << cout.fill('*') << "\t" << "Price" << "\n";
			cout << setw(15) << cout.fill('*') << ptr->brand << "\t" << ptr->proc << "\t" << ptr->ram << "\t" << ptr->memory << "\t" << ptr->memory_count << "\t" << ptr->price << "\n";
			cout << "Press any button to exit...";
			//readStruct();
			free(ptr);
			_getch();
			break;
		case 50: // 2.      		
			menu = NULL;
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
			cin >> computer.memory_count;

			FILE* f; // переменная для работы с файлом
			//"E:\\alc.dat", "ab+"
			f = fopen("E:\\data.bin", "ab+"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать			
			//fwrite(&flag, sizeof(int), 1, f);
			fwrite(&computer, sizeof(Computer), 1, f); // записываем в файл f р		
			//1 * sizeof(computer)
			fseek(f, 0, SEEK_SET); // перемещаемся от начала (SEEK_SET) файла f на 4 длинны пакета int_double, то есть к началу 5-го пакету
			fread(&computer, sizeof(Computer), 1, f); // считываем из файла f ровно 1 пакет pack размера int_double
			cout << computer.brand << "\t" << computer.proc << "\t" << computer.ram << "\t" << computer.memory << "\t" << computer.memory_count << "\t" << computer.price << "\n";
			_getch(); // ожидаем нажатия пользователем клавиши
			fclose(f); // закрываем файл

			//writeStruct(computer);
			break;
		case 51:
			menu = NULL;
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
