#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class MyString {
    int size;
    char *data;
public:
    MyString();
    MyString(const char *str);
    MyString(const MyString &str);
    friend std::ostream& operator<<(std::ostream& out, const MyString& nume);
    friend istream& operator>>(std::istream& is, MyString& str);
    ~MyString();
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
class IllegallPriceExpt : public exception {
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

/**class Product:
 * it's abstract
 * this class will be inherited by two classes
 * it's interface
 * */
class Product {
public:
    Product();      //nu are sens
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
    string title;
    string author;
    int gross_price;
    int discount;
    int tax;
public:
    Book();
    ~Book();

    Book(string title1, string author1, int gross_price1);

    friend ostream &operator<<(ostream &out, const Book &new_book);

    friend istream& operator>>(istream& in, Book& book);

    Book(const Book &book);

    Book &operator=(const Book &book);

    /// Getters down here!
    string getTitle()  const;

    string getAuthor() const;

    int getPrice() const; //mystring ref

    /// Setters down here!
    void setTitle(string title_set);

    void setAuthor(string author_set);

    void setPrice(int gross_price_set);
    void setTax(int setter_tax);

    virtual double calculateShippingCost() const;

    virtual double calculateTax() const;

    virtual double discountedPrice() const;
};

Book::Book() : title(""), author(""), Product()  {}

Book::Book(string title1, string author1, int gross_price1)
    : gross_price(gross_price1), title(title1), author(author1), discount(10), tax(5), Product()
    {}

Book::~Book() {}

double Book::discountedPrice() const {

    return gross_price - gross_price * discount / 100;
}

void Book::setTax(int setter_tax) {
    if (setter_tax > 100) { throw IllegalTaxExpt(); }
    tax = setter_tax;
}
double Book::calculateShippingCost() const {
    cout << "\nShipping Cost is: ";
    return discountedPrice() + calculateTax();
}

double Book::calculateTax() const {

    return discountedPrice() * tax / 100;
}
ostream& operator<<(ostream& out, const Book& book) {
    out << "Book Title: " << book.title << endl;
    out << "Final Price: " << book.calculateShippingCost() << " lei" << endl;
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
string Book::getTitle() const {
    return title;
}
string Book::getAuthor() const {
    return author;
}
int Book::getPrice() const {
    return gross_price;
}
istream& operator>>(istream& in, Book& book) {
    cout << "Introduce the title: " << endl;
    in >> book.title;
    cout << endl;
    cout << "Introduce the gross price: " << endl;
    in >> book.gross_price;
    if (book.gross_price < 0) {
        throw IllegallPriceExpt ();
    }
    return in;
}
void Book::setTitle(string title_set) {
    title = title_set;
}
void Book::setAuthor(string author_set) {
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
    string password;

    string username;
public:
    User();
    User(string password1, string username1);
    User& operator=(const User &user);
    static void greeting_user() { cout << "Wellcome to Bookstore! " << "\nPlease introduce user details: " << endl;};
    friend istream& operator>>(istream& in, User& user);
};

User::User() : password(""), username("") {}
User::User(string password1, string username1) : password(password1), username(username1) {}

User& User::operator=(const User &user) {
    if (this == &user) {
        return *this;           // self assignment
    }
    this->username = user.username;
    this->password = user.password;
    return *this;
}
istream& operator>>(istream& in, User& user) {
    cout << "Introduce the username: " << endl;
    cin >> user.username;
    cout << "Introduce the password: " << endl;
    cin >> user.password;
    return in;
}

/**Clasa Customer:
 * Aici e clasa Customer cu proprietatile: name, client_type, nr_of_orders, customer_id
 * */
class Customer : protected User {
private:
    string name;
    int nr_of_orders;
    int id;
    static int contor;
public:
    Customer();

    Customer(string name1, int nr_of_orders1);

    Customer& operator=(const Customer& customer);

    friend ostream& operator<<(std::ostream& out, const Customer& new_customer);

    friend istream& operator>>(istream& in, Customer& customer);

    int getNrOrders() const;

    int getCustomerId() const;

    string getName() const;

    bool validation_input(string us, string pas);

    static int counter();
};
int Customer::contor = 1000;
Customer::Customer() : name(""), nr_of_orders(0), id(0) {}
Customer::Customer(string name1, int nr_of_orders1)
                    : id(counter()), name(name1), nr_of_orders(nr_of_orders1) {}

bool Customer::validation_input(string us, string pas) {
    if (password == pas && us == username)
        return true;
    else
        return false;
}
Customer& Customer::operator=(const Customer &customer) {
    if (this == &customer) {
        return *this;           // self assignment
    }
    this->name = customer.name;
    this->nr_of_orders = customer.nr_of_orders;
    return *this;
}

ostream& operator<<(std::ostream& out, const Customer& new_customer) {
    out << "Customer ID: " << new_customer.id << endl;
    out << "Name: " << new_customer.name << endl;
    return out;
}
istream& operator>>(istream& in, Customer& customer) {
    User::greeting_user();
    cout << "Introduce username: " << endl;
    in >> customer.username;
    cout << "Introduce password: " << endl;
    in >> customer.password;
    cout << "Name: " << endl;
    in >> customer.name;
    cout << "Nr of orders: " << endl;
    in >> customer.nr_of_orders;
    return in;
}
int Customer::getNrOrders() const {
    return nr_of_orders;
}
int Customer::getCustomerId() const {
    return id;
}
string Customer::getName() const {
    return name;
}
int Customer::counter() {
    contor++;
    return contor;
}

/** Clasa Employee:
 * Fiecare angajat va fi inregistrat sub forma: (nume, rol, ID, salary)
 * */
class Employee : protected User{
private:
    string name;
    string role;
    int id;
    int salary;
protected:    ///pot lasa private
    static int contor;

    static int count();
public:
    Employee();
    Employee(string name, string role, int salary);
    Employee& operator=(const Employee& employee);
    friend ostream& operator<<(std::ostream& out, const Employee& new_employee);
    friend istream& operator>>(istream& in, Employee& employee);

    int getId()  const;
    string getName() const;
    string getRole() const;
    int getSalary() const;
    void setSalary(int salary_set);
    bool validation_input(string us, string pas);
};
int Employee::contor = 100;

Employee::Employee() : name(""), role(""), salary(0)  {}

Employee::Employee(string name, string role, int salary) : id(count()), name(name), role(role), salary(salary) {}

bool Employee::validation_input(string us, string pas) {
    if (password == pas && us == username)
        return true;
    else
        return false;

}

Employee& Employee::operator=(const Employee& employee) {
    if (this == &employee) {
        return *this;       //protect against self assignment (v = v)
    }
    this->name = employee.name;
    this->role = employee.role;
    this->salary = employee.salary;
    return *this;
}
int Employee::count() {
    contor++;
    return contor;
}
ostream& operator<<(std::ostream& out, const Employee& new_employee) {
    out << "Employee ID: " << new_employee.id << endl;
    out << "Employee name: " << new_employee.name << endl;
    out << "Employee role: " << new_employee.role << endl;
    out << "Employee salary: " << new_employee.salary << " lei" << endl;
 return out;
}
istream& operator>>(istream& in, Employee& employee) {
    User::greeting_user();
    cout << "Introduce username: " << endl;
    in >> employee.username;
    cout << "Introduce password: " << endl;
    in >> employee.password;
    cout << "Introdu numele angajatului: ";
    in >> employee.name;
    cout << "Introdu rolul angajatului: ";
    in >> employee.role;
    cout << "Introdu salariu: ";
    in >> employee.salary;
    return in;
}

int Employee::getId() const {
    return id;
}
string Employee::getName() const {
    return name;
}
string Employee::getRole() const {
    return role;
}
int Employee::getSalary() const {
    return salary;
}

void Employee::setSalary(int salary_set) {
    salary = salary_set;
}

/**Class Event
 * Abstract
 * One pure virtual function
 * */
class Event {
protected:
    string name;
public:
    Event();
    Event(string name1);
    virtual void showEventName() { cout << "Base:: showEventName() " << getName() << endl;};
    virtual double calculateTotalExpenses() { cout << "Event total expenses:  0 "; return 0; };
    virtual void UpdateAll(string name, int param1, int param2, int param3, int param4) = 0;
    void setEventName(string name_set);
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
    void showEventName() override { cout << "Donation name is: " << getName() << endl; };
    void UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) override;
    double calculateTotalExpenses() override;
};

Donatie::Donatie() : donation_expenses(0), sponsorship(0) {}

Donatie::Donatie(int donation_expenses1, int sponsorship1)
        : donation_expenses(donation_expenses1), sponsorship(sponsorship1) {}

void Donatie::UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) {
    this->name = name;
    this->sponsorship = sponsorhips;
    this->donation_expenses = expenses;
}
double Donatie::calculateTotalExpenses() {
    double expenses = 0;
    expenses = getDsponsorhip() + getDonationExp();
    cout << "Donation total expenses:  ";
    return expenses;
}

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
    void showEventName() override { cout << "Contest name is " << getName() << endl; };
    void UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) override;
    double calculateTotalExpenses() override { cout << "Contest total expenses:   "; return getCsponsorship() + getPremium(); };
};

