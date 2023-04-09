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
        if(str != NULL){
            this->size = strlen(str);
            this->data = new char [size + 1];
            strcpy(data, str);
            this->data[size] = '\0';
        }
    }
MyString& MyString::operator=(const MyString& str) {
    if (this == &str) {
        return *this;       //protect against self assignment (v = v)
    }
    //delete [] data;      //delete the allocated memory
    this->data = new char [str.size + 1];
    strncpy(this->data, str.data, str.size);
    this->size = str.size;
    this->data[size] = '\0';
    return *this;
}
std::ostream& operator<<(std::ostream& out, const MyString& nume) {
        for (int i = 0; i < nume.size; i++) {
            out << nume.data[i];
        }
    return out;
    }

MyString::MyString(const MyString &str) {
    this->data = new char [str.size + 1];
    strncpy(this->data, str.data, str.size);
    this->data[size] = '\0';
}

MyString::~MyString() { //daca nu e null deja
    if (data != NULL) {
        delete [] data;
    }
}

/**
 * Clasa Book
 * Aici voi pastra datele pentru fiecare carte sub forma (titlu, editura, autor, gen/categorie, pret)
 * */
class Book {
    MyString title;
    MyString publisher;
    MyString author;
    MyString section;
    int price;
    Book *books;        // necesara supraincarcrea op =
    int Max_books;     // nr carti ptr lista
public:
    Book();

    Book(const MyString &title1, const MyString &publisher1, const MyString &author1, const MyString &section1,
         int price1);

    ~Book();

    Book(const MyString &title1, const MyString &author1);

    /// Operator overloading pentru afisarea obiectului Book
    friend ostream &operator<<(std::ostream &out, const Book &new_book);

    Book(const Book &book);

    Book &operator=(const Book &book);

    Book *getBooks();
};

Book::Book() : title(NULL), publisher(NULL), author(NULL), section(NULL), price(0) {}

Book::Book(const MyString &title1, const MyString &publisher1, const MyString &author1, const MyString &section1, int price1) {
    title = title1;
    publisher = publisher1;
    author = author1;
    section = section1;
    price = price1;
}
Book::Book(const MyString &title1, const MyString &author1) {
    title = title1;
    author = author1;
}
ostream& operator<<(std::ostream& out, const Book& new_book) {
    out << "Titlu: " << new_book.title << endl;
    out << "Editura: " << new_book.publisher << endl;
    out << "Autor: " << new_book.author << endl;
    out << "Gen: " << new_book.section << endl;
    out << "Pret: " << new_book.price << " lei" << endl;
    return out;
}

Book& Book::operator=(const Book& book) {
    if (this == &book) {
        return *this;       //protect against self assignment (v = v)
    }
    this->title = book.title;
    this->publisher = book.publisher;
    this->author = book.author;
    this->section = book.section;
    this->price = book.price;
    return *this;
}
Book::Book(const Book &book) {
    this->title = book.title;
    this->publisher = book.publisher;
    this->author = book.author;
    this->section = book.section;
    this->price = book.price;
}

Book *Book::getBooks() {              // metoda returneaza o lista de carti de tip Book, cu proprietatile titlu & autor
    cout << "nr carti: " << endl;
    /*
    cin >> Max_books;
    cin.ignore();
     */
    Max_books = 2;

    if (Max_books > 0) {
        Book* books = new Book[Max_books];
        for (int i = 0; i < Max_books; i++) {
            char titlu[50];
            char autor[50];
            char editura[50];
            char gen[20];
            int pret;

            cout << "Book name: " << endl;
            cin.getline(titlu, 50);
            cout << "Author name:" << endl;
            cin.getline(autor, 50);
            cout << "Publisher name: " << endl;
            cin.getline(editura,50);
            cout << "Gender of the book: " << endl;
            cin.getline(gen, 20);
            cout << "Price: ";
            cin >> pret;
            books[i] = Book(titlu, autor, editura, gen, pret);

            cin.ignore();
        }
        // continuare ... pentru afisare:
        for (int i = 0; i < Max_books; i++) {
            cout << "Cartea " << i + 1 << ": " << endl << books[i] << endl;
        }

    }
}
Book::~Book() {
    if (books != NULL) {
        delete [] books;
    }
}
/**   Clasa Customer:
 * Aici e clasa Customer cu proprietatile: name, client_type, book, nr_of_orders, customer_id
 * */
