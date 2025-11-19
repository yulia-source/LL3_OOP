#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Person {
private:
    string surname;
    string name;
    string patronymic;
    string gender;
    int day, month, year;

public:
    Person() {
        surname = name = patronymic = gender = "";
        day = month = year = 0;
    }

    friend istream& operator>>(istream& in, Person& p) {
        cout << "Enter surname: ";
        in >> p.surname;
        cout << "Enter name: ";
        in >> p.name;
        cout << "Enter patronymic: ";
        in >> p.patronymic;
        cout << "Enter gender (m/f): ";
        in >> p.gender;

        cout << "Enter date of birth (day month year): ";
        in >> p.day >> p.month >> p.year;

        if (p.day < 1 || p.day > 31 || p.month < 1 || p.month > 12 || p.year < 1900 || p.year > 2025)
            throw invalid_argument("Invalid date of birth!");

        return in;
    }

    friend ostream& operator<<(ostream& out, const Person& p) {
        out << "---------------------------------\n";
        out << "Surname: " << p.surname << endl;
        out << "Name: " << p.name << endl;
        out << "Patronymic: " << p.patronymic << endl;
        out << "Gender: " << p.gender << endl;
        out << "Date of birth: " << p.day << "." << p.month << "." << p.year << endl;
        out << "---------------------------------\n";
        return out;
    }

    bool search(int y) const {
        return year == y;
    }

    bool search(const string& value, const string& field) const {
        if (field == "surname") return surname == value;
        if (field == "gender") return gender == value;
        return false;
    }
};

int main() {
    Person person;
    int choice;

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Enter person data\n";
        cout << "2. Display person data\n";
        cout << "3. Search by surname\n";
        cout << "4. Search by year of birth\n";
        cout << "5. Search by gender\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "Exiting program...\n";
            return 0;

        case 1:
            try {
                cin >> person;
            }
            catch (const invalid_argument& e) {
                cerr << e.what() << endl;
            }
            break;

        case 2:
            cout << person;
            break;

        case 3: {
            string s;
            cout << "Enter surname: ";
            cin >> s;
            if (person.search(s, "surname")) cout << "Found!\n";
            else cout << "Not found.\n";
            break;
        }

        case 4: {
            int y;
            cout << "Enter year: ";
            cin >> y;
            if (person.search(y)) cout << "Found!\n";
            else cout << "Not found.\n";
            break;
        }

        case 5: {
            string g;
            cout << "Enter gender (m/f): ";
            cin >> g;
            if (person.search(g, "gender")) cout << "Found!\n";
            else cout << "Not found.\n";
            break;
        }

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
