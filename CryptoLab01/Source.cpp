#include <string>
#include <locale>
#include <iostream>
#include <conio.h>

using namespace std;

void inputText(wstring*);
int inputLength();
void inputKey(int*);
void decrypt(wstring*, int, int*);

void main() {
	wstring* text = new wstring();
	int length;
	int* key;
	
	inputText(text);
	length = inputLength();
	key = new int[length];
	inputKey(key);
	decrypt(text, length, key);

	wcout << endl << L"Дешифрованный текст: " << text;
	wcout << endl << endl << "Нажмите любую клавишу для выхода...";
	_getch();
}

void inputText(wstring* text) {

}

int inputLength() {
	return 0;
}

void inputKey(int* key) {
	
}

void decrypt(wstring* text, int length, int* key) {

}