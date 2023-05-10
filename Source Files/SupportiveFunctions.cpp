#include "string"
#include "vector"
#include "iostream"
#include "iomanip"
#include "../Header Files/SupportiveFunctions.h"

using namespace std;

string to_upper(string str){
    /**
    Convert a string to upper case.

    @param str The input string to be converted to upper case.
    @return The input string in upper case format.
    */

    for(char & i : str)
        i=toupper(i);

    return str;
}


int get_number_of_records(const string& filename) {
    /**
     * @brief Returns number of records in the .csv file
     * @param filename A string representing full path to the file (or just filename)
     * @return An integer representing number of records.
     */

    fstream fin(filename, ios::in);
    int i = 0;
    string temp;

    while(getline(fin, temp)) {
        i++;
    }
    fin.close();
    return i - 1;
}

int make_choice_main_menu() {
    int choice;
    string userInput;

    cout << setfill('=') << setw(35) << "" << endl;
    cout << setfill(' ') << left << setw(10) << "| Key" << "|"
         << setw(23) << "Option" << "|" << endl;
    cout << setfill('=') << setw(35) << "" << endl;
    cout << setfill(' ') << left << setw(10) << "| 1" << "|"
         << setw(23) << "Add Contact" << "|" << endl;
    cout << setfill(' ') << left << setw(10) << "| 2" << "|"
         << setw(23) << "Find Contact" << "|" << endl;
    cout << setfill(' ') << left << setw(10) << "| 3" << "|"
         << setw(23) << "Read All Contacts" << "|" << endl;
    cout << setfill(' ') << left << setw(10) << "| 4" << "|"
         << setw(23) << "Update Contact" << "|" << endl;
    cout << setfill(' ') << left << setw(10) << "| 5" << "|"
         << setw(23) << "Delete Contact" << "|" << endl;
    cout << setfill('-') << setw(35) << "" << endl;
    cout << setfill(' ') << left << setw(10) << "| 0" << "|"
         << setw(23) << "Exit" << "|" << endl;
    cout << setfill('=') << setw(35) << "" << endl;
    cout << "Enter key: \n";
    getline(cin, userInput);

    // validate that  user input is integer
    try {
        choice = stoi(userInput);
        if (choice >= 0 and choice <= 4)
            return choice;
    } catch (...) {
        return -1;
    }
    return -1;
}

optional <Contact> find_contact(const string& number, Phonebook& p) {
    ifstream fin(p.getFileName(), ios::in);

    // skip header row
    string temp, field;
    getline(fin, temp);

    try {
        // skip to desired position_
        for (int i = 0; i < p.getNumberOfContacts(); ++i) {
            vector<string> contact;

            getline(fin, temp);  // getting entire record into one string
            stringstream ss(temp);  // giving string 'temp' as an input string to our string stream

            // parsing string stream into a 'contact' vector
            while (getline(ss, field, ',')) {
                contact.push_back(field);
            }

            // check if contact has the same number as user inputted
            if (contact[3] == number) {
                // assuming that contact now has right data display it to user
                Contact contact_to_display(contact[1], contact[2], contact[3],
                                           contact[5], stoi(contact[0]),
                                           stoi(contact[4])
                );

                fin.close(); // close the file
                return contact_to_display; // if yes return Contact
            }
        }
    } catch(invalid_argument&) {
        cout << "INVALID_ARGUMENT_ERROR" << endl;
    } catch(exception& e) {
        if (e.what() == "Segmentation fault")
            cout << "\nSEGMENTATION FAULT\n";
    } catch (...) {
        cout << "OCCURRED_EXCEPTION" << endl;
    }

    fin.close();
    return nullopt;
}

int make_choice_update_contact() {
    int choice;
    string userInput;

    // get user input
    cout << "\nWhat do you want to change?\n"
            "1 |\tFirst Name\n"
            "2 |\tLast Name\n"
            "3 |\tPhone Number\n"
            "0 |\tGo Back\n";
    getline(cin, userInput);

    // validate that  user input is integer
    try {
        choice = stoi(userInput);
        if (choice >= 0 and choice <= 3)
            return choice;
    } catch (...) {
        return -1;
    }
    return -1;
}

int make_choice_select_role() {
    int choice;
    string userInput;

    // get user input
    cout << "\nWhat is your role in a company?\n"
            "1 |\tOwner\n"
            "2 |\tManager\n"
            "3 |\tSpecialist\n"
            "4 |\tIntern\n";

    getline(cin, userInput);

    // validate that  user input is integer
    try {
        choice = stoi(userInput);
        if (choice >= 0 and choice <= 4)
            return choice;
    } catch (...) {
        return -1;
    }
    return -1;
}

bool check_password(const string& p, const string& r) {
    fstream fin(R"(D:\Mirshod\IUT\OOP2\phone-book\Resource Files\employees.csv)");
    string word, line;
    vector <string> row;

    while(getline(fin, line)){
        row.clear();

        // Owner, 12345
        // Manager, uuuuu

        // parse file data to vector
        stringstream ss(line);
        while(getline(ss, word, ','))
            row.push_back(word);

        // check if password for given role is correct
        if (row[0] == r) // for role
            if (row[1] == p) // for password
                return true;
    }

    return false;
}
