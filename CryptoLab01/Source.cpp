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
void crypt(wstring*, wstring*, vector<int>*);
void outputResult(wstring*, wstring*, vector<int>*);
void wait();

void main() {
	setlocale(LC_ALL, "Russian");
	wcin.imbue(locale("rus_rus.866"));
	wstring* text = new wstring();
	wstring* newText = new wstring();
	int keyLength;
	vector<int>* key = new vector<int>();

	inputText(text);
	keyLength = inputLength(text->size());
	inputKey(key, keyLength);
	crypt(text, newText, key);
	outputResult(text, newText, key);

	delete text;
	delete newText;
	delete key;
}

void inputText(wstring* text) {
	//Функция считывает текст, предназначенные для шифрования
	wstring temp;

	while (true) {
		system("cls");
		wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
		wcout << L"Введите текст для шифрования: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"Недопустимая длина текста. Попробуйте ещё раз." << endl;
			wait();
		}
	}

	text->assign(temp);
	wcout << endl << L"Данные удовлетворяют условиям. Ввод данных прошёл успешно.";
	wait();
}

int inputLength(int textLength) {
	//Функция, получающая размер ключевой комбинации
	int keyLength;
	string temp;

	while (true) {
		system("cls");
		wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
		wcout << L"Длина кодируемого текста: " << textLength << endl
			<< L"Введите размер ключа: ";
		getline(cin, temp);

		try {
			keyLength = stoi(temp); //Конвертация string -> int
			if (keyLength > textLength) {
				throw (-1);
			}
			else if (keyLength <= 1) {
				throw 0;
			}
			else {
				wcout << endl << L"Данные удовлетворяют условиям. Ввод данных прошёл успешно.";
				wait();
				break;
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"Ошибка ввода: на вход поданы некорректные данные. Введите целочисленное значение.";
		}
		catch (out_of_range e) {
			wcout << endl << L"Переполнение: значение на входе слишком велико. Попробуйте ещё раз.";
		}
		catch (int e) {
			switch (e) {
			case (-1):
				wcout << endl << L"Логическая ошибка: длина ключа должна быть меньше или равна длине кодируемого текста. Попробуйте ещё раз.";
				break;
			case 0:
				wcout << endl << L"Логическая ошибка: длина ключа должна быть больше единицы. Попробуйте ещё раз.";
				break;
			}
		}

		wait();
	}

	return keyLength;
}

void inputKey(vector<int>* key, int keyLength) {
	//Функция чтения ключа
	string temp;
	int element;

	while ( key->size() < keyLength) {
		//Вспомогательная информация интерфейса
		system("cls");
		wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
		wcout << L"Длина ключа: " << keyLength << endl;
		wcout << L"Элементы ключа: ";

		if (!key->empty()) {
			for (unsigned int i = 0; i < key->size(); i++) {
				cout << (key->at(i)+1) << " ";
			}
			cout << endl << endl;
		}
		else {
			wcout << L"ни одного элемента не введено" << endl << endl;
		}

		wcout << L"Введите новый элемент ключа: ";
		getline(cin, temp);

		//Обработка полученных на вход данных для конвертации в int
		try {
			element = stoi(temp); //Конвертация string -> int
			if (element > keyLength) {
				throw (-1);
			}
			else if (element <= 0) {
				throw 0;
			}
			else {
				for (unsigned int j = 0; j < key->size(); j++) { //Проверка уникальности нового элемента
					if ( element == (key->at(j)+1) ) {
						throw (-2);
					}
				}
				key->push_back(element-1);
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"Ошибка ввода: на вход поданы некорректные данные. Введите целочисленное значение." << endl;
			wait();
		}
		catch (out_of_range e) {
			wcout << endl << L"Переполнение: значение на входе слишком велико. Попробуйте ещё раз." << endl;
			wait();
		}
		catch (int a) {
			switch (a) {
			case (-1):
				wcout << endl << L"Логическая ошибка: новый элемент ключа должен быть меньше или равен длине ключа. Попробуйте ещё раз." << endl;
				break;
			case 0:
				wcout << endl << L"Логическая ошибка: элемент должен быть положительным и не равен нулю. Попробуйте ещё раз." << endl;
				break;
			case (-2):
				wcout << endl << L"Логическая ошибка: элемент должен отсутствовать среди уже введённых. Попробуйте ещё раз." << endl;
				break;
			}
			wait();
		}
		
	}
	wcout << endl << L"Данные удовлетворяют условиям. Ввод данных прошёл успешно.";
	wait();
}

void crypt(wstring* text, wstring* newText, vector<int>* key) {
	//Функция шифрования текста полученным ключом
	//Дополнение текста пробелами по заданию
	int cycleCount = text->size() / key->size();
	int spaceCount = (key->size() * (cycleCount+1)) - text->size();

	if (spaceCount != 0) {
		cycleCount++;
		for (int i = 0; i < spaceCount; i++) {
			text->append(L" ");
		}
	}
	
	//Шифрование текста по ключу
	for ( int i = 0; i < cycleCount; i++ ) {
		for (unsigned int j = 0; j < key->size(); j++) {
			newText->push_back(text->at(key->at(j) + ((key->size()) * i)));
		}
	}
}

void outputResult(wstring* text, wstring* newText, vector<int>* key) {
	system("cls");
	wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
	wcout << endl << L"Ключ: ";
	for (unsigned int i = 0; i < key->size(); i++) {
		cout << (key->at(i)+1) << " ";
	}
	cout << endl;
	wcout << endl << L"Исходный текст: " << text->data() << endl;
	wcout << endl << L"Дешифрованный текст: " << newText->data() << endl;
	wait();
}

void wait() {
	wcout << endl << L"Нажмите любую клавишу для продолжения...";
	_getch();
}