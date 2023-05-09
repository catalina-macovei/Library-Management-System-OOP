#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
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

/** Exeption:
 * */
class IllegallPriceExpt : public std::exception {
public:
    const char* what() const throw () {
        return "\nIllegal price exception\n";
    }
};

class IllegalTaxExpt : public exception {
public:
    const char* what() const throw () {
        return "\nIllegal tax exception! Tax ican't be higher than 100. It is in %!\n";
    }
};

class IllegalIdExpt : public exception {
public:
    const char* what() const throw () {
        return "\nThat's not a legall ID! It should be three digits long!\n";
    }
};

/**class Product:
 * it's abstract
 * this class will be inherited by two classes
 * it's an interface
 * */
class Product {
public:
    Product();
    virtual ~Product() = 0;
    virtual double calculateShippingCost() const = 0;       // pret cu reducere si taxa aplicata
    virtual double calculateTax() const = 0;                // pentru fiecare produs se achita un anumit procent din pret ca taxa (impozit)
    virtual double discountedPrice() const = 0;             // pret cu discount
};
Product::Product() {}
Product::~Product() {}



/**
 * Clasa Book
 * Aici voi pastra datele pentru fiecare carte sub forma (titlu, autor, pret)
 * */
class Book : public Product {
    MyString title;
    MyString author;
    int gross_price;
    int discount;
    int tax;
public:
    Book();
    ~Book();

    Book(const MyString title1, const MyString author1, int gross_price1, int discount, int tax);

    friend ostream &operator<<(ostream &out, const Book &new_book);

    Book(const Book &book);

    Book &operator=(const Book &book);

    /// Getters down here!
    const MyString getTitle()  const;

    const MyString getAuthor() const;

    int getPrice() const; //mystring ref

    /// Setters down here!
    void setTitle(const MyString title_set);

    void setAuthor(const MyString author_set);

    void setPrice(int gross_price_set);

    virtual double calculateShippingCost() const;

    virtual double calculateTax() const;

    virtual double discountedPrice() const;
};

Book::Book() : title(NULL), author(NULL), Product()  {}

Book::Book(const MyString title1, const MyString author1, int gross_price1, int discount1, int tax1)
    : gross_price(gross_price1), title(title1), author(author1), discount(discount1), tax(tax1), Product()
    {
        if (gross_price1 < 0) {
            throw IllegallPriceExpt ();
        }
    }

Book::~Book() {}

double Book::discountedPrice() const {
    return gross_price - gross_price * discount / 100;
}

double Book::calculateShippingCost() const {
    cout << "\nShipping Cost is: ";
    return discountedPrice() + calculateTax();
}

double Book::calculateTax() const {
    return discountedPrice() * tax / 100;
}
ostream& operator<<(ostream& out, const Book& book) {
    out << "Title: " << book.title << endl;
    out << "Author: " << book.author << endl;
    out << "Price: " << book.gross_price << " lei" << endl;
    out << "The shipping price: " << book.calculateShippingCost() << " lei" << endl;
    out << "The tax for this product is " << book.calculateTax() << " lei" << endl;
    return out;
}
Book& Book::operator=(const Book& book) {
    if (this == &book) {
        return *this;       //protect against self assignment (book = book)
    }
    this->title = book.title;
    this->author = book.author;
    this->gross_price = book.gross_price;
    this->discount = book.discount;
    this->tax = book.tax;
    return *this;
}
Book::Book(const Book& book) {
    this->title = book.title;
    this->author = book.author;
    this->gross_price = book.gross_price;
    this->discount = book.discount;
    this->tax = book.tax;
}
const MyString Book::getTitle() const {
    return title;
}
const MyString Book::getAuthor() const {
    return author;
}
int Book::getPrice() const {
    return gross_price;
}
void Book::setTitle(const MyString title_set) {
    title = title_set;
}
void Book::setAuthor(const MyString author_set) {
    author = author_set;
}
void Book::setPrice(int price_set) {
    gross_price = price_set;
}


/**Class OfficeSupplies:
 * other accesories for school or office such textbooks, pencils
 * It inherits class Product
 * */

class OfficeSupplies : public Product {
    MyString name;
    int gross_price;
    int discount;
    int tax;

public:
    OfficeSupplies();

