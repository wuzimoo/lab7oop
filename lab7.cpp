#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Клас "Product"
class Product {
private:
    string name;    // назва товару
    int quantity;   // кількість одиниць товару
    double cost;    // ціна одиниці товару

public:
    // Конструктор за замовчуванням
    Product()
        : name("Unnamed"), quantity(0), cost(0.0)
    {}

    // Конструктор з параметрами
    Product(const string &n, int q, double c)
        : name(n), quantity(q), cost(c)
    {}

    // Сетери
    void setName(const string &n)       { name = n; }
    void setQuantity(int q)            { quantity = q; }
    void setCost(double c)             { cost = c; }

    // Гетери
    string getName()    const { return name; }
    int    getQuantity()const { return quantity; }
    double getCost()    const { return cost; }
};

// Клас "Shop" (агрегатор), містить масив (vector) об'єктів "Product"
class Shop {
private:
    vector<Product> products; // список товарів

public:
    // Додати новий продукт
    void addProduct(const Product &p) {
        products.push_back(p);
    }

    // Пошук товару за назвою (може бути кілька)
    // Повертає список знайдених товарів
    vector<Product> searchByName(const string &searchName) const {
        vector<Product> results;
        for (auto &prod : products) {
            if (prod.getName() == searchName) {
                results.push_back(prod);
            }
        }
        return results;
    }

    // Знаходить товар із мінімальною ціною (або nullptr, якщо список порожній)
    // Повертає вказівник на знайдений Product (для наочності),
    // можна було й індекс або саме Product
    const Product* findMinCostProduct() const {
        if (products.empty()) {
            return nullptr;
        }
        const Product* minProd = &products[0];
        for (size_t i = 1; i < products.size(); i++) {
            if (products[i].getCost() < minProd->getCost()) {
                minProd = &products[i];
            }
        }
        return minProd;
    }

    // Вивід усіх товарів (допоміжний метод)
    void printAll() const {
        if (products.empty()) {
            cout << "[Список товарів порожній]\n";
            return;
        }
        for (size_t i = 0; i < products.size(); i++) {
            cout << i+1 << ") \"" << products[i].getName() << "\" "
                 << " Qty: "  << products[i].getQuantity()
                 << " Cost: " << products[i].getCost()
                 << "\n";
        }
    }
};

// Проста функція для зчитування числа з консолі з перевіркою
int readInt() {
    int val;
    while (true) {
        cin >> val;
        if (!cin.fail()) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некоректне число. Спробуйте ще: ";
    }
    return val;
}

double readDouble() {
    double val;
    while (true) {
        cin >> val;
        if (!cin.fail()) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некоректне число. Спробуйте ще: ";
    }
    return val;
}

// Головна функція (демонструє роботу класів)
int main() {
    cout << "=== Лабораторна робота №7 (Варіант 2): Агрегація класів [Shop -> Product] ===\n";

    Shop shop;
    bool running = true;

    while (running) {
        cout << "\nОберіть дію:\n"
             << "1) Додати новий товар\n"
             << "2) Пошук товару за назвою\n"
             << "3) Знайти товар з мінімальною ціною\n"
             << "4) Вивести усі товари\n"
             << "0) Вихід\n"
             << "Ваш вибір: ";

        int choice = readInt();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистити буфер

        switch (choice) {
            case 1: {
                // Додати товар
                cout << "Введіть назву товару: ";
                string nm;
                getline(cin, nm);

                cout << "Введіть кількість: ";
                int qty = readInt();

                cout << "Введіть ціну: ";
                double cst = readDouble();

                Product p(nm, qty, cst);
                shop.addProduct(p);

                cout << "[Товар додано]\n";
                break;
            }
            case 2: {
                // Пошук за назвою
                cout << "Введіть назву товару для пошуку: ";
                string searchStr;
                getline(cin, searchStr);

                vector<Product> found = shop.searchByName(searchStr);
                if (found.empty()) {
                    cout << "[Нічого не знайдено]\n";
                } else {
                    cout << "[Знайдено " << found.size() << " товар(ів)]:\n";
                    for (auto &f : found) {
                        cout << "Name: " << f.getName()
                             << ", Qty: " << f.getQuantity()
                             << ", Cost: " << f.getCost()
                             << "\n";
                    }
                }
                break;
            }
            case 3: {
                // Мінімальна ціна
                const Product* minP = shop.findMinCostProduct();
                if (!minP) {
                    cout << "[Список товарів порожній]\n";
                } else {
                    cout << "[Товар з мін. ціною]: "
                         << minP->getName() << " | "
                         << "Qty: " << minP->getQuantity()
                         << " | Cost: " << minP->getCost()
                         << "\n";
                }
                break;
            }
            case 4: {
                // Вивести усі
                shop.printAll();
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default:
                cout << "[Невірний вибір]\n";
                break;
        }
    }

    cout << "\n=== Завершення програми ===\n";
    return 0;
}
