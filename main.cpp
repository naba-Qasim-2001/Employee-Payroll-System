#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Employee {
private:
    int id;
    string name;
protected:
    double salary;
public:
    Employee(int id, const string& name, double salary)
        : id(id), name(name), salary(salary) {}
    virtual ~Employee() {}
    int getId() const { return id; }
    string getName() const { return name; }
    virtual double calculate() const = 0;
    virtual string type() const = 0;
};

class FullTime : public Employee {
protected:
    double bonus;
public:
    FullTime(int id, const string& name, double salary, double bonus = 0)
        : Employee(id, name, salary), bonus(bonus) {}
    string type() const override { return "Full-time"; }
    double calculate() const override { return salary + bonus; }
};

class Manager : public FullTime {
    double allowance;
public:
    Manager(int id, const string& name, double salary, double allowance)
        : FullTime(id, name, salary), allowance(allowance) {}
    string type() const override { return "Manager"; }
    double calculate() const override { return salary + bonus + allowance; }
};

class PartTime : public Employee {
    double rate;
    int hours;
public:
    PartTime(int id, const string& name, double rate, int hours)
        : Employee(id, name, 0), rate(rate), hours(hours) {}
    string type() const override { return "Part-time"; }
    double calculate() const override { return rate * hours; }
};

// قراءة قيمة رقمية مع التحقق (ما يوقف البرنامج إذا انكتب حرف)
template <typename T>
T readValue(const string& prompt, bool nonNegative = true) {
    T v;
    cout << prompt;
    while (!(cin >> v) || (nonNegative && v < 0)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

bool idExists(const vector<unique_ptr<Employee>>& list, int id) {
    for (const auto& e : list)
        if (e->getId() == id) return true;
    return false;
}

int main() {
    vector<unique_ptr<Employee>> list;
    int choice;
    do {
        cout << "\n1. Add full-time\n2. Add part-time\n3. Add manager\n"
             << "4. Report\n0. Exit\n";
        choice = readValue<int>("Choice: ");

        if (choice == 1 || choice == 3) {
            int id = readValue<int>("ID: ");
            if (idExists(list, id)) { cout << "ID already exists.\n"; continue; }
            string name;
            cout << "Name: "; getline(cin, name);
            double salary = readValue<double>("Monthly salary: ");
            double extra  = readValue<double>(choice == 1 ? "Bonus: " : "Allowance: ");
            if (choice == 1) list.push_back(make_unique<FullTime>(id, name, salary, extra));
            else             list.push_back(make_unique<Manager>(id, name, salary, extra));
        }
        else if (choice == 2) {
            int id = readValue<int>("ID: ");
            if (idExists(list, id)) { cout << "ID already exists.\n"; continue; }
            string name;
            cout << "Name: "; getline(cin, name);
            double rate = readValue<double>("Hourly rate: ");
            int hours   = readValue<int>("Hours: ");
            list.push_back(make_unique<PartTime>(id, name, rate, hours));
        }
        else if (choice == 4) {
            double total = 0;
            cout << fixed << setprecision(2);
            for (const auto& e : list) {
                double pay = e->calculate();
                cout << e->getId() << " | " << e->getName() << " | "
                     << e->type() << " | " << pay << "\n";
                total += pay;
            }
            cout << "Total: " << total << "\n";
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