    OfficeSupplies(const MyString &name1, int gross_price1, int discount1, int tax1);

    friend ostream& operator<<(ostream& out, const OfficeSupplies& supp);

    virtual double calculateShippingCost() const;

    virtual double calculateTax() const;

    virtual double discountedPrice() const;

    void setTax(int tax1) ;

    int getTax() const;
};

OfficeSupplies::OfficeSupplies()
                : name(NULL), gross_price(0), discount(0), tax(0), Product() {}

OfficeSupplies::OfficeSupplies(const MyString &name1, int gross_price1, int discount1, int tax1)
                :   Product(), name(name1), gross_price(gross_price1), discount(discount1), tax(tax1)
                {}

void OfficeSupplies::setTax(int tax1) {
    tax = tax1;
}

int OfficeSupplies::getTax() const {
    return tax;
}

double OfficeSupplies::discountedPrice() const {
    return gross_price - gross_price * discount / 100;
}

double OfficeSupplies::calculateShippingCost() const {
    return discountedPrice() + calculateTax();
}

double OfficeSupplies::calculateTax() const {
    if (tax > 100) { throw IllegalTaxExpt(); }
    return discountedPrice() * tax / 100;
}
ostream& operator<<(ostream& out, const OfficeSupplies& supp) {
    out << "Title: " << supp.name << endl;
    out << "Price: " << supp.gross_price << " lei" << endl;
    out << "The shipping price: " << supp.calculateShippingCost() << " lei" << endl;
    out << "The tax for this product is " << supp.calculateTax() << " lei" << endl;
    return out;
}

/**Class User:
 * defined to set a password and a user name for users of bookstore app:
 * customer, employee, manager.
 * */
class User {
protected:
    MyString password;

    MyString username;

    void setPassword(const MyString password_set);

    void setUsername(const MyString username_set);
public:
    User();

    User(const MyString &password1, const MyString &username1);

    User& operator=(const User &user);

    User(const User& user);
};

User::User() : password(NULL), username(NULL) {}
User::User(const MyString &password1, const MyString &username1) : password(password1), username(username1) {}

void User::setPassword(const MyString password_set) {
    password = password_set;
}
void User::setUsername(const MyString username_set) {
    username = username_set;
}
User& User::operator=(const User &user) {
    if (this == &user) {
        return *this;           // self assignment
    }
    this->username = user.username;
    this->password = user.password;
    return *this;
}
User::User(const User& user) {
    this->password = user.password;
    this->username = user.username;
}

/**Clasa Customer:
 * Aici e clasa Customer cu proprietatile: name, client_type, nr_of_orders, customer_id
 * */
class Customer: protected User{
private:
    MyString name;
    MyString client_type;           // Efficient/Traditional - clients become efficient if they have more than 2 orders
    int nr_of_orders;
    int customer_id;
public:
    Customer();

    Customer(int customer_id1, const MyString &name1, const MyString &client_type1, int nr_of_orders1, const MyString &password1, const MyString &username1);

    Customer& operator=(const Customer& customer);

    Customer(const Customer& customer);

    friend ostream& operator<<(std::ostream& out, const Customer& new_customer);

    void setType(const MyString type_set);

    int getNrOrders() const;

    int getCustomerId() const;

    const MyString getName() const;

    const MyString getClientType() const;
};
Customer::Customer() : customer_id(0), name(NULL), client_type(NULL), nr_of_orders(0),
                        User()
                        {}

Customer::Customer(int customer_id1, const MyString &name1, const MyString &client_type1, int nr_of_orders1, const MyString &password1, const MyString &username1)
                    : customer_id(customer_id1), name(name1), client_type(client_type1), nr_of_orders(nr_of_orders1),
                      User(password1, username1)
                      {}

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
    out << "PASSWORD: " << new_customer.password << endl;
    return out;
}
int Customer::getNrOrders() const {
    return nr_of_orders;
}
int Customer::getCustomerId() const {
    return customer_id;
}
const MyString Customer::getName() const {
    return name;
}
const MyString Customer::getClientType() const {
    return client_type;
}
void Customer::setType(const MyString type_set) {
    client_type = type_set;
}



/** Clasa Employee:
 * Fiecare angajat va fi inregistrat sub forma: (nume, rol, ID, salary)
 * */
