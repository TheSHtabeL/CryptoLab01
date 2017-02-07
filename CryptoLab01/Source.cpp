#include <string>
#include <locale>
#include <iostream>
#include <conio.h>
#include <vector>
#include <conio.h>
#include <list>

using namespace std;

void inputText(wstring*);
int inputLength(int);
void inputKey(vector<int>*, int);
void decrypt(wstring*, int, vector<int>*);
void wait();

void main() {
	setlocale(LC_ALL, "Russian");
	wstring* text = new wstring();
	int keyLength;
	vector<int>* key = new vector<int>();

	inputText(text);
	keyLength = inputLength(text->size());
	inputKey(key, keyLength);
	decrypt(text, keyLength, key);

	wcout << endl << L"������������� �����: " << text->data();
	wait();
}

void inputText(wstring* text) {
	//������� ��������� �����, ��������������� ��� ����������
	wstring temp;

	while (true) {
		system("cls");
		wcout << L"/*----  ������������ ������ �1  ----*/" << endl << endl;
		wcout << L"������� ����� ��� ����������: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"������������ ����� ������. ���������� ��� ���." << endl;
			wait();
		}
	}

	text->assign(temp);
	wcout << endl << L"������ ������������� ��������. ���� ������ ������ �������.";
	wait();
}

int inputLength(int textLength) {
	//�������, ���������� ������ �������� ����������
	int keyLength;
	string temp;

	while (true) {
		system("cls");
		wcout << L"/*----  ������������ ������ �1  ----*/" << endl << endl;
		wcout << L"����� ����������� ������: " << textLength << endl
			<< L"������� ������ �����: ";
		getline(cin, temp);

		try {
			keyLength = stoi(temp); //����������� string -> int
			if (keyLength > textLength) {
				throw (-1);
			}
			else if (keyLength <= 1) {
				throw 0;
			}
			else {
				wcout << endl << L"������ ������������� ��������. ���� ������ ������ �������.";
				wait();
				break;
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"������ �����: �� ���� ������ ������������ ������. ������� ������������� ��������.";
		}
		catch (out_of_range e) {
			wcout << endl << L"������������: �������� �� ����� ������� ������. ���������� ��� ���.";
		}
		catch (int e) {
			switch (e) {
			case (-1):
				wcout << endl << L"���������� ������: ����� ����� ������ ���� ������ ��� ����� ����� ����������� ������. ���������� ��� ���.";
				break;
			case 0:
				wcout << endl << L"���������� ������: ����� ����� ������ ���� ������ �������. ���������� ��� ���.";
				break;
			}
		}

		wait();
	}

	return keyLength;
}

void inputKey(vector<int>* key, int keyLength) {
	string temp;
	int element;

	while ( key->size() < keyLength) {
		//��������������� ���������� ����������
		system("cls");
		wcout << L"/*----  ������������ ������ �1  ----*/" << endl << endl;
		wcout << L"����� �����: " << keyLength << endl;
		wcout << L"�������� �����: ";

		if (!key->empty()) {
			for (unsigned int i = 0; i < key->size(); i++) {
				cout << key->at(i) << " ";
			}
			cout << endl << endl;
		}
		else {
			wcout << L"�� ������ �������� �� �������" << endl << endl;
		}

		wcout << L"������� ����� ������� �����: ";
		getline(cin, temp);

		//��������� ���������� �� ���� ������ ��� ����������� � int
		try {
			element = stoi(temp); //����������� string -> int
			if (element > keyLength) {
				throw (-1);
			}
			else if (element <= 0) {
				throw 0;
			}
			else {
				for (unsigned int j = 0; j < key->size(); j++) { //�������� ������������ ������ ��������
					if (element == key->at(j)) {
						throw (-2);
					}
				}
				key->push_back(element);
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"������ �����: �� ���� ������ ������������ ������. ������� ������������� ��������." << endl;
			wait();
		}
		catch (out_of_range e) {
			wcout << endl << L"������������: �������� �� ����� ������� ������. ���������� ��� ���." << endl;
			wait();
		}
		catch (int a) {
			switch (a) {
			case (-1):
				wcout << endl << L"���������� ������: ����� ������� ����� ������ ���� ������ ��� ����� ����� �����. ���������� ��� ���." << endl;
				break;
			case 0:
				wcout << endl << L"���������� ������: ������� ������ ���� ������������� � �� ����� ����. ���������� ��� ���." << endl;
				break;
			case (-2):
				wcout << endl << L"���������� ������: ������� ������ ������������� ����� ��� ��������. ���������� ��� ���." << endl;
				break;
			}
			wait();
		}
		
	}
	wcout << endl << L"������ ������������� ��������. ���� ������ ������ �������.";
	wait();
}

void decrypt(wstring* text, int length, vector<int>* key) {
	
}

void wait() {
	wcout << endl << L"������� ����� ������� ��� �����������...";
	_getch();
}