Concurs::Concurs() : premium(0), c_sponsorhip(0) {}

Concurs::Concurs(int premium1, int c_sponsorship1) : premium(premium1), c_sponsorhip(c_sponsorship1){}

void Concurs::UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) {
    this->name = name;
    this->c_sponsorhip = sponsorhips;
    this->premium = expenses;
}

int Concurs::getPremium() const {
    return premium;
}
int Concurs::getCsponsorship() const {
    return c_sponsorhip;
}


class Campanie : public Donatie, public Concurs{

public:
    Campanie();
    Campanie(int premium1, int c_sponsorship1, int donation_expenses1, int sponsorship1);
    void UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) override;
    virtual void showEventName() { cout << "Campain name is " << getName() << endl; };
    virtual double calculateTotalExpenses();
};
Campanie::Campanie() {}

Campanie::Campanie(int premium1, int c_sponsorship1, int donation_expenses1, int sponsorship1) : Concurs(premium1, c_sponsorship1),Donatie(donation_expenses1, sponsorship1) {}

void Campanie::UpdateAll(string name, int expenses, int sponsorhips, int param3, int param4) {
    this->name = name;
    Donatie::UpdateAll("", expenses, sponsorhips, 0, 0);
    Concurs::UpdateAll("", param3, param4, 0, 0);
}