class Customer {
    MyString name;
    MyString client_type; // Efficient/Traditional - clients become efficient if they have more than 2 orders
    Book* book;
    int nr_of_orders;
    int customer_id;

public:
    Customer();
    Customer(int customer_id1, const MyString &name1, const MyString &client_type1, Book* book1, int nr_of_orders1);

    /// Operator overloading '=' pentru customer
    Customer& operator=(const Customer& customer);

    /// Copy constructor down here:
    Customer(const Customer& customer);

    /// Operator overloading pentru afisarea obiectului Customer
    friend ostream& operator<<(std::ostream& out, const Customer& new_customer);
};
Customer::Customer() : customer_id(0), name(NULL), client_type(NULL), book(NULL), nr_of_orders(0){}

Customer::Customer(int customer_id1, const MyString &name1, const MyString &client_type1, Book* book1, int nr_of_orders1) {
    customer_id = customer_id1;
    name = name1;
    client_type = client_type1;
    book = book1->getBooks();
    nr_of_orders = nr_of_orders1;
}

Customer::Customer(const Customer& customer) {
    this->customer_id = customer.customer_id;
    this->name = customer.name;
    this->client_type = customer.client_type;
    this->book = customer.book;
    this->nr_of_orders = customer.nr_of_orders;
}

Customer& Customer::operator=(const Customer &customer) {
    if (this == &customer) {
        return *this;           // self assignment
    }
    this->customer_id = customer.customer_id;
    this->name = customer.name;
    this->client_type = customer.client_type;
    this->book = customer.book;
    this->nr_of_orders = customer.nr_of_orders;
    return *this;
}

ostream& operator<<(std::ostream& out, const Customer& new_customer) {
    out << "Customer ID: " << new_customer.customer_id << endl;
    out << "Name: " << new_customer.name << endl;
    out << "Client type: " << new_customer.client_type << endl;
    out << "Book: " << new_customer.book << endl;
    out << "Nr of orders: " << new_customer.nr_of_orders << endl;
    return out;
}


/** Clasa Employee:
 * Fiecare angajat va fi inregistrat sub forma: (nume, rol, ID, salary)
 * */
class Employee {
    MyString name;
    MyString role;
    int employee_id;
    int salary;
public:
    Employee();
    Employee(int employee_id1, const MyString &name1, const MyString &role1, int salary1);
    Employee& operator=(const Employee& employee);
    Employee(const Employee &employee);
    friend ostream& operator<<(std::ostream& out, const Employee& new_employee);
};

Employee::Employee() : employee_id(0), name(NULL), role(NULL), salary(0)  {}

Employee::Employee(int employee_id1, const MyString &name1, const MyString &role1, int salary1) {
    employee_id = employee_id1;
    name = name1;
    role = role1;
    salary = salary1;
}

Employee& Employee::operator=(const Employee& employee) {
    if (this == &employee) {
        return *this;       //protect against self assignment (v = v)
    }
    this->employee_id = employee.employee_id;
    this->name = employee.name;
    this->role = employee.role;
    this->salary = employee.salary;
    return *this;
}

Employee::Employee(const Employee &employee) {
    this->employee_id = employee.employee_id;
    this->name = employee.name;
    this->role = employee.role;
    this->salary = employee.salary;
}

ostream& operator<<(std::ostream& out, const Employee& new_employee) {
    out << "Employee ID: " << new_employee.employee_id << endl;
    out << "Employee name: " << new_employee.name << endl;
    out << "Employee role: " << new_employee.role << endl;
    out << "Employee salary: " << new_employee.salary << " lei" << endl;
    return out;
}

class Bookstore {
    MyString name;          // unique
    MyString address;       // unique
    Book book;              // a list of books needed
    Employee employee;      // a list of employees and their roles needed
    Customer customer;      // a list of customers needed
};

int main() {
    Book* books;
    Book book1("Padurea Spanzuratilor", "Prut", "nume autor", "thriller", 233);
    Book book("xax", "xax");            // initializare
    Customer customer(101, "NUME PRENUME", "TIP CLIENT", books, 2);
    Employee employee(201, "N P", "rol", 5000);

    cout << book1 << endl;
    cout << customer << endl;
    cout << employee << endl;

    return 0;
}
//int customer_id1, const MyString &name1, const MyString &client_type1, Book* book1, int nr_of_orders1