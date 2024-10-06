#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_PEOPLE = 1000;

// Define the Person class
class Person {
    private:
        string first_name;
        string last_name;
        int birth_year;
        int death_year;
        string contribution;

    public:
        // Constructor
        Person(string first = "", string last = "", int birth = 0, int death = -1, string contr = "") {
            first_name = first;
            last_name = last;
            birth_year = birth;
            death_year = death;
            contribution = contr;
        }

        // Copy constructor
        Person(const Person& other) {
            first_name = other.first_name;
            last_name = other.last_name;
            birth_year = other.birth_year;
            death_year = other.death_year;
            contribution = other.contribution;
        }

        // Destructor
        ~Person() {}

        // Getter methods
        string get_first_name() const {
            return first_name;
        }

        string get_last_name() const {
            return last_name;
        }

        int get_birth_year() const {
            return birth_year;
        }

        int get_death_year() const {
            return death_year;
        }

        string get_contribution() const {
            return contribution;
        }

        // Setter methods
        void set_first_name(string first) {
            first_name = first;
        }

        void set_last_name(string last) {
            last_name = last;
        }

        void set_birth_year(int birth) {
            birth_year = birth;
        }

        void set_death_year(int death) {
            death_year = death;
        }

        void set_contribution(string contr) {
            contribution = contr;
        }

        // Print method
        void print() const {
            cout << "Name: " << first_name << " " << last_name << endl;
            cout << "Birth Year: " << birth_year << endl;
            if (death_year != -1) {
                cout << "Death Year: " << death_year << endl;
            }
            cout << "Contribution: " << contribution << endl;
            cout << endl;
        }
};

class Table {
    private:
        Person* people;
        int num_people;
        const static int MAX_PEOPLE = 100;

    public:
        // Constructor
        Table() {
            people = new Person[MAX_PEOPLE];
            num_people = 0;
        }

        // Copy constructor
        Table(const Table& other) {
            people = new Person[MAX_PEOPLE];
            num_people = other.num_people;

            for (int i = 0; i < num_people; i++) {
                people[i] = other.people[i];
            }
        }

        // Destructor
        ~Table() {
            delete[] people;
        }

        // Print method
        void print() const {
            for (int i = 0; i < num_people; i++) {
                people[i].print();
            }
        }

        // Read method
        void read(string filename) {
            ifstream infile(filename);

            if (!infile) {
                cout << "Error opening file" << endl;
                return;
            }

            string line;
            while (getline(infile, line)) {
                string first, last, contr;
                int birth, death;
                istringstream iss(line);

                iss >> first >> last >> birth >> death;
                getline(iss, contr);

                people[num_people] = Person(first, last, birth, death, contr);
                num_people++;
            }

            infile.close();
        }

        // Search by name method
        void search_by_name(string name) const {
            for (int i = 0; i < num_people; i++) {
                if (people[i].get_first_name() == name || people[i].get_last_name() == name) {
                    people[i].print();
                }
            }
        }

        // Search by birth year range method
        void search_by_birth_year_range(int start, int end) const {
            for (int i = 0; i < num_people; i++) {
                int birth = people[i].get_birth_year();

                if (birth >= start && birth <= end) {
                    people[i].print();
                }
            }
        }
};

// Main function
int main() {
    // Print the author's name and UAID
    cout << "Author: Dylan Pallasigui\n";

    Table t;
    t.read("people.txt");

    int choice;
    do {
        cout << "1. Print table\n";
        cout << "2. Search by name\n";
        cout << "3. Search by birth year range\n";
        cout << "4. Quit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                t.print();
                break;
            case 2: {
                string name;
                cout << "Enter name to search for: ";
                cin >> name;
                t.search_by_name(name);
                break;
            }
            case 3: {
                int start, end;
                cout << "Enter birth year range (start end): ";
                cin >> start >> end;
                t.search_by_birth_year_range(start, end);
                break;
            }
            case 4:
                break;
            default:
                cout << "Invalid choice" << endl;
        }

        cout << endl;
    } while (choice != 4);

    return 0;
}