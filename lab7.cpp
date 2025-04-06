#include <iostream>
#include <string>
using namespace std;

// Клас "Address" (підклас — частина "Person")
class Address {
private:
    string city;
    string street;
    int building;

public:
    // Конструктор за замовчуванням
    Address()
        : city("Unknown"), street("Unknown"), building(0)
    {}

    // Конструктор з параметрами
    Address(const string &c, const string &s, int b)
        : city(c), street(s), building(b)
    {}

    // Сетери
    void setCity(const string &c)    { city = c; }
    void setStreet(const string &s)  { street = s; }
    void setBuilding(int b)          { building = b; }

    // Гетери
    string getCity()    const { return city; }
    string getStreet()  const { return street; }
    int    getBuilding()const { return building; }

    // Виведення
    void printAddress() const {
        cout << city << ", " << street << " bld. " << building;
    }
};

// Клас "Person" (агрегатор) містить об'єкт "Address"
class Person {
private:
    string name;
    int age;
    Address address; // агрегація: Person "має" Address

public:
    // Конструктор за замовчуванням
    Person()
        : name("NoName"), age(0), address()
    {}

    // Конструктор з параметрами
    Person(const string &n, int a, const Address &addr)
        : name(n), age(a), address(addr)
    {}

    // Методи set
    void setName(const string &n)    { name = n; }
    void setAge(int a)               { age = a; }
    void setAddress(const Address &ad){ address = ad; }

    // Методи get
    string  getName()    const { return name; }
    int     getAge()     const { return age; }
    Address getAddress() const { return address; }

    // Виведення
    void printPerson() const {
        cout << "Person: " << name
             << " (Age: " << age << "), Address: ";
        address.printAddress();
        cout << "\n";
    }
};

// Головна функція
int main() {
    cout << "=== Лабораторна робота №7: Агрегація об’єктів у класі ===\n\n";

    // 1) Створюємо "порожнього" Person (дефолт)
    Person p1;
    p1.printPerson();

    // 2) Змінюємо дані (Name, Age, Address)
    p1.setName("Ivan");
    p1.setAge(30);
    Address addr("Kyiv", "Khreshchatyk", 1);
    p1.setAddress(addr);
    p1.printPerson();

    // 3) Створюємо Person з повним набором параметрів
    Person p2("Oksana", 25, Address("Lviv", "Shevchenko St.", 10));
    p2.printPerson();

    cout << "\n=== Завершення програми ===\n";
    return 0;
}