double Campanie::calculateTotalExpenses() {
    double total = 0;
    cout << "Campain total expenses: ";
    total = getPremium() + getCsponsorship() + getDsponsorhip() + getDonationExp();
    return  total;
}
void display_sum(int sum) {
    cout << "The allocated budget for events is: " << sum << endl;
}

class Sponsor {
private:
    string name;
    double sponsorshipAmount;

public:
    Sponsor(const string& name, double sponsorshipAmount) {
        this->name = name;
        this->sponsorshipAmount = sponsorshipAmount;
    }

    friend ostream& operator<<(ostream& os, const Sponsor& sponsor) {
        os << "Sponsor Name: " << sponsor.name << endl;
        os << "Sponsorship Amount: " << sponsor.sponsorshipAmount << endl;
        return os;
    }
};

class Partner {
private:
    string name;
    string partnershipType;

public:
    Partner(const string& name, const string& partnershipType) {
        this->name = name;
        this->partnershipType = partnershipType;
    }

    // Overloaded insertion operator
    friend ostream& operator<<(ostream& os, const Partner& partner) {
        os << "Partner Name: " << partner.name << endl;
        os << "Partnership Type: " << partner.partnershipType << endl;
        return os;
    }
};

// Generic class for the Bussiness Relationship
template<typename T>
class BussinessRelationship {
private:
    vector<T> relations;

public:
    void addRelation(const T& object) {
        relations.push_back(object);
    }

    void displayRelations() const {
        for (const auto& object : relations) {
            cout << object << endl;
        }
    }
};



int main() {

    BussinessRelationship<Sponsor> sponsorBookstore;
    sponsorBookstore.addRelation(Sponsor("ABC Company", 5000.0));
    sponsorBookstore.addRelation(Sponsor("XYZ Corporation", 3000.0));
    sponsorBookstore.addRelation(Sponsor("123 Enterprises", 2000.0));

    BussinessRelationship<Partner> partnerBookstore;
    partnerBookstore.addRelation(Partner("Company A", "Gold"));
    partnerBookstore.addRelation(Partner("Company B", "Silver"));
    partnerBookstore.addRelation(Partner("Company C", "Bronze"));

    cout << "Sponsors:" << endl;
    sponsorBookstore.displayRelations();

    cout << "Partners:" << endl;
    partnerBookstore.displayRelations();


    return 0;
}
