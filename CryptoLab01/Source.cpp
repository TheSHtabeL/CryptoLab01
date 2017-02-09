#include <string>
#include <locale>
#include <iostream>
#include <conio.h>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

void inputSourceFileName(wstring*);
bool readSource(wstring*, wstring*);
int inputLength(int);
void inputKey(vector<int>*, int);
void getReverseKey(vector<int>*, vector<int>*);
void crypt(wstring*, wstring*, vector<int>*);
void outputResult(wstring*, wstring*, wstring*, vector<int>*);
void saveResult(int, wstring*);
void correctText(wstring*, vector<int>*);
void wait();

void main() {
	locale::global(locale("Russian"));
	//wcin.imbue(locale("rus_rus.866"));
	//wcin.imbue(locale("Russian"));
	wstring* sourceFileName = new wstring();
	wstring* text = new wstring();
	wstring* encryptedText = new wstring();
	wstring* decryptedText = new wstring();
	int keyLength; //����� �����
	int correction; //�������� ��� ��������� ������ ����� ������������ (�������� ������ ��������)
	vector<int>* key = new vector<int>(); //���� ��� ����������
	vector<int>* reverseKey = new vector<int>(); //���� ��� ������������

	while (true) {
		text->clear();
		inputSourceFileName(sourceFileName);
		if(!readSource(sourceFileName, text)){
			continue;
		}
		
		if (text->size() > 1) {
			break;
		}
		else {
			wcout << endl << L"���������� ������: ����� ������ � ����� ������ ���� ������ ������ �������.";
			wait();
		}
	}
	keyLength = inputLength(text->size()); //��������� ����� ��� �����
	inputKey(key, keyLength); //������ ����� ����������
	getReverseKey(key, reverseKey); //��������� ����� ������������
	correction = text->size(); //���������� �������������� ����� ��������� ������ ��� ����������� ���������
	correctText(text, key); //��������� ��������� ������
	crypt(text, encryptedText, key); //����������
	crypt(encryptedText, decryptedText, reverseKey); //������������
	outputResult(text, encryptedText, decryptedText, key);
	saveResult(correction, decryptedText);

	delete text;
	delete encryptedText;
	delete decryptedText;
	delete key;
	delete reverseKey;
	delete sourceFileName;
}

void inputSourceFileName(wstring* text) {
	//������� ��������� �����, ��������������� ��� ����������
	wstring temp;

	while (true) {
		system("cls");
		wcout << L"/*----  ������������ ������ �1  ----*/" << endl << endl;
		wcout << L"������� �������� ����� ��� ����������: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"������������ ����� �������� �����. ���������� ��� ���." << endl;
			wait();
		}
	}

	text->assign(temp);
	wcout << endl << L"������ ������������� ��������. ���� ������ ������ �������.";
	wait();
}

bool readSource(wstring* sourceFileName, wstring* text) {
	//������� ������ �������� ����� �� �����
	wifstream file(sourceFileName->data());
	wchar_t* byte = new wchar_t();

	if (file.fail()) {
		wcout << endl << L"������ ��� �������� �����";
		wait();
		text->clear();
		return false;
	}
	while ( file.read( byte, 1 ) ) { //������������ ������ �����
		text->push_back(*byte);
	}
	file.close();
	
	delete byte;
	return true;
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
	//������� ������ �����
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
				cout << (key->at(i)+1) << " ";
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
					if ( element == (key->at(j)+1) ) {
						throw (-2);
					}
				}
				key->push_back(element-1);
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

void getReverseKey(vector<int>* key, vector<int>* reverseKey) {
	//�������� ��� ��� ���������� �� ��������� �����
	for ( unsigned int i = 0; i < key->size(); i++ ) {
		for ( unsigned int j = 0; j < key->size(); j++ ) {
			if (i == key->at(j)) {
				reverseKey->push_back(j);
				break;
			}
		}
	}
}

void crypt(wstring* text, wstring* newText, vector<int>* key) {
	//������� ���������� ������ ���������� ������
	//���������� ������ ��������� �� �������
	int cycleCount = text->size() / key->size();
	
	//���������� ������ �� �����
	for ( int i = 0; i < cycleCount; i++ ) {
		for (unsigned int j = 0; j < key->size(); j++) {
			newText->push_back(text->at(key->at(j) + ((key->size()) * i)));
		}
	}

	return;
}

void outputResult(wstring* text, wstring* encryptedText, wstring* decryptedText,vector<int>* key) {
	system("cls");
	wcout << L"/*----  ������������ ������ �1  ----*/" << endl << endl;
	wcout << endl << L"����: ";
	for (unsigned int i = 0; i < key->size(); i++) {
		cout << (key->at(i)+1) << " ";
	}
	cout << endl;
	wcout << endl << L"�������� �����: " << text->data() << endl;
	wcout << endl << L"������������� �����: " << encryptedText->data() << endl;
	wcout << endl << L"������������� �����: " << decryptedText->data() << endl;
	wait();
}

void saveResult(int sourceTextLength, wstring* decryptedText) {
	//���������� ���������� ���������� � ��������� �����
	wofstream file("target.txt");
	int count = (decryptedText->size() - sourceTextLength);

	for(int i = 0; i < count; i++){ //������� ��������� �� ��������, ����������� ��� ��������
		decryptedText->pop_back();
	}

	file.write(decryptedText->data(), decryptedText->size());
	file.close();
}

void correctText(wstring* text, vector<int>* key) {
	//����� ����������� ���������, ����� ���������� ��� �������� ����� ������� ����� �����
	int cycleCount = text->size() / key->size();
	int spaceCount = (key->size() * (cycleCount + 1)) - text->size();

	if (spaceCount != 0) {
		cycleCount++;
		for (int i = 0; i < spaceCount; i++) {
			text->append(L" ");
		}
	}
}

void wait() {
	wcout << endl << L"������� ����� ������� ��� �����������...";
	_getch();
}