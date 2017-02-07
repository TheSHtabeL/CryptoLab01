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

	wcout << endl << L"Дешифрованный текст: " << text;
	wait();
}

void inputText(wstring* text) {
	//Функция считывает текст, предназначенные для шифрования
	wstring temp;

	while (true) {
		wcout << L"Введите текст для шифрования: ";
		getline(wcin, temp);
		if (temp.size() > 1) {
			break;
		}
		else {
			wcout << endl << L"Недопустимая длина текста. Попробуйте ещё раз." << endl;
		}
	}
	text->assign(temp);
	wait();
}

int inputLength(int textLength) {
	//Функция, получающая размер ключевой комбинации
	int keyLength;
	string temp;

	system("cls");
	while (true) {
		wcout << L"Длина кодируемого текста: " << textLength << endl
			<< L"Введите размер ключа: ";
		getline(cin, temp);
		try {
			keyLength = stoi(temp); //Конвертация 
			if (keyLength > textLength) {
				throw (-1);
			}
			else {
				break;
			}
		}
		catch (invalid_argument e) {
			wcout << endl << L"Ошибка ввода: на вход поданы некорректные данные. Введите целочисленное значение." << endl;
		}
		catch (out_of_range e) {
			wcout << endl << L"Переполнение: значение на входе слишком велико. Попробуйте ещё раз." << endl;
		}
		catch ( int ) {
			wcout << endl << L"Логическая ошибка: длина ключа должна быть меньше или равна длине кодируемого текста. Попробуйте ещё раз." << endl;
		}
	}
	
	return keyLength;
}

void inputKey(vector<int>* key, int length) {
	
}

void decrypt(wstring* text, int length, vector<int>* key) {

}

void wait() {
	wcout << endl << endl << L"Нажмите любую клавишу для продолжения...";
	_getch();
}