class Employee : protected User {
private:
    MyString name;
    MyString role;
    int employee_id;
    int salary;

protected:
    double performance_metric;

    MyString responsibility;

    void setPerformanceMetric(double performance_metric_set);

    void increaseSalary(double percent_increase);

public:
    Employee();

    Employee(int employee_id1, const MyString &name1, const MyString &role1, int salary1, const MyString &password1, const MyString &username1);

    Employee& operator=(const Employee& employee);

    Employee(const Employee &employee);

    friend ostream& operator<<(std::ostream& out, const Employee& new_employee);

    /// Getters down here!
    int getId()  const;

    const MyString getName() const;

    const MyString getRole() const;

    int getSalary() const;

    int getVacationDays() const;

    const MyString getEmail() const;

    /// Setters down here!
    void setName(const MyString name_set);

    void setRole(const MyString role_set);

    void setSalary(int salary_set);

    void setId(int id_set);
};

Employee::Employee() : name(NULL), role(NULL), salary(0)  {}

Employee::Employee(int employee_id1, const MyString &name1, const MyString &role1, int salary1, const MyString &password1, const MyString &username1)
            : employee_id(employee_id1), name(name1), role(role1), salary(salary1), User(password1, username1)
            {
                if (int(log10(employee_id) + 1) != 3) { throw IllegalIdExpt (); }
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
    out << "Employee pw: " << new_employee.password << endl;

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
void Employee::setPerformanceMetric(double performance_metric_set) {
    performance_metric = performance_metric_set;
}

void Employee::increaseSalary(double percent_increase) {
    double new_salary = getSalary() * (1 + percent_increase / 100);
    setSalary(new_salary);
}



/**Class Manager:
 * it is derived from Employee
 * The manager is an employee of the bookstore which is responsible for:
 * hiring a new employee
 * managing schedules
 * inventory management
 * */
class Manager : public Employee {
private:
    MyString responsibility;
public:
    Manager();
    Manager(int employee_id1, const MyString &name1, const MyString &role1, int salary1, const MyString &password1, const MyString &username1, const MyString &responsibility1);
    Manager& operator=(const Manager& manager);
    Manager(const Manager &manager);
    friend ostream& operator<<(std::ostream& out, const Manager& new_manager);

    // Getters
    const MyString getResponsibility() const;

    // Setters
    void setPerformanceMetric(double performance_metric_set);

    void setResponsibility(const MyString &responsibility_set);

    // Other methods
    void increaseSalary(double percent_increase);

};

Manager::Manager() : Employee() {}

Manager::Manager(int employee_id1, const MyString &name1, const MyString &role1, int salary1, const MyString &password1, const MyString &username1, const MyString &responsibility1)
        : responsibility(responsibility1), Employee(employee_id1, name1, role1, salary1, password1, username1 ) {}

Manager& Manager::operator=(const Manager& manager) {
    if (this == &manager) {
        return *this; //protect against self assignment (v = v)
    }

    Employee::operator=(manager); // call base class operator=
    this->responsibility = manager.responsibility;

    return *this;
}

Manager::Manager(const Manager &manager) {
    Employee::operator=(manager);                       // call base class operator=

    this->responsibility = manager.responsibility;
}

ostream& operator<<(std::ostream& out, const Manager& new_manager) {
    out << "\n\nAbout Manager details: " << endl;
    out << static_cast<const Employee&>(new_manager);           // print base class fields
    out << "Manager responsibility: " << new_manager.responsibility << endl;
    return out;
}

const MyString Manager::getResponsibility() const {
    return responsibility;
}
void Manager::setResponsibility(const MyString &responsibility_set) {
    responsibility = responsibility_set;
}

void Manager::setPerformanceMetric(double performance_metric_set) {
    Employee::setPerformanceMetric(performance_metric_set);
}

void Manager::increaseSalary(double percent_increase) {
    Employee::increaseSalary(percent_increase);
}

//
//class Bookstore {
//    MyString name;
//    MyString address;
//    Book *books;
//    int books_number;
//    Employee *employee;
//    int employee_number;
//    Customer *customer;
//    int customer_number;
//    bool ok;
//public:
//    Bookstore();
//
//    Bookstore(const MyString& name1, const MyString& address1,int books_number1, int employee_number1, int customer_number1, bool ok);
//
//    ~Bookstore();
//
//    Bookstore &operator=(const Bookstore &bookstore);
//
//    friend ostream &operator<<(std::ostream &out, const Bookstore &new_bookstore);
//
//    Bookstore(const Bookstore& another_bookstore);
//
//    /// Bookstore Setters:
//    void setName(const MyString new_name);
//
//    void setAddress(const MyString new_address);
//
//    void setBooks(const Book* new_books, int books_nr);
//
//    void setCustomers(const Customer* new_customers, int customer_nr);
//
//    void setEmployees(const Employee* new_employees, int employee_nr);
//
//    /// Bussiness methods down here:
//    double mediumSalary();
//
//    double mediumPrice();
//
//    int efficientCustomers();
//
//    const MyString maxSalary();
//};
//Bookstore::Bookstore()
//    : name(NULL), address(NULL), books(NULL), books_number(0), employee(NULL), employee_number(0), customer(NULL), customer_number(0) {}
//
//Bookstore::~Bookstore() {
//    if (books != NULL) {
//        delete [] books;
//    }
//    if (customer != NULL) {
//        delete [] customer;
//    }
//    if (employee != NULL) {
//        delete [] employee;
//    }
//}
//
//Bookstore::Bookstore(const MyString& name1, const MyString& address1,int books_number1, int employee_number1, int customer_number1, bool ok)
//:   name(name1), address(address1), employee(NULL), employee_number(employee_number1), customer(NULL), books_number(books_number1), books(NULL), customer_number(customer_number1), ok(0)
//    {
//        if (ok) {  //op de citire
//            cin.ignore();
//            cout << "Bookstore name: " << endl;
//            cin >> name;
//            cout << "Bookstore address: " << endl;
//            cin >> address;
//            cout << "Employees number: " << endl;
//            cin >> employee_number1;
//            employee_number = employee_number1;
//            cin.ignore();
//
//            if (employee_number > 0) {
//                employee = new Employee[employee_number];
//                for (int i = 0; i < employee_number; i++) {
//                    char name[30];
//                    char role[30];
//                    int id;
//                    int salary;
//                    char pw[15];
//                    char user[15];
//
//                    cout << "Employee's name: " << endl;
//                    cin.getline(name, 30);
//                    cout << "Employee's role:" << endl;
//                    cin.getline(role, 30);
//                    cout << "Employee ID: ";
//                    cin >> id;
//                    cout << "Salary: " << endl;
//                    cin >> salary;
//                    strcpy(pw, "password");
//                    strcpy(user, "username");
//
//                    employee[i] = Employee(id, name, role, salary, pw, user);
//                    cin.ignore();
//                }
//            }
//
//            cout << "Customers number: " << endl;
//            cin >> customer_number1;
//            customer_number = customer_number1;
//            cin.ignore();
//            if (customer_number > 0) {
//                customer = new Customer[customer_number];
//                for (int i = 0; i < customer_number; i++) {
//                    char name[30];
//                    char type[30];
//                    int id;
//                    int orders_nr;
//                    char pw[15];
//                    char user[15];
//
//                    cout << "Client's name: " << endl;
//                    cin.getline(name, 30);
//                    cout << "Customer ID: ";
//                    cin >> id;
//                    cout << "Number of orders: " << endl;
//                    cin >> orders_nr;
//                    if (orders_nr > 2)
//                        strcpy(type, "efficient");
//                    else
//                        strcpy(type, "traditional");
//                    strcpy(pw, "password");
//                    strcpy(user, "username");
//                    customer[i] = Customer(id, name, type, orders_nr, pw, user);
//                    cin.ignore();
//                }
//            }
//            cout << "books number: " << endl;
//            cin >> books_number1;
//            books_number = books_number1;
//            cin.ignore();
//            if (books_number > 0) {
//                books = new Book[books_number];
//                for (int i = 0; i < books_number; i++) {
//                    char title[30];
//                    char author[30];
//                    int price;
//                    cout << "Book name: " << endl;
//                    cin.getline(title, 30);
//                    cout << "Author name:" << endl;
//                    cin.getline(author, 30);
//                    cout << "Price: ";
//                    cin >> price;
//                    books[i] = Book(title, author, price);
//
//                    cin.ignore();
//                }
//            }
//        }
//}
//Bookstore& Bookstore::operator=(const Bookstore& bookstore) {
//    if (this == &bookstore) {
//        return *this;
//    }
//    this->name = bookstore.name;
//    this->address = bookstore.address;
//    this->employee_number = bookstore.employee_number;
//    this->books_number = bookstore.books_number;
//    this->customer_number = bookstore.customer_number;
//
//    if (employee != NULL) {
//        delete [] employee;
//    }
//    if (employee_number > 0) {
//        employee = new Employee[employee_number];
//        for (int i = 0; i < employee_number; i++) {
//            this->employee[i] = bookstore.employee[i];
//        }
//    }
//
//    if (customer != NULL) {
//        delete [] customer;
//    }
//    if (customer_number > 0) {
//        customer = new Customer[customer_number];
//        for (int i = 0; i < customer_number; i++) {
//            this->customer[i] = bookstore.customer[i];
//        }
//    }
//
//    if (books != NULL) {
//        delete [] books;
//    }
//    if (books_number > 0) {
//        books = new Book[books_number];
//        for (int i = 0; i < books_number; i++) {
//            this->books[i] = bookstore.books[i];
//        }
//    }
//    return *this;
//}
//ostream& operator<<(std::ostream& out, const Bookstore& new_bookstore) {
//    out << "\n\n<<------------------->>   BOOKSTORE  STAGE: < completed >    <<---------------------->>" << endl;
//    out << "\n\nBookstore name: " << new_bookstore.name << endl;
//    out << "\nBookstore address: " << new_bookstore.address << endl;
//
//    out << "\nYou've introduced " << new_bookstore.employee_number << " employees successfully!" << endl;
//    for (int i = 0; i < new_bookstore.employee_number; i++) {
//        out << "Employee " << i + 1 << ":" << endl;
//        out << new_bookstore.employee[i] << endl;
//    }
//    out << "\nYou've introduced " << new_bookstore.customer_number << " customers successfully!" << endl;
//    for (int i = 0; i < new_bookstore.customer_number; i++) {
//        out << "Customer " << i + 1 << ":" << endl;
//        out << new_bookstore.customer[i] << endl;
//    }
//    out << "\nIn stock you've introduced " << new_bookstore.books_number << " books: " << endl;
//    for (int i = 0; i < new_bookstore.books_number; i++) {
//        out << "Book " << i + 1 << ":" << endl;
//        out << new_bookstore.books[i] << endl;
//    }
//    return out;
//}
//Bookstore::Bookstore(const Bookstore& another_bookstore) {
//    this->name = another_bookstore.name;
//    this->address = another_bookstore.address;
//    this->employee_number = another_bookstore.employee_number;
//    this->customer_number = another_bookstore.customer_number;
//    this->books_number = another_bookstore.books_number;
//
//    if (employee_number > 0) {
//        employee = new Employee[employee_number];
//        for (int i = 0; i < employee_number; i++) {
//            employee[i] = another_bookstore.employee[i];
//        }
//    }
//    if (customer_number > 0) {
//        customer = new Customer[customer_number];
//        for (int i = 0; i < customer_number; i++) {
//            customer[i] = another_bookstore.customer[i];
//        }
//    }
//    if (books_number > 0) {
//        books = new Book[books_number];
//        for (int i = 0; i < books_number; i++) {
//            books[i] = another_bookstore.books[i];
//        }
//    }
//}
//void Bookstore::setName(const MyString new_name) {
//    name = new_name;
//}
//void Bookstore::setAddress(const MyString new_address) {
//    address = new_address;
//}
//void Bookstore::setBooks(const Book* new_books, int books_nr) {
//    if (books != NULL) {
//        delete [] books;
//    }
//    if (books_nr > 0) {
//        books_number = books_nr;
//        books = new Book[books_number];
//        for (int i = 0; i < books_number; i++) {
//            books[i] = new_books[i];
//        }
//    }
//}
//void Bookstore::setCustomers(const Customer *new_customers, int customer_nr) {
//    if (customer != NULL) {
//        delete [] customer;
//    }
//    if (customer_nr > 0) {
//        customer_number = customer_nr;
//        customer = new Customer[customer_nr];
//        for (int i = 0; i < customer_number; i++) {
//            customer[i] = new_customers[i];
//        }
//    }
//}
//void Bookstore::setEmployees(const Employee *new_employees, int employee_nr) {
//    if (employee != NULL) {
//        delete [] employee;
//    }
//    if (employee_nr > 0) {
//        employee_number = employee_nr;
//        employee = new Employee[employee_number];
//        for (int i = 0; i < employee_number; i++) {
//            employee[i] = new_employees[i];
//        }
//    }
//}
//double Bookstore::mediumSalary() {
//    double med_sum = 0;
//    for (int i = 0; i < employee_number; i++) {
//        med_sum += employee[i].getSalary();
//    }
//    return med_sum / employee_number;
//}
//double Bookstore::mediumPrice() {
//    double med_price = 0;
//    for (int i = 0; i < books_number; i++) {
//        med_price += books[i].getPrice();
//    }
//    return med_price / books_number;
//}
//int Bookstore::efficientCustomers() {
//    int counter = 0;
//    for (int i = 0; i < customer_number; i++) {
//        if (customer[i].getNrOrders() > 2)
//            counter++;
//    }
//    return counter;
//}
//const MyString Bookstore::maxSalary() {
//    MyString ret_name;
//    int max = employee[0].getSalary();
//    ret_name = employee[0].getName();
//    for (int i = 0; i < employee_number; i++) {
//        if (max < employee[i].getSalary()) {
//            max = employee[i].getSalary();
//            ret_name = employee[i].getName();
//        }
//    }
//    return ret_name;
//}
//

/**Class Event
 * Abstract
 * One pure virtual function
 * */
class Event {
private:
    string name;

public:
    virtual void showEventName() { cout << "Base:: showEventName() " << getName() << endl;};
    virtual double calculateTotalExpenses() { cout << "Event total expenses:  0 "; return 0; };
    void setEventName(string name_set);
    Event();
    Event(string name1);
    string getName() const;
    virtual ~Event() = 0;
};
Event::Event() : name("hi") {}
string Event::getName() const {
    return name;
}
void Event::setEventName(string name_set) {
    name = name_set;
}
Event::~Event() {}
Event::Event(string name1) : name(name1) {}

class Donatie : public virtual Event {
    int donation_expenses;
    int sponsorship;
public:
    Donatie();
    Donatie(int donation_expenses1, int sponsorship1);
    int getDonationExp() const;
    int getDsponsorhip() const;
    virtual void showEventName() { cout << "Derived donation:: showEventName() " << getName() << endl; };
    double calculateEdonation() { cout << "\nDynamic cast\n" << "Total expenses for donation: " << endl; return getDsponsorhip() + getDonationExp();}
};

Donatie::Donatie() : donation_expenses(0), sponsorship(0) {}

Donatie::Donatie(int donation_expenses1, int sponsorship1)
        : donation_expenses(donation_expenses1), sponsorship(sponsorship1) {}

int Donatie::getDonationExp() const {
    return donation_expenses;
}

int Donatie::getDsponsorhip() const {
    return sponsorship;
}


class Concurs : public virtual Event {
    int premium;    // the value of the premium in lei
    int c_sponsorhip;       // what's the budget for organising the contest
public:
    Concurs();
    Concurs(int premium1, int c_sponsorship1);
    int getPremium() const;
    int getCsponsorship() const;
    virtual void showEventName() { cout << "Contest name is " << getName() << endl; };
    virtual double calculateTotalExpenses() { cout << "Contest total expenses:   "; return getCsponsorship() + getPremium(); };
};

Concurs::Concurs() : premium(0), c_sponsorhip(0) {}

Concurs::Concurs(int premium1, int c_sponsorship1) : premium(premium1), c_sponsorhip(c_sponsorship1){}

int Concurs::getPremium() const {
    return premium;
}
int Concurs::getCsponsorship() const {
    return c_sponsorhip;
}


class Campanie : public Donatie, public Concurs{
    int x;
public:
    Campanie();
    Campanie(int x1, int premium1, int c_sponsorship1, int donation_expenses1, int sponsorship1);
    virtual void showEventName() { cout << "Campain name is " << getName() << endl; };
    virtual double calculateTotalExpenses();
};
Campanie::Campanie() : x(0) {}

Campanie::Campanie(int x1, int premium1, int c_sponsorship1, int donation_expenses1, int sponsorship1)
        : x(x1), Concurs(premium1, c_sponsorship1), Donatie(donation_expenses1, sponsorship1) {}

double Campanie::calculateTotalExpenses() {
    cout << "Campain total expenses: ";
    return getPremium() + getCsponsorship() + x + getDsponsorhip() + getDonationExp();
}
void progression(Employee& emp) {
    emp.setRole("director");
    emp.setSalary(15000);
    cout << "Manager promoted to next level!";
}


int main() {
    bool set_default = false;
    char repeat = 'Y';
    Book  book1("Padurea Spanzuratilor", "Liviu Rebreanu", 233, 20, 5);
    Customer customer(101, "Radu Valentin", "Traditional", 1, "pw", "user");
    Employee employee(201, "Radu Laura", "casier", 5000, "pp", "uu");

    /// For testing, you may skip this section
//    cout << "Testing Book:" << endl;
//    cout << book1 << endl;
//    cout << "Testing customer:" << endl;
//    cout << customer << endl;
//    cout << "Testing employee:" << endl;
//    cout << employee << endl;

//while (repeat == 'Y' || repeat == 'y') {
//    char meth;
//
//    cout << "Do you want to use the default values or introduce them by yourself ?        R: 1 - introduce by yourself    0 - default values" << endl;
//    cin >> set_default;
//    Bookstore bookstore1("nume librarie", "adresa", 0, 0, 0, set_default);
//
//    if (set_default) {
//        cout << "First bookstore : " << endl;
//        cout << bookstore1;
//
//        cout << "Do you want to see a data revision?  R: Y - yes or N - no" << endl;
//        cin >> meth;
//       if (meth == 'Y' || meth == 'y') {
//           cout << "<<---------------Revision--------------->>" << endl;
//           cout << "Pretul mediu books: " << bookstore1.mediumPrice() << endl;
//           cout << "Salariu mediu employees: " << bookstore1.mediumSalary() << endl;
//           cout << "Nr of efficient customers: " << bookstore1.efficientCustomers() << endl;
//           cout << "Numele angajatului cu cel mai mare salariu: " <<bookstore1.maxSalary() << endl;
//       }
//        cout << "Do you want to create one more bookstore ? R: Y - yes or N - no" << endl;
//        cin >> repeat;
//    } else {
//        cout << "\n\nSecond Bookstore: " << endl;
//
//        bookstore1.setName("Librarius");
//        bookstore1.setAddress("Alba Iulia 184/2");
//
//        Customer new_customers[] = {Customer(100, "Baraboi Adrian", "Efficient", 2, "pw", "user"),
//                                    Customer(101, "Radu Laura", "Traditional", 4, "pw", "user"),
//                                    Customer(102, "Popa Valentin", "Efficient", 3, "pw", "user")};
//        bookstore1.setCustomers(new_customers, 3);
//
//        Employee new_employees[] = {Employee(1000, "Racasan Nicoleta", "Vanzator Consultant", 10000),
//                                    Employee(1001, "Popescu Mihai Octavian", "Programator", 15000),
//                                    Employee(1002, "Salceanu Alexandru", "Administrator", 20000)};
//        bookstore1.setEmployees(new_employees, 3);
//
//        Book book[] = {Book("Strainul", "Albert Camus", 110),
//                       Book("Conditia umana", "Andre Malraux", 200),
//                       Book("Tropice triste", "Claude Levi-Strauss", 250),
//                       Book("Ulise", "James Joyse", 300),
//                       Book("Desertul Tatarilor", "Dino Buzzati", 220)};
//        bookstore1.setBooks(book, 5);
//
//        cout << bookstore1;
//
//        cout << "Do you want to see a data revision?  R: Y - yes or N - no" << endl;
//        cin >> meth;
//        if (meth == 'Y' || meth == 'y') {
//            cout << "<<---------------Revision--------------->>" << endl;
//            cout << "Pretul mediu books: " << bookstore1.mediumPrice() << endl;
//            cout << "Salariu mediu employees: " << bookstore1.mediumSalary() << endl;
//            cout << "Nr of efficient customers: " << bookstore1.efficientCustomers() << endl;
//            cout << "Numele angajatului cu cel mai mare salariu: " <<bookstore1.maxSalary() << endl;
//        }
//        cout << "Do you want to create one more bookstore ? R: Y - yes or N - no" << endl;
//        cin >> repeat;
//    }
//
//}

/// Part 2 of testing :


//    Manager manager(101, "Paolo Escobar", "staff manager", 10000, "uuu", "ppp", "hiring");
//
//    char increase;
//    cout << manager;
//    cout << "\nYou want to increase salary for manager? Y/N" << endl;
//    cin >> increase;
//
//    if (increase == 'Y' || increase == 'y') {
//
//        manager.increaseSalary(10.5);
//
//        cout << "\nThe new salary for this manager is:  "
//        << manager.getSalary() << " lei"<< endl;
//
//    } else {
//
//        cout << "\nOk. The salary remains the same :((" << endl;
//
//    }
//    OfficeSupplies supplies("caiet", 30, 20, 3);
//    cout << supplies;
//    Campanie campanie(1, 200, 300, 100, 200);
//    Campanie().showEventName();
//    cout << campanie.calculateTotalExpenses() << endl;

    /**DYNAMIC DISPATCH on class Event:
     * Make sure you have defined a virtual function in your base class
     * Override keyword after function definition in derived class
     * Voila! Dynamic dispatch - the mechanism to choose at runtime the correct function is done
     * To actually call that matches the data type of your object
     * */
     cout << endl;

     Event* event1 = new Campanie(1, 200, 300, 100, 200);
     event1->setEventName("Licurici");
     event1->showEventName();
     cout << event1->calculateTotalExpenses() << endl;
     delete event1;

     cout << endl;


     Event* event2 = new Concurs(200, 3000);
     event2->setEventName("Concurs");
     event2->showEventName();
     cout << event2->calculateTotalExpenses() << endl;
     delete event2;

     /**Upcasting :
      * */

     Manager manager(101, "Paolo Escobar", "staff manager", 10000, "uuu", "ppp", "hiring");
     cout << manager;
     progression(manager);      // helps reuse the code from employee
     cout << manager;

    Book  book3("Padurea Spanzuratilor", "Liviu Rebreanu", 233, 20, 5);
    Product* prod1 = &book3;
    cout <<"\nUpcasting done: " << endl;
    cout << prod1->calculateShippingCost() << " lei" << endl;
    cout << "Discounted price " << prod1->discountedPrice() << " lei" << endl;
    cout << "Tax value:  " << prod1->calculateTax() << " lei" << endl;


    OfficeSupplies office_sup("Carnet", 80, 25, 5);
    Product* prod2 = &office_sup;
    cout <<"\nUpcasting done: " << endl;
    cout << prod2->calculateShippingCost() << " lei" << endl;
    cout << "Discounted price " << prod2->discountedPrice() << " lei" << endl;
    cout << "Tax value:  " << prod2->calculateTax() << " lei" << endl;


    /**Downcasting:
     * using dynamic_cast
     * */
    Event* event11 = new Donatie(222, 222);

    Donatie* donatie = dynamic_cast<Donatie*>(event11);
    if (donatie != nullptr) {
        cout << "\n  " << donatie->calculateEdonation() << endl;
    }


    /**Exception handling:
     * */
    try {
        Book bookEx("aaa", "aaaa", -333, 33, 33);
    }
    catch (const IllegallPriceExpt &ex) {
        cout << ex.what() << "\n";
    }
    OfficeSupplies offsup("pix", 23, 40, 1645);
    int temporary;

    try {
        offsup.calculateTax();
    }
    catch (const IllegalTaxExpt &ex) {
        cout << ex.what() << endl;

        temporary = offsup.getTax() / 10;
        offsup.setTax(temporary);

        temporary = offsup.getTax();
        cout << "The new truncated tax is " << temporary << endl;

        try {
            if (temporary > 100) { throw temporary; }
        }
        catch(int temp) {
            cout << "Truncation failed! " << endl;
            bool tax_tracker = false;

            while(!tax_tracker) {
                cout << "Set new value for tax: " << endl;
                cin >> temporary;
                if (temporary < 100) {
                    offsup.setTax(temporary);
                    cout << "New tax has been set: " << offsup.getTax() << endl;
                    tax_tracker = true;
                }
            }
        }
    }

    /**Static testing:
     * */

    return 0;
}
