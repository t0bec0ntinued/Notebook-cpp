#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
//Объявляю структуры для данных
typedef struct Cards CardElement; //Описываю новый тип данных


enum Department { //enum - тип перечисления
	DEPT_PROGRAMMERS=1,
	DEPT_MANAGEMENT=2,
	DEPT_SHIPPING=3
};
enum Transport {
	TRANSP_TRAIN=1,
	TRANSP_AUTO=2,
	TRANSP_AERO=3,
	TRANSP_SHIP=4
};
struct Cards {
	char Name[255];
	char LastName[255];
	int Age;
	enum Department Department;
	union {
		struct {
			char Project[255];
			char CPU[127];
			int Memory;
		} Programmers;
		struct {
			char Project[255];
			char Customer[255];
			int ProgrammersNum;
		}Management;
		struct {
			enum Transport Transport;
			char Address[255];
			char Customer[255];
			int Weight;
		} Shipping;
		CardElement* pNext; //Указатель на следующий элемент списка . Тип , на который он указывает - struct CardElement
	};
};// В нём всегда хранится адрес, где располагается следующий элемент списка
							// Либо NULL, в случае последнего эл. списка

	//Функции
	CardElement* pRoot = NULL; // Указатель на первый элемент списка


	//Делаем обход списка. pCur - вспомогательный указатель, который указывает на текущий рассматриваемый 
	//элемент.
	CardElement* Find(int k) {//Функция поиска для вставки

		if (!pRoot)
			return NULL;

		CardElement* pCur;   //Создаём переменную pCur

		pCur = pRoot;       //Записываем в неё NULL - указываем на начальный элемент

		for (int i = 0; i < k; i++) //До тех пор, пока i меньше переданного значения
		{                           //в переменную pCur будет записываться адрес переменной 
									// pNext
			if (pCur->pNext == NULL)return pCur;// Если элемента pNext нет,
			pCur = pCur->pNext;                 // то вернётся указатель на pCur, т.е на текущий элемент


		}

		return pCur;
	}

	CardElement* Add() {    //Функция вставки

		CardElement* pNew = (CardElement*)malloc(sizeof(CardElement)); //Выделяем динамически память 

		if (pNew == NULL) { //Проверяем на ошибки
			printf("Ошибка выделения памяти\n");
			free(pNew);
			exit;
		}
		else {   //В случае успеха вводим данные
			printf("Введите имя\n");
			scanf("%s", &pNew->Name); // -> Обратиться по адресу Name и отсканированную строку pNew записать туда

			printf("Введите фамилию\n");
			scanf("%s", &pNew->LastName); // Обратиться по адресу LastName и вставить введённую строку pNew (далее аналогично)
			printf("Введите возраст\n");
			scanf("%d", &pNew->Age);
			int n = 0;
			printf("Выберите отдел:\n1.Программисты\n2.Менеджмент\n3.Доставка\n");
			do {
				scanf("%d", &n);
				if (n < 1 || n>3) { //Проверка на ложный выбор
					printf("Такого отдела нет. Попробуйте снова.\n");
				}
			} while (n < 1 || n>3); //До тех пор, пока не будут введены корректные данные
			if (n >= 1 && n <= 3) {
				pNew->Department = (enum Department)n;  // Перейти по адресу поля Department в структуре Cards 
			}                                           // И записать туда значение из перечисления Department, соответствующее n    

			if (n == 1) {                               //При выборе n=0 работаем с структурой Programmers
				printf("Введите имя проекта:\n");
				scanf("%s", &pNew->Programmers.Project);
				printf("Введите имя процессора:\n");
				scanf("%s", &pNew->Programmers.CPU);
				printf("Введите количество памяти:\n");
				scanf("%d", &pNew->Programmers.Memory);
			}
			if (n == 2) {                               //При выборе n=1 работаем с структурой Management
				printf("Введите имя проекта:\n");
				scanf("%s", &pNew->Management.Project);
				printf("Введите имя заказчика:\n");
				scanf("%s", &pNew->Management.Customer);
				printf("Введите количество программистов:\n");
				scanf("%d", &pNew->Management.ProgrammersNum);
			}
			if (n == 3) {                                //При выборе n=2 работаем с структурой Shipping
				printf("Введите адресс:\n");
				scanf("%s", &pNew->Shipping.Address);
				printf("Введите имя заказчика:\n");
				scanf("%s", &pNew->Shipping.Customer);
				printf("Введите вес груза:\n");
				scanf("%d", &pNew->Shipping.Weight);
				int i = 0;
				printf("Выберите тип транспорта:\n1.Поезд\n2.Автомобиль\n3.Самолёт\n4.Корабль\n");

				do {
					scanf("%d", &i);
					if (i < 1 || i>4) {
						printf("Неверно указан тип транспорта\n");
					}
				} while (i < 1 || i>4);
				if (i >= 1 && i <= 4) {
					pNew->Shipping.Transport = (enum Transport)i;
				}

			}
			int k = 0;
			printf("После какой записи вставить новую?\n");
			scanf("%u", &k);
			if (pRoot == NULL || k < 1) { // При отсутствии значений в таблице или при выборе 
				pNew->pNext = pRoot;      // нулевой записи(или меньше нуля), новая запись будет добавлена в
				pRoot = pNew;             // начало списка
										  // Теперь pNew - первый и последний элемент списка, поэтому указатель pNext,
										  // содержащийся в нём приравниваем к NULL
			}
			else {                                 //Если список не пустой, то сначала находим нужный элемент,
				CardElement* Insert = Find(k - 1); // а потом вставляем после него новый
				// Вставляем новый элемент в список
				pNew->pNext = Insert->pNext;       // Связываем pNew с pNext, который стоял после Insert
				Insert->pNext = pNew;              // Т.е записываем pNext, который был в Insert в pNext, который находится в pNew
												   //После записываем pNew в pNext , лежащий в Insert
			}
			return pNew;

		}




		free(pNew);       //Освобождаю память использованной переменной


	}

	void CardList() {

		Cards* temp = pRoot;
		int i = 1;
		printf("|№  | Имя   |Фамилия|Возраст|Отдел П || Проект | CPU      | Memory |         |\n");
		printf("|   |       |       |       |      М || Проект | Заказчик | Пр-ты  |         |\n");
		printf("|   |       |       |       |      Д || Адрес  | Заказчик | Вес    |Транспорт|\n");


		while (temp) {
			printf("+---+-------+-------+-------+--------++--------+----------+--------+---------+");
			printf("\n|%-3d|%-7s|%-7s|%-7d|", i, temp->Name, temp->LastName, temp->Age);
			switch (temp->Department) {
			case DEPT_PROGRAMMERS:
				printf("Програм.");
				printf("||%-8s|%-10s|%-8d|         |\n", temp->Programmers.Project, temp->Programmers.CPU, temp->Programmers.Memory);
				break;
			case DEPT_MANAGEMENT:
				printf("Менеджм.");
				printf("||%-8s|%-10s|%-8d|         |\n", temp->Management.Project, temp->Management.Customer, temp->Management.ProgrammersNum);
				break;
			case DEPT_SHIPPING:
				printf("Доставка");
				printf("||%-8s|%-10s|%-8d|", temp->Shipping.Address, temp->Shipping.Customer, temp->Shipping.Weight);
				switch (temp->Shipping.Transport) {
				case TRANSP_TRAIN:
					printf("Поезд    |\n");
					break;
				case TRANSP_AUTO:
					printf("Автом.   |\n");
					break;
				case TRANSP_AERO:
					printf("Самолёт  |\n");
					break;
				case TRANSP_SHIP:
					printf("Корабль  |\n");
					break;
				}
				break;
			}
			temp = temp->pNext; // В temp записываем указатель pNext, хранящийся в temp
			i++;
		}
		printf("+---+-------+-------+-------+--------++--------+----------+--------+---------+");




	}

	void Delete(int index)    //Функция для удаления данных из таблицы
	{
		if (pRoot == NULL)   //Проверяем наличие данных в таблице
		{
			printf("Отсутствуют данные для удаления.");
			return;
		}
		if (index == 0)      //Если передан начальный элемент таблицы
		{

			CardElement* pDel = pRoot;//Создаём указатель pDel , присваем ему данные первого элемента

			pRoot = pRoot->pNext; //Обращаемся к следующему элементу и записываем данные из него в pRoot

			free(pDel); //удаляем данные первого элемента

		}
		else
		{

			CardElement* pBeforeDel = Find(index - 1); // Создаём указатель pBeforeDel, в который заносится адрес эелемента,
													   // стоящего перед тем, который мы хотим удалить
			if (pBeforeDel->pNext == NULL)return;   //Если введён последний элемент списка  

			CardElement* pDel = pBeforeDel->pNext;  //то в адрес удаляемого элемента запишется pNext,
													//который лежал в pBeforeDel (если проще, то это будет адрес удаляемого элемента)
			if (pDel == NULL)
			{

				printf("Отсутствуют данные для удаления.");

				return;

			}

			pBeforeDel->pNext = pDel->pNext; //Переставляем связи. В pNext, хранящийся внутри pBeforeDel
											 //записываем pNext, находящийся в pDel
			free(pDel);                      //Освобождаем память, занимаемую элементом

		}
	}
	void RemoveAll()
	{
		CardElement* pTemp = pRoot;
		CardElement* pDel;
		for (int i = 0; pTemp != NULL; i++)
		{
			pDel = pTemp;
			pTemp = pTemp->pNext;
			free(pDel);
		}
		pRoot = NULL;
	}


	void SaveToFile() {   //Функция для сохранения в файл
		char FileName[256];      //Создаём переменную для имени файла
		printf("Введите имя файла:\n");
		scanf("%s", &FileName);   //Считываем путь к файлу с клавиатуры

		FILE* saveFile = fopen(FileName, "wb"); //открываем файл для записи в бинарном виде
		if (!saveFile) {                     //проверяем на ошибки
			printf("Не удалось открыть файл.\n");
			return;
		}
		CardElement* pFile = pRoot;                             //Записываем данные
		fwrite(pFile, sizeof(CardElement), 1, saveFile);
		pFile = pFile->pNext;
		while (pFile) {
			fwrite(pFile, sizeof(CardElement), 1, saveFile);
			pFile = pFile->pNext;
		}
		fclose(saveFile);      //Закрываем поток
	}

	void WriteFromFile() {     //Функция для написания из файла
		char FileName[256];   //Создаём переменную для имени файла
		printf("Введите имя файла:\n");
		scanf("%s", FileName); //Сканируем путь к файлу с клавиатуры
		FILE* writeFile = fopen(FileName, "rb"); //Открываем файл для чтения
		if (!writeFile)       //Проверяем открытие файла
		{
			printf("Не удалось открыть файл");
			return;
		}

		RemoveAll();

		CardElement* pFile = (CardElement*)malloc(sizeof(CardElement));  //Выделяем память динамически
		if (pFile == NULL)
		{
			printf("Не удалось выделить память.");  //Проверяем на ошибки
			system("pause");
			return;
		}


		// Записываем данные из файла
		CardElement* endElem = pFile;

		fread(pFile, sizeof(CardElement), 1, writeFile);

		pRoot = pFile;


		while (1)
		{
			pFile = (CardElement*)malloc(sizeof(CardElement));
			if (pFile == NULL)
			{
				printf("Не удалось выделить память");
				system("pause");
				return;
			}
			fread(pFile, sizeof(CardElement), 1, writeFile);
			if (feof(writeFile))
			{
				free(pFile);
				break;
			}

			endElem->pNext = pFile;
			endElem = pFile;
		}

		fclose(writeFile);
	}

	int main() {
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
		setlocale(LC_ALL, "Russian");
		int func;

		do {
			printf("Выберите функцию\n1.Добавить новую запись\n2.Удалить запись\n3.Запись в файл\n4.Чтение из файла\n5.Выход\n");
			scanf("%d", &func);
			if (func == 1) {
				Add();
				CardList();
				printf("\n");
			}
			if (func == 2) {
				int index;
				printf("Введите номер строки, которую хотите удалить:\n");
				scanf("%d", &index);
				Delete(index);
				CardList();
				printf("\n");
			}
			if (func == 3) {
				SaveToFile();

			}
			if (func == 4) {
				WriteFromFile();
				CardList();
				printf("\n");
			}
			if (func == 5) {
				RemoveAll();
			}
			if (func < 1 || func>5) {
				printf("Такой функции нет. Попробуйте снова\n");
			}


		} while (func != 5);


	}
