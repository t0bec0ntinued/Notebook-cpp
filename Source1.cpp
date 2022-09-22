#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
//�������� ��������� ��� ������
typedef struct Cards CardElement; //�������� ����� ��� ������


enum Department { //enum - ��� ������������
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
		CardElement* pNext; //��������� �� ��������� ������� ������ . ��� , �� ������� �� ��������� - struct CardElement
	};
};// � �� ������ �������� �����, ��� ������������� ��������� ������� ������
							// ���� NULL, � ������ ���������� ��. ������

	//�������
	CardElement* pRoot = NULL; // ��������� �� ������ ������� ������


	//������ ����� ������. pCur - ��������������� ���������, ������� ��������� �� ������� ��������������� 
	//�������.
	CardElement* Find(int k) {//������� ������ ��� �������

		if (!pRoot)
			return NULL;

		CardElement* pCur;   //������ ���������� pCur

		pCur = pRoot;       //���������� � �� NULL - ��������� �� ��������� �������

		for (int i = 0; i < k; i++) //�� ��� ���, ���� i ������ ����������� ��������
		{                           //� ���������� pCur ����� ������������ ����� ���������� 
									// pNext
			if (pCur->pNext == NULL)return pCur;// ���� �������� pNext ���,
			pCur = pCur->pNext;                 // �� ������� ��������� �� pCur, �.� �� ������� �������


		}

		return pCur;
	}

	CardElement* Add() {    //������� �������

		CardElement* pNew = (CardElement*)malloc(sizeof(CardElement)); //�������� ����������� ������ 

		if (pNew == NULL) { //��������� �� ������
			printf("������ ��������� ������\n");
			free(pNew);
			exit;
		}
		else {   //� ������ ������ ������ ������
			printf("������� ���\n");
			scanf("%s", &pNew->Name); // -> ���������� �� ������ Name � ��������������� ������ pNew �������� ����

			printf("������� �������\n");
			scanf("%s", &pNew->LastName); // ���������� �� ������ LastName � �������� �������� ������ pNew (����� ����������)
			printf("������� �������\n");
			scanf("%d", &pNew->Age);
			int n = 0;
			printf("�������� �����:\n1.������������\n2.����������\n3.��������\n");
			do {
				scanf("%d", &n);
				if (n < 1 || n>3) { //�������� �� ������ �����
					printf("������ ������ ���. ���������� �����.\n");
				}
			} while (n < 1 || n>3); //�� ��� ���, ���� �� ����� ������� ���������� ������
			if (n >= 1 && n <= 3) {
				pNew->Department = (enum Department)n;  // ������� �� ������ ���� Department � ��������� Cards 
			}                                           // � �������� ���� �������� �� ������������ Department, ��������������� n    

			if (n == 1) {                               //��� ������ n=0 �������� � ���������� Programmers
				printf("������� ��� �������:\n");
				scanf("%s", &pNew->Programmers.Project);
				printf("������� ��� ����������:\n");
				scanf("%s", &pNew->Programmers.CPU);
				printf("������� ���������� ������:\n");
				scanf("%d", &pNew->Programmers.Memory);
			}
			if (n == 2) {                               //��� ������ n=1 �������� � ���������� Management
				printf("������� ��� �������:\n");
				scanf("%s", &pNew->Management.Project);
				printf("������� ��� ���������:\n");
				scanf("%s", &pNew->Management.Customer);
				printf("������� ���������� �������������:\n");
				scanf("%d", &pNew->Management.ProgrammersNum);
			}
			if (n == 3) {                                //��� ������ n=2 �������� � ���������� Shipping
				printf("������� ������:\n");
				scanf("%s", &pNew->Shipping.Address);
				printf("������� ��� ���������:\n");
				scanf("%s", &pNew->Shipping.Customer);
				printf("������� ��� �����:\n");
				scanf("%d", &pNew->Shipping.Weight);
				int i = 0;
				printf("�������� ��� ����������:\n1.�����\n2.����������\n3.������\n4.�������\n");

				do {
					scanf("%d", &i);
					if (i < 1 || i>4) {
						printf("������� ������ ��� ����������\n");
					}
				} while (i < 1 || i>4);
				if (i >= 1 && i <= 4) {
					pNew->Shipping.Transport = (enum Transport)i;
				}

			}
			int k = 0;
			printf("����� ����� ������ �������� �����?\n");
			scanf("%u", &k);
			if (pRoot == NULL || k < 1) { // ��� ���������� �������� � ������� ��� ��� ������ 
				pNew->pNext = pRoot;      // ������� ������(��� ������ ����), ����� ������ ����� ��������� �
				pRoot = pNew;             // ������ ������
										  // ������ pNew - ������ � ��������� ������� ������, ������� ��������� pNext,
										  // ������������ � �� ������������ � NULL
			}
			else {                                 //���� ������ �� ������, �� ������� ������� ������ �������,
				CardElement* Insert = Find(k - 1); // � ����� ��������� ����� ���� �����
				// ��������� ����� ������� � ������
				pNew->pNext = Insert->pNext;       // ��������� pNew � pNext, ������� ����� ����� Insert
				Insert->pNext = pNew;              // �.� ���������� pNext, ������� ��� � Insert � pNext, ������� ��������� � pNew
												   //����� ���������� pNew � pNext , ������� � Insert
			}
			return pNew;

		}




		free(pNew);       //���������� ������ �������������� ����������


	}

	void CardList() {

		Cards* temp = pRoot;
		int i = 1;
		printf("|�  | ���   |�������|�������|����� � || ������ | CPU      | Memory |         |\n");
		printf("|   |       |       |       |      � || ������ | �������� | ��-��  |         |\n");
		printf("|   |       |       |       |      � || �����  | �������� | ���    |���������|\n");


		while (temp) {
			printf("+---+-------+-------+-------+--------++--------+----------+--------+---------+");
			printf("\n|%-3d|%-7s|%-7s|%-7d|", i, temp->Name, temp->LastName, temp->Age);
			switch (temp->Department) {
			case DEPT_PROGRAMMERS:
				printf("�������.");
				printf("||%-8s|%-10s|%-8d|         |\n", temp->Programmers.Project, temp->Programmers.CPU, temp->Programmers.Memory);
				break;
			case DEPT_MANAGEMENT:
				printf("�������.");
				printf("||%-8s|%-10s|%-8d|         |\n", temp->Management.Project, temp->Management.Customer, temp->Management.ProgrammersNum);
				break;
			case DEPT_SHIPPING:
				printf("��������");
				printf("||%-8s|%-10s|%-8d|", temp->Shipping.Address, temp->Shipping.Customer, temp->Shipping.Weight);
				switch (temp->Shipping.Transport) {
				case TRANSP_TRAIN:
					printf("�����    |\n");
					break;
				case TRANSP_AUTO:
					printf("�����.   |\n");
					break;
				case TRANSP_AERO:
					printf("������  |\n");
					break;
				case TRANSP_SHIP:
					printf("�������  |\n");
					break;
				}
				break;
			}
			temp = temp->pNext; // � temp ���������� ��������� pNext, ���������� � temp
			i++;
		}
		printf("+---+-------+-------+-------+--------++--------+----------+--------+---------+");




	}

	void Delete(int index)    //������� ��� �������� ������ �� �������
	{
		if (pRoot == NULL)   //��������� ������� ������ � �������
		{
			printf("����������� ������ ��� ��������.");
			return;
		}
		if (index == 0)      //���� ������� ��������� ������� �������
		{

			CardElement* pDel = pRoot;//������ ��������� pDel , �������� ��� ������ ������� ��������

			pRoot = pRoot->pNext; //���������� � ���������� �������� � ���������� ������ �� ���� � pRoot

			free(pDel); //������� ������ ������� ��������

		}
		else
		{

			CardElement* pBeforeDel = Find(index - 1); // ������ ��������� pBeforeDel, � ������� ��������� ����� ���������,
													   // �������� ����� ���, ������� �� ����� �������
			if (pBeforeDel->pNext == NULL)return;   //���� ����� ��������� ������� ������  

			CardElement* pDel = pBeforeDel->pNext;  //�� � ����� ���������� �������� ��������� pNext,
													//������� ����� � pBeforeDel (���� �����, �� ��� ����� ����� ���������� ��������)
			if (pDel == NULL)
			{

				printf("����������� ������ ��� ��������.");

				return;

			}

			pBeforeDel->pNext = pDel->pNext; //������������ �����. � pNext, ���������� ������ pBeforeDel
											 //���������� pNext, ����������� � pDel
			free(pDel);                      //����������� ������, ���������� ���������

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


	void SaveToFile() {   //������� ��� ���������� � ����
		char FileName[256];      //������ ���������� ��� ����� �����
		printf("������� ��� �����:\n");
		scanf("%s", &FileName);   //��������� ���� � ����� � ����������

		FILE* saveFile = fopen(FileName, "wb"); //��������� ���� ��� ������ � �������� ����
		if (!saveFile) {                     //��������� �� ������
			printf("�� ������� ������� ����.\n");
			return;
		}
		CardElement* pFile = pRoot;                             //���������� ������
		fwrite(pFile, sizeof(CardElement), 1, saveFile);
		pFile = pFile->pNext;
		while (pFile) {
			fwrite(pFile, sizeof(CardElement), 1, saveFile);
			pFile = pFile->pNext;
		}
		fclose(saveFile);      //��������� �����
	}

	void WriteFromFile() {     //������� ��� ��������� �� �����
		char FileName[256];   //������ ���������� ��� ����� �����
		printf("������� ��� �����:\n");
		scanf("%s", FileName); //��������� ���� � ����� � ����������
		FILE* writeFile = fopen(FileName, "rb"); //��������� ���� ��� ������
		if (!writeFile)       //��������� �������� �����
		{
			printf("�� ������� ������� ����");
			return;
		}

		RemoveAll();

		CardElement* pFile = (CardElement*)malloc(sizeof(CardElement));  //�������� ������ �����������
		if (pFile == NULL)
		{
			printf("�� ������� �������� ������.");  //��������� �� ������
			system("pause");
			return;
		}


		// ���������� ������ �� �����
		CardElement* endElem = pFile;

		fread(pFile, sizeof(CardElement), 1, writeFile);

		pRoot = pFile;


		while (1)
		{
			pFile = (CardElement*)malloc(sizeof(CardElement));
			if (pFile == NULL)
			{
				printf("�� ������� �������� ������");
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
			printf("�������� �������\n1.�������� ����� ������\n2.������� ������\n3.������ � ����\n4.������ �� �����\n5.�����\n");
			scanf("%d", &func);
			if (func == 1) {
				Add();
				CardList();
				printf("\n");
			}
			if (func == 2) {
				int index;
				printf("������� ����� ������, ������� ������ �������:\n");
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
				printf("����� ������� ���. ���������� �����\n");
			}


		} while (func != 5);


	}
