#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <regex>
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
    out << book.calculateShippingCost() << " lei" << endl;
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
    string name;
    int gross_price;
    int discount;
    int tax;

public:
    OfficeSupplies();

    OfficeSupplies( string name1, int gross_price1, int discount1, int tax1);

    friend ostream& operator<<(ostream& out, const OfficeSupplies& supp);

    virtual double calculateShippingCost() const;

    virtual double calculateTax() const;

    virtual double discountedPrice() const;

    void setTax(int tax1) ;

    int getTax() const;
};

OfficeSupplies::OfficeSupplies()
                : name(""), gross_price(0), discount(0), tax(0), Product() {}

OfficeSupplies::OfficeSupplies(string name1, int gross_price1, int discount1, int tax1)
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

/// FOR EVENTS:
class Event {
private:
    string name;
    string date;
    string location;
    string description;

public:
    Event() {}

    void setName(const string& name) {
        this->name = name;
    }

    void setDate(const string& date) {
        this->date = date;
    }

    void setLocation(const string& location) {
        this->location = location;
    }

    void setDescription(const string& description) {
        this->description = description;
    }

    friend ostream& operator<<(ostream& os, const Event& event) {

        os << "Event: " << event.name << endl;
        os << "Date: " << event.date << endl;
        os << "Location: " << event.location << endl;
        os << "Description: " << event.description << endl;
        return os;
    }
};

// EventBuilder abstract class
class EventBuilder {
protected:
    shared_ptr<Event> event;

public:
    virtual void createEvent() = 0;
    virtual void buildName(const string& name) = 0;
    virtual void buildDate(const string& date) = 0;
    virtual void buildLocation(const string& location) = 0;
    virtual void buildDescription(const string& description) = 0;
    virtual shared_ptr<Event> getEvent() = 0;
};

// CampaignBuilder concrete class
class CampaignBuilder : public EventBuilder {
public:
    void createEvent() override {
        event = make_shared<Event>();
    }

    void buildName(const string& name) override {
        event->setName(name);
    }

    void buildDate(const string& date) override {
        event->setDate(date);
    }

    void buildLocation(const string& location) override {
        event->setLocation(location);
    }

    void buildDescription(const string& description) override {
        event->setDescription(description);
    }

    shared_ptr<Event> getEvent() override {
        return event;
    }
};

// Manager class that defines the steps and order in which the builders should build the event
class Manager {
private:
    vector<shared_ptr<Event>> events;
    EventBuilder* eventBuilder;

public:
    void setEventBuilder(EventBuilder* builder) {
        eventBuilder = builder;
    }

    void addEvent() {
        events.push_back(eventBuilder->getEvent());
    }

    void constructEvent(const string& name, const string& date, const string& location, const string& description) {
        eventBuilder->createEvent();
        eventBuilder->buildName(name);
        eventBuilder->buildDate(date);
        eventBuilder->buildLocation(location);
        eventBuilder->buildDescription(description);
        addEvent();
    }

