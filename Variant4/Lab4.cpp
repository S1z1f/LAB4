#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
class Book {    //Объявление класса
    string author;  //ФИО
    string name;    //Название книги
    string publisger;   //Издательство
    int year;   //Год выпуска
    int pages;  //Количество страниц
public:
    Book() {    //Конструктор создаёт пустые поля
        author = ""; name = ""; publisger = ""; year = 0; pages = 0;
    }
    Book(string author, string name, string publisger, int year, int pages) {   //Конструктор с параметрами
        this->author = author; this->name = name; this->publisger = publisger; this->year = year; this->pages = pages;
    // Присваеваем полям значения
    }
    bool operator<(const Book& b) const {   // Перегрузка оператора "<"
        return author < b.author;   // Сравниваем книги по алфавиту по полю ФИО автора
    }
    friend ostream& operator<<(ostream& out, const Book& b);    // Объявление дружественной функции для перегрузки оператора вывода
};
ostream& operator <<(ostream & out, const Book & b) {   // Реализация перегруженного оператора
    out<< "   Автор: " << b.author << "." << endl << "Название книги: " <<  b.name << "." << endl << "Издательство: " << b.publisger << "." << endl << "Год издания: " << b.year << "."<< endl << "Количество страниц: " << b.pages;
    //Записываем значения в файл
    return out;
}
int main() {
    ifstream fin("input.txt");  //Открываем файл со значениями
    ofstream fout("output.txt");    //Открываем файл для записи результатов
    int n;  //Количество книг
    fin >> n;   //Считаем количество книг из исходного файла
    fin.ignore(2, '\n');    // Очистка буфера от символа переноса строки после числа
    list<Book> items;   // Создание исходного контейнера
    for (int i=0; i < n; i++) {     //Перебираем данные из файла
        string author, name, publisger;
        int year, pages;
        getline(fin, author);   //Построчное чтение данных
        getline(fin, name);
        getline(fin, publisger);
        fin >> year >> pages;
        fin.ignore(2, '\n');
        items.push_back(Book(author, name, publisger, year, pages));    // Создание объекта Book и добавление его в конец списка данные
    }
    vector<Book> copy_items(items.size());  // Создание вектора copy_items такого же размера, как и список
    copy(items.begin(), items.end(), copy_items.begin());   // Копирование всех элементов из list в vector
    fout << "Исходный контейнер (list):" << endl;   //Вывод в файл
    for (const Book& b : items) fout << b << endl;     // Вывод каждого элемента
    items.sort();   //Сортировка
    fout << endl << "Контейнер после сортировки: " << endl; // Вывод в файл контейнера после сортировки
    for (const Book& b : items) fout << b << endl;
    fout << endl << "Копия исходного контейнера: " << endl; // Вывод в файл скопированного вектора
    for (const Book& b : copy_items) fout << b << endl;
    if (n>0) {  // Демонстрация работы конструктора копирования и оператора присваивания
        Book first = items.front(); // Вызов конструктора копирования
        Book other;     // Вызов конструктора по умолчанию
        other = first;  // Вызов перегруженного оператора присваивания с копированием
        // Вывод результатов
        fout << endl << "Конструктор копирования: " << endl << first << endl;
        fout << endl << "Выполнение конструкта: " << endl << other << endl;
    }
    return 0;
}
