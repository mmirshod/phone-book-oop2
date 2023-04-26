#include "string"
#include "fstream"
#include "vector"
#include "iostream"
#include "iomanip"
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


int get_number_of_records(string filename) {
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


bool file_exists(string filename) {
    /**
     * @brief Validate whether file exist or not
     * @param filename A string representing full path to the file (or just filename)
     * @returns True if file exists. False if file does NOT exist
     */

    ifstream fin(filename);
    return fin.good();
}

int make_choice() {
    int choice;
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
         << setw(23) << "Delete Contact" << "|" << endl;
    cout << setfill('-') << setw(35) << "" << endl;
    cout << setfill(' ') << left << setw(10) << "| 0" << "|"
         << setw(23) << "Exit" << "|" << endl;
    cout << setfill('=') << setw(35) << "" << endl;
    cout << "Enter key: "; cin >> choice;
    return choice;
}