    const vector<shared_ptr<Event>>& getEvents() const {
        return events;
    }
};


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
    // Comparison operator for sorting by sponsorship amount
    bool operator<(const Sponsor& other) const {
        return sponsorshipAmount < other.sponsorshipAmount;
    }
    // Overloading the + operator to sum sponsorshipAmount
    friend int operator+(const Sponsor& lhs, const Sponsor& rhs) {
        return lhs.sponsorshipAmount + rhs.sponsorshipAmount;
    }
    double getSponsorshipAmount() {
        return sponsorshipAmount;
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
    // Custom comparison function to sort partners in alphabetical order
    bool operator<(const Partner& other) const {
        return name < other.name;
    }
    bool operator==(const Partner& other) const {
        return name == other.name && partnershipType == other.partnershipType;
    }

    bool operator!=(const Partner& other) const {
        return !(*this == other);
    }

    string getPartnershipType() const {
        return partnershipType;
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
    void UpdateRelationsList() {
        sort(relations.begin(), relations.end());
    }

    typename vector<T>::iterator findPartnerByType(const string& partnershipType) {
        return find_if(relations.begin(), relations.end(), [&](const T& partner) {
            return partner.getPartnershipType() == partnershipType;
        });
    }

    bool hasPartnerByType(const string& partnershipType) {
        return findPartnerByType(partnershipType) != relations.end();
    }

    void printPartnerByType(const string& partnershipType) {
        auto partnerIt = findPartnerByType(partnershipType);
        if (partnerIt != relations.end()) {
            cout << "Found partner with " << partnershipType << " status:" << endl;
            cout << *partnerIt << endl;
        } else {
            cout << "No partner with " << partnershipType << " status found." << endl;
        }
    }
};
// Template specialization for sorting sponsors by name and sponsorshipAmount and also calculate the total sponsorship amount
template<>
void BussinessRelationship<Sponsor>::UpdateRelationsList() {
    sort(relations.begin(), relations.end());
    double sum = 0;
    for (const auto& object : relations) {
        sum = sum + static_cast<Sponsor>(object).getSponsorshipAmount();
    }
    cout << "The total amount offered by sponsors is: " << sum << endl;
    cout << endl;

};

int main() {

    ///////////////////  *  PART I of testing TEMPLATES AND SPECIALIZATION OBJ, STL find_if, sort *  ///////////////////

    BussinessRelationship<Sponsor> sponsorBookstore;
    sponsorBookstore.addRelation(Sponsor("ABC Company", 5000.0));
    sponsorBookstore.addRelation(Sponsor("XYZ Corporation", 3000.0));
    sponsorBookstore.addRelation(Sponsor("123 Enterprises", 2000.0));

    BussinessRelationship<Partner> partnerBookstore;
    partnerBookstore.addRelation(Partner("Company B", "Gold"));
    partnerBookstore.addRelation(Partner("Company C", "Silver"));
    partnerBookstore.addRelation(Partner("Company A", "Bronze"));

    cout << "Sponsors:" << endl;
    sponsorBookstore.displayRelations();
    sponsorBookstore.UpdateRelationsList();
    cout << "Sorted Sponsors (by sponsorship amount):" << endl;
    sponsorBookstore.displayRelations();


    cout << "Sorted Partners (by their name):" << endl;
    partnerBookstore.UpdateRelationsList();
    partnerBookstore.displayRelations();
    BussinessRelationship<Partner> businessRelationship;

    businessRelationship.addRelation(Partner("Partner A", "Gold"));
    businessRelationship.addRelation(Partner("Partner B", "Silver"));
    businessRelationship.addRelation(Partner("Partner C", "Bronze"));
    businessRelationship.addRelation(Partner("Partner D", "Silver"));

    businessRelationship.displayRelations();
    cout << endl;

    businessRelationship.printPartnerByType("Gold");

    ///////////////////  *   PART II of testing  REGEX, SHARED_PTR, BUILDER PATTERN  * ///////////////////

    Manager manager;
    // Validate date using regular expression
    regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    int numEvents;


    cout << "Enter the number of events to create: ";
    cin >> numEvents;

    for (int i = 0; i < numEvents; i++) {
        string name, date, location, description;

        cout << "Enter details for Event " << i+1 << ":" << endl;

        // Validate and read name
        cout << "Name: ";
        cin >> name;

        // Validate and read date
        while (true) {
            cout << "Date (YYYY-MM-DD): ";
            cin >> date;

            if (regex_match(date, dateRegex)) {
                break;
            } else {
                cout << "Invalid date format. Please enter in the format YYYY-MM-DD." << endl;
            }
        }

        cout << "Location: ";
        cin >> location;

        cout << "Description: ";
        cin >> description;

        CampaignBuilder campaignBuilder;
        manager.setEventBuilder(&campaignBuilder);
        manager.constructEvent(name, date, location, description);
    }

    const vector<shared_ptr<Event>>& events = manager.getEvents();
    cout << "\n\nEvents you've just introduced: "<< endl;
    for (const auto& event : events) {
        cout << *event << endl;
    }

    ////////////// * PREVIOUS MENU : UPDATE -> used unique_ptr * //////////////

    string username = "";
    string password = "";
    int account_option;

    Employee employee("", "", 5000);

    Customer customer("Radu Valentin",  1);
    cout << "\nChoose an account type:    0-Customer  |   1-Employee\n";
    cin >> account_option;
    if (account_option == 0) {
        cin >> customer;
        cout << "Please loggin to see your account details! " << endl;
        cout << "Introduce username: " << endl;
        cin >> username;
        cout << "Introduce password: " << endl;
        cin >> password;
        if (customer.validation_input(username, password)) {
            cout << "Authentification successfull!" << endl;
            cout << "---Account details---" << endl;
            cout << customer;
            cout << "nr of orders: " << customer.getNrOrders() << endl;
            cout << "----------------\n" << endl;

            /**Downcasting:
             * using dynamic_cast
             * */
            Product* prod;
            try {
                int buy_option;

                cout << "What discount card you have?    0 - BooksExpress  ||   1 - OfficeExpress";
                cin >> buy_option;

                if (buy_option == 0)
                    prod = new Book("The Great Gatsby", "F. Scott Fitzgerald", 200);
                else if (buy_option == 1)
                    prod = new OfficeSupplies("Set of pencils", 70, 20, 1);
                else {
                    cout << "Make sure you've introduced the correct number!" << endl;
                    return 0;
                }
                cout << "Buy the book  -  1     ||    Buy the pencils   -   0";
                cin >> buy_option;
                if (buy_option == 1 && dynamic_cast<Book*>(prod))
                    cout << "Congrats! You bought a book with only " << prod->calculateShippingCost() << " $" << endl;
                else if (buy_option == 0 && dynamic_cast<OfficeSupplies*>(prod))
                    cout << "Congrats! You bought pencils with only " << prod->calculateShippingCost() << " $" << endl;
                else throw runtime_error("Can't buy books having OfficeExpress card and pencils having BooksExpress card!>> See you next time! ");
            } catch (runtime_error& error) {
                cout << error.what() << endl;
            }
            if (prod != NULL) {
                delete prod;
            }

        }
    } else if (account_option == 1) {
        cin >> employee;
        cout << "Please loggin to see your account details! " << endl;
        cout << "Introduce username: " << endl;
        cin >> username;
        cout << "Introduce password: " << endl;
        cin >> password;
        if (employee.validation_input(username, password)) {
            cout << "Authentification successfull!" << endl;
            cout << "---Account details---" << endl;
            cout << employee;
            cout << "----------------\n" << endl;

            account_option = -1;
            cout << "want to add items in stock ?  1:yes || 0:no";
            cin >> account_option;
            if (account_option == 1) {
                int nr_items;
                vector<unique_ptr<Product>> products;
                cout << "How many items you want to add? " <<  endl;
                cin >> nr_items;

                for (int i = 0; i<nr_items;i++) {
                    int opt;
                    cout << "Introduce: " << endl;
                    cout << "1.Book" << endl;
                    cout << "2.Office item" << endl;
                    cin >> opt;
                    switch (opt) {
                        case 1: {
                            string title;
                            string author;
                            int price;
                            cout << "Titlu: " << endl;
                            cin >> title;
                            cout << "Autor: " << endl;
                            cin >> author;
                            cout << "price: " << endl;
                            cin >> price;
                            products.push_back(make_unique<Book>(title, author, price));
                            break;
                        }
                        case 2: {
                            string name;
                            int gross_price;
                            cout << "Name: " << endl;
                            cin >> name;
                            cout << "pret: " << endl;
                            cin >> gross_price;
                            products.push_back(make_unique<OfficeSupplies>(name, gross_price, 10, 2));
                            break;
                        }

                    }
                }

//                for (const auto& product : products) {
//                    if (dynamic_cast<Book*>(product)) {
//                        cout << *dynamic_cast<Book*>(product) << endl;
//                    } else {
//                        cout << *dynamic_cast<OfficeSupplies*>(product) << endl;
//                    }
                for (const auto& product : products) {
                    if (auto book = dynamic_cast<Book*>(product.get())) {
                        cout << *book << endl;
                    } else if (auto officeSupplies = dynamic_cast<OfficeSupplies*>(product.get())) {
                        cout << *officeSupplies << endl;
                    }
                }

                }
            }


        }


    return 0;
}