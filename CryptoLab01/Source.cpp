#include <string>
#include <locale>
#include <iostream>
#include <conio.h>
#include <vector>
#include <conio.h>

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

	wcout << endl << L"������������� �����: " << text;
	wait();
}

void inputText(wstring* text) {
	//������� ��������� �����, ��������������� ��� ����������
	wstring temp;

	while (true) {
		wcout << L"������� ����� ��� ����������: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"������������ ����� ������. ���������� ��� ���." << endl;
		}
	}
	text->assign(temp);
	wait();
}

int inputLength(int textLength) {
	//�������, ���������� ������ �������� ����������
	int keyLength;
	string temp;

	system("cls");
	while (true) {
		wcout << L"����� ����������� ������: " << textLength << endl
			<< L"������� ������ �����: ";
		getline(cin, temp);
		try {
			keyLength = stoi(temp); //����������� 
			if (keyLength > textLength) {
				throw (-1);
			}
			else {
				break;
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"������ �����: �� ���� ������ ������������ ������. ������� ������������� ��������." << endl;
		}
		catch (out_of_range e) {
			wcout << endl << L"������������: �������� �� ����� ������� ������. ���������� ��� ���." << endl;
		}
		catch ( int ) {
			wcout << endl << L"���������� ������: ����� ����� ������ ���� ������ ��� ����� ����� ����������� ������. ���������� ��� ���." << endl;
		}
	}
	
	return keyLength;
}

void inputKey(vector<int>* key, int length) {
	
}

void decrypt(wstring* text, int length, vector<int>* key) {

}

void wait() {
	wcout << endl << endl << L"������� ����� ������� ��� �����������...";
	_getch();
}