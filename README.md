# Employee Payroll System (C++ OOP Project)

## Project Description
A console-based payroll system that manages full-time, part-time, and manager employees. It calculates each employee's salary and the total payroll, and prints a report of all employees.

## Objectives
- Apply OOP concepts in a practical application.
- Manage employees using classes and objects.
- Calculate salaries polymorphically based on employee type.

## OOP Concepts Applied
- **Classes and Objects:** `Employee`, `FullTime`, `Manager`, `PartTime`.
- **Encapsulation:** private data members (`id`, `name`) with public getters.
- **Constructors and Destructors:** parameterized constructors and a virtual destructor.
- **Inheritance:** `FullTime` and `PartTime` inherit from `Employee`; `Manager` inherits from `FullTime`.
- **Polymorphism:** virtual `calculate()` and `type()` overridden in each derived class, called through `unique_ptr<Employee>`.
- **Abstract Class:** `Employee` has pure virtual functions and cannot be instantiated.
- **Access Modifiers:** `private`, `protected`, and `public` are used across the classes.
- **Smart Pointers:** `std::unique_ptr` manages employee objects automatically.

## Features
- Add full-time employees (salary + bonus).
- Add part-time employees (hourly rate x hours).
- Add managers (salary + bonus + allowance).
- Report showing ID, name, type, and pay for each employee, plus the total payroll.
- Input validation: rejects non-numeric input, negative values, and duplicate IDs.

## Requirements
- A C++17 compatible compiler (g++, clang++, or MSVC).

## How to Compile and Run
```bash
g++ -std=c++17 main.cpp -o payroll
./payroll
```

## Menu
```
1. Add full-time
2. Add part-time
3. Add manager
4. Report
0. Exit
```

## Sample Output
```
1 | Ali | Full-time | 1500.00
2 | Sara | Part-time | 400.00
3 | Omar | Manager | 2500.00
Total: 4400.00
```
