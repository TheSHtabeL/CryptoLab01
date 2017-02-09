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
	int keyLength; //Длина ключа
	int correction; //Величина для коррекции текста после дешифрования (удаление лишних пробелов)
	vector<int>* key = new vector<int>(); //Ключ для шифрования
	vector<int>* reverseKey = new vector<int>(); //Ключ для дешифрования

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
			wcout << endl << L"Логическая ошибка: длина текста в файле должна быть больше одного символа.";
			wait();
		}
	}
	keyLength = inputLength(text->size()); //Получение длины для ключа
	inputKey(key, keyLength); //Чтение ключа шифрования
	getReverseKey(key, reverseKey); //Получение ключа дешифрования
	correction = text->size(); //Сохранение первоначальной длины исходного текста для последующей коррекции
	correctText(text, key); //Коррекция исходного текста
	crypt(text, encryptedText, key); //Шифрование
	crypt(encryptedText, decryptedText, reverseKey); //Дешифрование
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
	//Функция считывает текст, предназначенные для шифрования
	wstring temp;

	while (true) {
		system("cls");
		wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
		wcout << L"Введите названия файла для шифрования: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"Недопустимая длина названия файла. Попробуйте ещё раз." << endl;
			wait();
		}
	}

	text->assign(temp);
	wcout << endl << L"Данные удовлетворяют условиям. Ввод данных прошёл успешно.";
	wait();
}

bool readSource(wstring* sourceFileName, wstring* text) {
	//Функция читает исходный текст из файла
	wifstream file(sourceFileName->data());
	wchar_t* byte = new wchar_t();

	if (file.fail()) {
		wcout << endl << L"Ошибка при открытии файла";
		wait();
		text->clear();
		return false;
	}
	while ( file.read( byte, 1 ) ) { //Посимвольное чтение файла
		text->push_back(*byte);
	}
	file.close();
	
	delete byte;
	return true;
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

void getReverseKey(vector<int>* key, vector<int>* reverseKey) {
	//Вынимает код для дешифрации из исходного ключа
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
	//Функция шифрования текста полученным ключом
	//Дополнение текста пробелами по заданию
	int cycleCount = text->size() / key->size();
	
	//Шифрование текста по ключу
	for ( int i = 0; i < cycleCount; i++ ) {
		for (unsigned int j = 0; j < key->size(); j++) {
			newText->push_back(text->at(key->at(j) + ((key->size()) * i)));
		}
	}

	return;
}

void outputResult(wstring* text, wstring* encryptedText, wstring* decryptedText,vector<int>* key) {
	system("cls");
	wcout << L"/*----  Лабораторная работа №1  ----*/" << endl << endl;
	wcout << endl << L"Ключ: ";
	for (unsigned int i = 0; i < key->size(); i++) {
		cout << (key->at(i)+1) << " ";
	}
	cout << endl;
	wcout << endl << L"Исходный текст: " << text->data() << endl;
	wcout << endl << L"Зашифрованный текст: " << encryptedText->data() << endl;
	wcout << endl << L"Дешифрованный текст: " << decryptedText->data() << endl;
	wait();
}

void saveResult(int sourceTextLength, wstring* decryptedText) {
	//Сохранение результата дешифрации в отдельном файле
	wofstream file("target.txt");
	int count = (decryptedText->size() - sourceTextLength);

	for(int i = 0; i < count; i++){ //Убираем коррекцию из пробелов, добавленную при шифрации
		decryptedText->pop_back();
	}

	file.write(decryptedText->data(), decryptedText->size());
	file.close();
}

void correctText(wstring* text, vector<int>* key) {
	//Текст дополняется пробелами, чтобы количество его символов стало кратным длине ключа
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
	wcout << endl << L"Нажмите любую клавишу для продолжения...";
	_getch();
}