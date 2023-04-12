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

    /// Operator overloading pentru citirea sirului
    friend istream& operator>>(std::istream& is, MyString& str);

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
        return *this;                       //protect against self assignment (v = v)
    }
    delete [] data;                         //delete the allocated memory          !!!!!!
    this->data = new char [str.size + 1];
    strncpy(this->data, str.data, str.size);
    this->size = str.size;
    this->data[size] = '\0';
    return *this;
}
std::ostream& operator<<(std::ostream& out, const MyString& str) {
        for (int i = 0; i < str.size; i++) {
            out << str.data[i];
        }
    return out;
    }
std::istream& operator>>(std::istream& is, MyString& str) {
    str.size = 50;
    str.data = new char [50];
    is.getline(str.data, 50);
    return  is;
}
MyString::MyString(const MyString &str) {
    this->data = new char [str.size + 1];
    strncpy(this->data, str.data, str.size);
    this->size = str.size;
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
    MyString author;
    int price;
public:
    Book();

    Book(const MyString title1, const MyString author1, int price1);

    friend ostream &operator<<(ostream &out, const Book &new_book);

    Book(const Book &book);

    Book &operator=(const Book &book);
};

Book::Book() : title(NULL), author(NULL)  {}

Book::Book(const MyString title1, const MyString author1, int price1) : price(price1), title(title1), author(author1){}

ostream& operator<<(ostream& out, const Book& book) {
    out << "Title: " << book.title << endl;
    out << "Author: " << book.author << endl;
    out << "Price: " << book.price << " lei" << endl;
    return out;
}


Book& Book::operator=(const Book& book) {
    if (this == &book) {
        return *this;       //protect against self assignment (v = v)
    }
    this->title = book.title;
    this->author = book.author;
    this->price = book.price;
    return *this;
}
Book::Book(const Book& book) {
    this->title = book.title;
    this->author = book.author;
    this->price = book.price;
}
/**   Clasa Customer:
 * Aici e clasa Customer cu proprietatile: name, client_type, book, nr_of_orders, customer_id
 * */
class Customer {
    MyString name;
    MyString client_type; // Efficient/Traditional - clients become efficient if they have more than 2 orders
    int nr_of_orders;
    int customer_id;

public:
    Customer();
    Customer(int customer_id1, const MyString &name1, const MyString &client_type1, int nr_of_orders1);
    /// Operator overloading '=' pentru customer
    Customer& operator=(const Customer& customer);

    /// Copy constructor down here:
    Customer(const Customer& customer);

    /// Operator overloading pentru afisarea obiectului Customer
    friend ostream& operator<<(std::ostream& out, const Customer& new_customer);
};
Customer::Customer() : customer_id(0), name(NULL), client_type(NULL), nr_of_orders(0){}

Customer::Customer(int customer_id1, const MyString &name1, const MyString &client_type1, int nr_of_orders1) {
    customer_id = customer_id1;
    name = name1;
    client_type = client_type1;
    nr_of_orders = nr_of_orders1;
}

Customer::Customer(const Customer& customer) {
    this->customer_id = customer.customer_id;
    this->name = customer.name;
    this->client_type = customer.client_type;
    this->nr_of_orders = customer.nr_of_orders;
}

Customer& Customer::operator=(const Customer &customer) {
    if (this == &customer) {
        return *this;           // self assignment
    }
    this->customer_id = customer.customer_id;
    this->name = customer.name;
    this->client_type = customer.client_type;
    this->nr_of_orders = customer.nr_of_orders;
    return *this;
}

ostream& operator<<(std::ostream& out, const Customer& new_customer) {
    out << "Customer ID: " << new_customer.customer_id << endl;
    out << "Name: " << new_customer.name << endl;
    out << "Client type: " << new_customer.client_type << endl;
    //out << "Book: " << new_customer.book << endl;
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
    Book *books;             // a list of books needed
    int books_number;
    Employee employee;      // a list of employees and their roles needed
    Customer customer;      // a list of customers needed
public:
    Bookstore();

    Bookstore(const MyString& name1, const MyString& address1,int books_number1, const Employee& employee1, const Customer& customer1);

    ~Bookstore();

    Bookstore &operator=(const Bookstore &bookstore);

    friend ostream &operator<<(std::ostream &out, const Bookstore &new_bookstore);

    Bookstore(const Bookstore& another_bookstore);
};
Bookstore::Bookstore() : name(NULL), address(NULL), books(NULL), books_number(0), employee(), customer() {}

Bookstore::~Bookstore() {
    if (books != NULL) {
        delete [] books;
    }
}

Bookstore::Bookstore(const MyString& name1, const MyString& address1, int books_number1, const Employee& employee1, const Customer& customer1) :
    name(name1), address(address1), employee(employee1), customer(customer1), books_number(books_number1), books(NULL)
{
    name = name1;
    address = address1;
    employee = employee1;
    customer = customer1;
    cout << "books number: " << endl;
    cin >> books_number1;
    books_number = books_number1;
    cin.ignore();

    if (books_number > 0) {
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            char title[30];
            char author[30];
            int price;
            cout << "Book name: " << endl;
            cin.getline(title, 30);
            cout << "Author name:" << endl;
            cin.getline(author, 30);
            cout << "Price: ";
            cin >> price;
            books[i] = Book(title, author, price);

            cin.ignore();
        }
        }
}

Bookstore& Bookstore::operator=(const Bookstore& bookstore) {
    if (this == &bookstore) {
        return *this;
    }

    this->name = bookstore.name;
    this->address = bookstore.address;
    this->employee = bookstore.employee;
    this->customer = bookstore.customer;
    this->books_number = bookstore.books_number;

    if (books_number > 0) {
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            this->books[i] = bookstore.books[i];
        }
    }
    return *this;
}
ostream& operator<<(std::ostream& out, const Bookstore& new_bookstore) {
    out << "Bookstore name: " << new_bookstore.name << endl;
    out << "Bookstore address: " << new_bookstore.address << "\n\n";
    out << "Bookstore employee list: " << endl;
    out << new_bookstore.employee << endl;
    out << "Bookstore customer list: " << endl;
    out << new_bookstore.customer << endl;
    out << "In stock you've introduced " << new_bookstore.books_number << " books: " << endl;
    for (int i = 0; i < new_bookstore.books_number; i++) {
        out << "Book " << i + 1 << ":" << endl;
        out << new_bookstore.books[i] << endl;
    }
    return out;
}
Bookstore::Bookstore(const Bookstore& another_bookstore) {
    this->name = another_bookstore.name;
    this->address = another_bookstore.address;
    this->employee = another_bookstore.employee;
    this->customer = another_bookstore.customer;
    this->books_number = another_bookstore.books_number;

    if (books_number > 0) {
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            books[i] = another_bookstore.books[i];
        }
    }
}

int main() {
    Book  book1("Padurea Spanzuratilor", "Prut", 233);
    Customer customer(101, "NUME PRENUME", "TIP CLIENT", 2);
    Employee employee(201, "N P", "rol", 5000);
    Bookstore bookstore("nume librarie", "adresa", 2, employee, customer);
    cout << bookstore;

    return 0;
}
