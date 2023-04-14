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
        return *this;                       //protect against self assignment (str = str)
    }
    if (data != NULL) {
        delete [] data;                     //delete the allocated memory          !!!!!!
    }
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
 * Aici voi pastra datele pentru fiecare carte sub forma (titlu, autor, pret)
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

    /// Getters down here!
    const MyString getTitle()  const;

    const MyString getAuthor() const;

    int getPrice() const;

    /// Setters down here!
    void setTitle(const MyString title_set);

    void setAuthor(const MyString author_set);

    void setPrice(int price_set);
};

Book::Book() : title(NULL), author(NULL)  {}

Book::Book(const MyString title1, const MyString author1, int price1) : price(price1), title(title1), author(author1) {}

ostream& operator<<(ostream& out, const Book& book) {
    out << "Title: " << book.title << endl;
    out << "Author: " << book.author << endl;
    out << "Price: " << book.price << " lei" << endl;
    return out;
}
Book& Book::operator=(const Book& book) {
    if (this == &book) {
        return *this;       //protect against self assignment (book = book)
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
const MyString Book::getTitle() const {
    return title;
}
const MyString Book::getAuthor() const {
    return author;
}
int Book::getPrice() const {
    return price;
}
void Book::setTitle(const MyString title_set) {
    title = title_set;
}
void Book::setAuthor(const MyString author_set) {
    author = author_set;
}
void Book::setPrice(int price_set) {
    price = price_set;
}



/**   Clasa Customer:
 * Aici e clasa Customer cu proprietatile: name, client_type, nr_of_orders, customer_id
 * */
class Customer {
    MyString name;
    MyString client_type;           // Efficient/Traditional - clients become efficient if they have more than 2 orders
    int nr_of_orders;
    int customer_id;

public:
    Customer();

    Customer(int customer_id1, const MyString &name1, const MyString &client_type1, int nr_of_orders1);

    Customer& operator=(const Customer& customer);

    Customer(const Customer& customer);

    friend ostream& operator<<(std::ostream& out, const Customer& new_customer);

    void setType(const MyString type_set);

    int getNrOrders() const;
};
Customer::Customer() : customer_id(0), name(NULL), client_type(NULL), nr_of_orders(0) {}

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
    out << "Nr of orders: " << new_customer.nr_of_orders << endl;
    return out;
}
int Customer::getNrOrders() const {
    return nr_of_orders;
}
void Customer::setType(const MyString type_set) {
    client_type = type_set;
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

    /// Getters down here!
    int getId()  const;

    const MyString getName() const;

    const MyString getRole() const;

    int getSalary() const;

    /// Setters down here!
    void setName(const MyString name_set);

    void setRole(const MyString role_set);

    void setSalary(int salary_set);

    void setId(int id_set);
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
int Employee::getId() const {
    return employee_id;
}
const MyString Employee::getName() const {
    return name;
}
const MyString Employee::getRole() const {
    return role;
}
int Employee::getSalary() const {
    return salary;
}
void Employee::setName(const MyString name_set) {
    name = name_set;
}
void Employee::setRole(const MyString role_set) {
    role = role_set;
}
void Employee::setSalary(int salary_set) {
    salary = salary_set;
}
void Employee::setId(int id_set) {
    employee_id = id_set;
}



class Bookstore {
    MyString name;
    MyString address;
    Book *books;
    int books_number;
    Employee *employee;      // a list of employees and their roles needed
    int employee_number;
    Customer *customer;
    int customer_number;
    bool ok;
public:
    Bookstore();

    Bookstore(const MyString& name1, const MyString& address1,int books_number1, int employee_number1, int customer_number1, bool ok);

    ~Bookstore();

    Bookstore &operator=(const Bookstore &bookstore);

    friend ostream &operator<<(std::ostream &out, const Bookstore &new_bookstore);

    Bookstore(const Bookstore& another_bookstore);

    /// Bookstore Setters:
    void setName(const MyString new_name);

    void setAddress(const MyString new_address);

    void setBooks(const Book* new_books, int books_nr);

    void setCustomers(const Customer* new_customers, int customer_nr);

    void setEmployees(const Employee* new_employees, int employee_nr);

    /// Bussiness methods down here:
    double mediumSalary();

    double mediumPrice();

    int efficientCustomers();

    const MyString maxSalary();
};
Bookstore::Bookstore() : name(NULL), address(NULL), books(NULL), books_number(0), employee(NULL), employee_number(0), customer(NULL), customer_number(0) {}

Bookstore::~Bookstore() {
    if (books != NULL) {
        delete [] books;
    }
    if (customer != NULL) {
        delete [] customer;
    }
    if (employee != NULL) {
        delete [] employee;
    }
}

Bookstore::Bookstore(const MyString& name1, const MyString& address1,int books_number1, int employee_number1, int customer_number1, bool ok)
:   name(name1), address(address1), employee(NULL), employee_number(employee_number1), customer(NULL), books_number(books_number1), books(NULL), customer_number(customer_number1), ok(0)
    {
        if (ok) {
            cin.ignore();
            cout << "Bookstore name: " << endl;
            cin >> name;
            cout << "Bookstore address: " << endl;
            cin >> address;
            cout << "Employees number: " << endl;
            cin >> employee_number1;
            employee_number = employee_number1;
            cin.ignore();

            if (employee_number > 0) {
                employee = new Employee[employee_number];
                for (int i = 0; i < employee_number; i++) {
                    char name[30];
                    char role[30];
                    int id;
                    int salary;

                    cout << "Employee's name: " << endl;
                    cin.getline(name, 30);
                    cout << "Employee's role:" << endl;
                    cin.getline(role, 30);
                    cout << "Employee ID: ";
                    cin >> id;
                    cout << "Salary: " << endl;
                    cin >> salary;

                    employee[i] = Employee(id, name, role, salary);
                    cin.ignore();
                }
            }

            cout << "Customers number: " << endl;
            cin >> customer_number1;
            customer_number = customer_number1;
            cin.ignore();
            if (customer_number > 0) {
                customer = new Customer[customer_number];
                for (int i = 0; i < customer_number; i++) {
                    char name[30];
                    char type[30];
                    int id;
                    int orders_nr;

                    cout << "Client's name: " << endl;
                    cin.getline(name, 30);
                    cout << "Customer ID: ";
                    cin >> id;
                    cout << "Number of orders: " << endl;
                    cin >> orders_nr;
                    if (orders_nr > 2)
                        strcpy(type, "efficient");
                    else
                        strcpy(type, "traditional");
                    customer[i] = Customer(id, name, type, orders_nr);
                    cin.ignore();
                }
            }
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
}
Bookstore& Bookstore::operator=(const Bookstore& bookstore) {
    if (this == &bookstore) {
        return *this;
    }
    this->name = bookstore.name;
    this->address = bookstore.address;
    this->employee_number = bookstore.employee_number;
    this->books_number = bookstore.books_number;
    this->customer_number = bookstore.customer_number;

    if (employee != NULL) {
        delete [] employee;
    }
    if (employee_number > 0) {
        employee = new Employee[employee_number];
        for (int i = 0; i < employee_number; i++) {
            this->employee[i] = bookstore.employee[i];
        }
    }

    if (customer != NULL) {
        delete [] customer;
    }
    if (customer_number > 0) {
        customer = new Customer[customer_number];
        for (int i = 0; i < customer_number; i++) {
            this->customer[i] = bookstore.customer[i];
        }
    }

    if (books != NULL) {
        delete [] books;
    }
    if (books_number > 0) {
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            this->books[i] = bookstore.books[i];
        }
    }
    return *this;
}
ostream& operator<<(std::ostream& out, const Bookstore& new_bookstore) {
    out << "\n\n<<------------------->>   BOOKSTORE  STAGE: < completed >    <<---------------------->>" << endl;
    out << "\n\nBookstore name: " << new_bookstore.name << endl;
    out << "\nBookstore address: " << new_bookstore.address << endl;

    out << "\nYou've introduced " << new_bookstore.employee_number << " employees successfully!" << endl;
    for (int i = 0; i < new_bookstore.employee_number; i++) {
        out << "Employee " << i + 1 << ":" << endl;
        out << new_bookstore.employee[i] << endl;
    }
    out << "\nYou've introduced " << new_bookstore.customer_number << " customers successfully!" << endl;
    for (int i = 0; i < new_bookstore.customer_number; i++) {
        out << "Customer " << i + 1 << ":" << endl;
        out << new_bookstore.customer[i] << endl;
    }
    out << "\nIn stock you've introduced " << new_bookstore.books_number << " books: " << endl;
    for (int i = 0; i < new_bookstore.books_number; i++) {
        out << "Book " << i + 1 << ":" << endl;
        out << new_bookstore.books[i] << endl;
    }
    return out;
}
Bookstore::Bookstore(const Bookstore& another_bookstore) {
    this->name = another_bookstore.name;
    this->address = another_bookstore.address;
    this->employee_number = another_bookstore.employee_number;
    this->customer_number = another_bookstore.customer_number;
    this->books_number = another_bookstore.books_number;

    if (employee_number > 0) {
        employee = new Employee[employee_number];
        for (int i = 0; i < employee_number; i++) {
            employee[i] = another_bookstore.employee[i];
        }
    }
    if (customer_number > 0) {
        customer = new Customer[customer_number];
        for (int i = 0; i < customer_number; i++) {
            customer[i] = another_bookstore.customer[i];
        }
    }
    if (books_number > 0) {
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            books[i] = another_bookstore.books[i];
        }
    }
}
void Bookstore::setName(const MyString new_name) {
    name = new_name;
}
void Bookstore::setAddress(const MyString new_address) {
    address = new_address;
}
void Bookstore::setBooks(const Book* new_books, int books_nr) {
    if (books != NULL) {
        delete [] books;
    }
    if (books_nr > 0) {
        books_number = books_nr;
        books = new Book[books_number];
        for (int i = 0; i < books_number; i++) {
            books[i] = new_books[i];
        }
    }
}
void Bookstore::setCustomers(const Customer *new_customers, int customer_nr) {
    if (customer != NULL) {
        delete [] customer;
    }
    if (customer_nr > 0) {
        customer_number = customer_nr;
        customer = new Customer[customer_nr];
        for (int i = 0; i < customer_number; i++) {
            customer[i] = new_customers[i];
        }
    }
}
void Bookstore::setEmployees(const Employee *new_employees, int employee_nr) {
    if (employee != NULL) {
        delete [] employee;
    }
    if (employee_nr > 0) {
        employee_number = employee_nr;
        employee = new Employee[employee_number];
        for (int i = 0; i < employee_number; i++) {
            employee[i] = new_employees[i];
        }
    }
}
double Bookstore::mediumSalary() {
    double med_sum = 0;
    for (int i = 0; i < employee_number; i++) {
        med_sum += employee[i].getSalary();
    }
    return med_sum / employee_number;
}
double Bookstore::mediumPrice() {
    double med_price = 0;
    for (int i = 0; i < books_number; i++) {
        med_price += books[i].getPrice();
    }
    return med_price / books_number;
}
int Bookstore::efficientCustomers() {
    int counter = 0;
    for (int i = 0; i < customer_number; i++) {
        if (customer[i].getNrOrders() > 2)
            counter++;
    }
    return counter;
}
const MyString Bookstore::maxSalary() {
    MyString ret_name;
    int max = employee[0].getSalary();
    ret_name = employee[0].getName();
    for (int i = 0; i < employee_number; i++) {
        if (max < employee[i].getSalary()) {
            max = employee[i].getSalary();
            ret_name = employee[i].getName();
        }
    }
    return ret_name;
}


int main() {
    bool set_default = false;
    char repeat = 'Y';
    Book  book1("Padurea Spanzuratilor", "Liviu Rebreanu", 233);
    Customer customer(101, "Radu Valentin", "Traditional", 1);
    Employee employee(201, "Radu Laura", "casier", 5000);

    /// For testing, you may skip this section
//    cout << "Testing Book:" << endl;
//    cout << book1 << endl;
//    cout << "Testing customer:" << endl;
//    cout << customer << endl;
//    cout << "Testing employee:" << endl;
//    cout << employee << endl;

while (repeat == 'Y') {
    cout << "Do you want to use the default values or introduce them by yourself ?        R: 1 - introduce by yourself    0 - default values" << endl;
    cin >> set_default;
    Bookstore bookstore1("nume librarie", "adresa", 0, 0, 0, set_default);

    if (set_default) {
        cout << "First bookstore : " << endl;
        cout << bookstore1;
        cout << "Pretul mediu books: " << bookstore1.mediumPrice() << endl;
        cout << "Salariu mediu employees: " << bookstore1.mediumSalary() << endl;
        cout << "Nr of efficient customers: " << bookstore1.efficientCustomers() << endl;
        cout << "Numele angajatului cu cel mai mare salariu: " <<bookstore1.maxSalary() << endl;


        cout << "Do you want to create one more bookstore ? R: Y - yes or N - no" << endl;
        cin >> repeat;
    } else {
        cout << "\n\nSecond Bookstore: " << endl;

        bookstore1.setName("Librarius");
        bookstore1.setAddress("Alba Iulia 184/2");

        Customer new_customers[] = {Customer(100, "Baraboi Adrian", "Efficient", 2),
                                    Customer(101, "Radu Laura", "Traditional", 4),
                                    Customer(102, "Popa Valentin", "Efficient", 3)};
        bookstore1.setCustomers(new_customers, 3);

        Employee new_employees[] = {Employee(1000, "Racasan Nicoleta", "Vanzator Consultant", 10000),
                                    Employee(1001, "Popescu Mihai Octavian", "Programator", 15000),
                                    Employee(1002, "Salceanu Alexandru", "Administrator", 20000)};
        bookstore1.setEmployees(new_employees, 3);

        Book book[] = {Book("Strainul", "Albert Camus", 110),
                       Book("Conditia umana", "Andre Malraux", 200),
                       Book("Tropice triste", "Claude Levi-Strauss", 250),
                       Book("Ulise", "James Joyse", 300),
                       Book("Desertul Tatarilor", "Dino Buzzati", 220)};
        bookstore1.setBooks(book, 5);

        cout << bookstore1;
        cout << "Medium price books: " << bookstore1.mediumPrice() << endl;
        cout << "Medium salary employees: " << bookstore1.mediumSalary() << endl;
        cout << "Nr of efficient customers: " << bookstore1.efficientCustomers() << endl;
        cout << "Numele angajatului cu cel mai mare salariu: " << bookstore1.maxSalary() << endl;

        cout << "Do you want to create one more bookstore ? R: Y - yes or N - no" << endl;
        cin >> repeat;
    }

}
    return 0;
}
