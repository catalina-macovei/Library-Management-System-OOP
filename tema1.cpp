#include <iostream>
#include <cstring>
using namespace std;

/**MyString:
 * Clasa care retine un sir de caractere alocat dinamic,
 * adica un pointer la un tablou unidimensional de char, alocat dinamic
 * */
class MyString {
    int size;
    char *data;
public:
    /// Constructorul care imi seteaza sirul null
    MyString();

    /// Constructorul care seteaza sirul nevid
    MyString(const char *str);

    /// Constructorul de copiere
    MyString(const MyString &str);

    /// Operator overloading pentru afisarea sirului
    friend std::ostream& operator<<(std::ostream& out, const MyString& nume);

    /// Dezalocarea memoriei din data []
    ~MyString();

    /// Operator overloading pentru copierea stringului
    MyString& operator=(const MyString& str);
};

MyString::MyString() : data(NULL), size(0) {}

MyString::MyString( const char *str) {
        this->size = strlen(str);
        this->data = new char [size];
        for (int i = 0; i < size; i++) {
            strcpy(data, str);
        }
    }
MyString& MyString::operator=(const MyString& str) {
    if (this == &str) {
        return *this;       //protect against self assignment (v = v)
    }
    delete this->data;      //delete the allocated memory
    this->data = new char [str.size];
    for (int i = 0; i < str.size; i++) {
        this->data[i] = str.data[i];
    }
    this->size = str.size;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const MyString& nume) {
        for (int i = 0; i < nume.size; i++) {
            out << nume.data[i];
        }
    return out;
    }
MyString::~MyString() { //daca nu e null deja
    if (data != NULL) {
        delete[] data;
    }
}
MyString::MyString(const MyString &str) {
    this -> size = str.size;
    this -> data = str.data;
    for (int i = 0; i < str.size; i++) {
        this -> data[i] = str.data[i];
    }
}
/**
 * Clasa Book
 * Aici voi pastra datele pentru fiecare carte sub forma (titlu, editura, autor, gen/categorie, pret)
 * */
class Book{
    MyString title;
    MyString publisher;
    MyString author;
    MyString section;
    int price;
public:
      Book();
      Book(const MyString &title1, const MyString &publisher1, const MyString& author1, const MyString& section1, int price1);
      /// Operator overloading pentru afisarea obiectului Book
      friend ostream& operator<<(std::ostream& out, const Book& new_book);
};

Book::Book() : title(NULL), publisher(NULL), author(NULL), section(NULL), price(0) {}

Book::Book(const MyString &title1, const MyString &publisher1, const MyString &author1, const MyString &section1, int price1) {
    title = title1;
    publisher = publisher1;
    author = author1;
    section = section1;
    price = price1;
}

ostream& operator<<(std::ostream& out, const Book& new_book) {
    out << "Titlu: " << new_book.title << endl;
    out << "Editura: " << new_book.publisher << endl;
    out << "Autor: " << new_book.author << endl;
    out << "Gen: " << new_book.section << endl;
    out << "Pret: " << new_book.price << " lei" << endl;
    return out;
}

/**               Customer Start                         */

class Customer {
    MyString name;
    MyString client_type; // Efficient/Traditional - clients become efficient if they have more than 2 orders
    Book book;
    int nr_of_orders;
    int customer_id;
};

class Employee {
    MyString name;
    MyString role;
    int employee_id;
    int salary;
};

class Bookstore {
    MyString name;
    MyString adress;
    Book book;
    Employee employee;
    Customer customer;
};

int main() {
    Book book("Padurea Spanzuratilor", "Prut", "nume autor", "thriller", 233);
    cout << book;
    return 0;
}